#include "hospital.h"

static void recalc(Patient *p) {
    int ri;
    if (p->roomNumber > 0 && p->daysAdmitted > 0) {
        ri = findRoomIndex(p->roomNumber);
        if (ri >= 0)
            p->roomCharges = p->daysAdmitted * rooms[ri].dailyRate;
    }
    p->totalBill = p->roomCharges + p->doctorFee + p->medicineCharges +
                   p->labCharges - p->discount;
    if (p->totalBill < 0)
        p->totalBill = 0;
}

void viewPatientBill(void) {
    int id, pi, i, any;
    Patient *p;

    if (!readInt("Patient id: ", &id))
        return;
    pi = findPatientIndex(id);
    if (pi < 0) {
        printf("Not found.\n");
        return;
    }
    p = &patients[pi];
    recalc(p);

    printf("\n===== Bill for %s (id %d) =====\n", p->name, p->id);
    printf("Status: %s\n", p->status);
    printf("Room: %d   Days: %d\n", p->roomNumber, p->daysAdmitted);
    printf("Room charge : %.2f\n", p->roomCharges);
    printf("Doctor fee  : %.2f\n", p->doctorFee);
    printf("Medicines   : %.2f\n", p->medicineCharges);
    printf("Lab         : %.2f\n", p->labCharges);
    printf("Discount    : %.2f\n", p->discount);
    printf("----------------------------\n");
    printf("TOTAL       : %.2f Tk\n", p->totalBill);
    printf("============================\n");

    printf("\nMeds given:\n");
    any = 0;
    for (i = 0; i < prescCount; i++) {
        if (prescriptions[i].patientId == id) {
            int mi = findMedIndex(prescriptions[i].medicineId);
            printf("  %s x%d = %.0f (%s)\n",
                   mi >= 0 ? medicines[mi].name : "?",
                   prescriptions[i].quantity, prescriptions[i].amount,
                   prescriptions[i].date);
            any = 1;
        }
    }
    if (!any)
        printf("  none\n");

    printf("Lab:\n");
    any = 0;
    for (i = 0; i < labOrderCount; i++) {
        if (labOrders[i].patientId == id) {
            int li = findLabIndex(labOrders[i].labTestId);
            printf("  %s [%s] %.0f\n",
                   li >= 0 ? labTests[li].name : "?",
                   labOrders[i].status, labOrders[i].amount);
            any = 1;
        }
    }
    if (!any)
        printf("  none\n");
}

void applyDiscount(void) {
    int id, pi;
    double pct, before;

    if (!readInt("Patient id: ", &id))
        return;
    pi = findPatientIndex(id);
    if (pi < 0) {
        printf("Not found.\n");
        return;
    }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Already discharged.\n");
        return;
    }

    if (!readDouble("Discount % (0-100): ", &pct) || pct < 0 || pct > 100) {
        printf("Bad percent.\n");
        return;
    }

    recalc(&patients[pi]);
    before = patients[pi].roomCharges + patients[pi].doctorFee +
             patients[pi].medicineCharges + patients[pi].labCharges;
    patients[pi].discount = before * pct / 100.0;
    recalc(&patients[pi]);

    printf("Discount = %.2f Tk, new total = %.2f\n",
           patients[pi].discount, patients[pi].totalBill);
}

void dischargePatient(void) {
    int id, pi, ri;
    Patient *p;

    if (!readInt("Patient id: ", &id))
        return;
    pi = findPatientIndex(id);
    if (pi < 0) {
        printf("Not found.\n");
        return;
    }
    p = &patients[pi];

    if (strcmp(p->status, "Discharged") == 0) {
        printf("Already discharged.\n");
        return;
    }
    if (p->doctorId < 0) {
        printf("Assign a doctor first.\n");
        return;
    }
    if (p->daysAdmitted < 1)
        p->daysAdmitted = 1;

    recalc(p);

    if (p->roomNumber > 0) {
        ri = findRoomIndex(p->roomNumber);
        if (ri >= 0) {
            rooms[ri].occupied = 0;
            rooms[ri].patientId = -1;
            strcpy(rooms[ri].status, "Available");
        }
    }

    releaseDoctorFromPatient(pi);
    todayDate(p->dischargeDate, MAX_DATE);
    strcpy(p->status, "Discharged");

    printf("\n******** HOSPITAL BILL ********\n");
    printf("Patient ID   : %d\n", p->id);
    printf("Name         : %s\n", p->name);
    printf("Admitted     : %s\n", p->admitDate);
    printf("Discharged   : %s\n", p->dischargeDate);
    printf("Room         : %d\n", p->roomNumber);
    printf("Days         : %d\n", p->daysAdmitted);
    printf("------------------------------\n");
    printf("Room         : Tk. %.2f\n", p->roomCharges);
    printf("Doctor       : Tk. %.2f\n", p->doctorFee);
    printf("Medicine     : Tk. %.2f\n", p->medicineCharges);
    printf("Lab          : Tk. %.2f\n", p->labCharges);
    printf("Discount     : Tk. %.2f\n", p->discount);
    printf("------------------------------\n");
    printf("TOTAL BILL   : Tk. %.2f\n", p->totalBill);
    printf("Status       : Discharged\n");
    printf("******************************\n");
}

void billingMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Billing --\n");
        printf("1. View bill\n");
        printf("2. Apply discount\n");
        printf("3. Discharge patient\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) viewPatientBill();
        else if (ch == 2) applyDiscount();
        else if (ch == 3) dischargePatient();
        else if (ch == 4) return;
        else printf("Invalid.\n");
    }
}
