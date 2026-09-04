#include "hospital.h"

static void recalcBill(Patient *p) {
    if (p->roomNumber > 0 && p->daysAdmitted > 0) {
        int ri = findRoomIndex(p->roomNumber);
        if (ri >= 0) {
            p->roomCharges = p->daysAdmitted * rooms[ri].dailyRate;
        }
    }
    p->totalBill = p->roomCharges + p->doctorFee + p->medicineCharges +
                   p->labCharges - p->discount;
    if (p->totalBill < 0) p->totalBill = 0;
}

void viewPatientBill(void) {
    int id;
    if (!readInt("Patient ID: ", &id)) return;
    int pi = findPatientIndex(id);
    if (pi < 0) { printf("Not found.\n"); return; }
    Patient *p = &patients[pi];
    recalcBill(p);

    printf("\n========================================\n");
    printf("ITEMIZED BILL — Patient %d\n", p->id);
    printf("========================================\n");
    printf("Name           : %s\n", p->name);
    printf("Status         : %s\n", p->status);
    printf("Room           : %d\n", p->roomNumber);
    printf("Days Admitted  : %d\n", p->daysAdmitted);
    printf("----------------------------------------\n");
    printf("Room Charges   : Tk. %.2f\n", p->roomCharges);
    printf("Doctor Fee     : Tk. %.2f\n", p->doctorFee);
    printf("Medicines      : Tk. %.2f\n", p->medicineCharges);
    printf("Lab Tests      : Tk. %.2f\n", p->labCharges);
    printf("Discount       : Tk. %.2f\n", p->discount);
    printf("----------------------------------------\n");
    printf("TOTAL BILL     : Tk. %.2f\n", p->totalBill);
    printf("========================================\n");

    printf("\nMedicines dispensed:\n");
    int any = 0;
    for (int i = 0; i < prescCount; i++) {
        if (prescriptions[i].patientId != id) continue;
        int mi = findMedIndex(prescriptions[i].medicineId);
        printf("  - %s x%d = %.0f (%s)\n",
               mi >= 0 ? medicines[mi].name : "?",
               prescriptions[i].quantity, prescriptions[i].amount,
               prescriptions[i].date);
        any = 1;
    }
    if (!any) printf("  (none)\n");

    printf("\nLab orders:\n");
    any = 0;
    for (int i = 0; i < labOrderCount; i++) {
        if (labOrders[i].patientId != id) continue;
        int li = findLabIndex(labOrders[i].labTestId);
        printf("  - %s [%s] = %.0f (%s)\n",
               li >= 0 ? labTests[li].name : "?",
               labOrders[i].status, labOrders[i].amount, labOrders[i].date);
        any = 1;
    }
    if (!any) printf("  (none)\n");
}

void applyDiscount(void) {
    int id;
    double pct;
    if (!readInt("Patient ID: ", &id)) return;
    int pi = findPatientIndex(id);
    if (pi < 0) { printf("Not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Already discharged.\n");
        return;
    }
    if (!readDouble("Discount percent (0-100): ", &pct) || pct < 0 || pct > 100) {
        printf("Invalid percent.\n");
        return;
    }
    recalcBill(&patients[pi]);
    double beforeDisc = patients[pi].roomCharges + patients[pi].doctorFee +
                        patients[pi].medicineCharges + patients[pi].labCharges;
    patients[pi].discount = beforeDisc * pct / 100.0;
    recalcBill(&patients[pi]);
    printf("Discount Tk. %.2f applied. New total Tk. %.2f\n",
           patients[pi].discount, patients[pi].totalBill);
}

void dischargePatient(void) {
    int id;
    if (!readInt("Patient ID: ", &id)) return;
    int pi = findPatientIndex(id);
    if (pi < 0) { printf("Not found.\n"); return; }
    Patient *p = &patients[pi];
    if (strcmp(p->status, "Discharged") == 0) {
        printf("Already discharged.\n");
        return;
    }
    if (p->doctorId < 0) {
        printf("Assign a doctor before discharge.\n");
        return;
    }
    if (p->daysAdmitted < 1) p->daysAdmitted = 1;
    recalcBill(p);

    if (p->roomNumber > 0) {
        int ri = findRoomIndex(p->roomNumber);
        if (ri >= 0) {
            rooms[ri].occupied = 0;
            rooms[ri].patientId = -1;
            strcpy(rooms[ri].status, "Available");
        }
    }
    releaseDoctorFromPatient(pi);
    todayDate(p->dischargeDate, MAX_DATE);
    strcpy(p->status, "Discharged");

    printf("\n========================================\n");
    printf("HOSPITAL DISCHARGE RECEIPT\n");
    printf("========================================\n");
    printf("Patient ID     : %d\n", p->id);
    printf("Patient Name   : %s\n", p->name);
    printf("Admit Date     : %s\n", p->admitDate);
    printf("Discharge Date : %s\n", p->dischargeDate);
    printf("Room Number    : %d\n", p->roomNumber);
    printf("Days Admitted  : %d\n", p->daysAdmitted);
    printf("----------------------------------------\n");
    printf("Room Charge    : Tk. %.2f\n", p->roomCharges);
    printf("Doctor Fee     : Tk. %.2f\n", p->doctorFee);
    printf("Medicines      : Tk. %.2f\n", p->medicineCharges);
    printf("Lab Tests      : Tk. %.2f\n", p->labCharges);
    printf("Discount       : Tk. %.2f\n", p->discount);
    printf("----------------------------------------\n");
    printf("TOTAL BILL     : Tk. %.2f\n", p->totalBill);
    printf("Status         : Discharged\n");
    printf("========================================\n");
}

void collectPartialPayment(void) {
    printf("Note: This demo tracks final bill on discharge.\n");
    viewPatientBill();
}

void billingMenu(void) {
    int c;
    while (1) {
        printf("\n=== BILLING & DISCHARGE ===\n");
        printf("1. View Itemized Bill\n");
        printf("2. Apply Discount\n");
        printf("3. Discharge Patient\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: viewPatientBill(); break;
            case 2: applyDiscount(); break;
            case 3: dischargePatient(); break;
            case 4: return;
            default: printf("Invalid.\n");
        }
    }
}
