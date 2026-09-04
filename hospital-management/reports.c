#include "hospital.h"

void hospitalSummary(void) {
    int i;
    int admitted = 0, discharged = 0, emergency = 0;
    int availDoc = 0, busyDoc = 0;
    int freeRoom = 0, usedRoom = 0, maint = 0;
    double revenue = 0;

    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].status, "Discharged") == 0) {
            discharged++;
            revenue += patients[i].totalBill;
        } else {
            admitted++;
            if (patients[i].isEmergency || strcmp(patients[i].status, "Emergency") == 0)
                emergency++;
        }
    }

    for (i = 0; i < doctorCount; i++) {
        if (doctors[i].available)
            availDoc++;
        else
            busyDoc++;
    }

    for (i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].status, "Maintenance") == 0)
            maint++;
        else if (rooms[i].occupied)
            usedRoom++;
        else
            freeRoom++;
    }

    printf("\n--- Hospital summary ---\n");
    printf("Patients total     : %d\n", patientCount);
    printf("Still admitted     : %d\n", admitted);
    printf("Emergency cases    : %d\n", emergency);
    printf("Discharged         : %d\n", discharged);
    printf("Doctors free/busy  : %d / %d\n", availDoc, busyDoc);
    printf("Rooms free/used    : %d / %d\n", freeRoom, usedRoom);
    printf("Rooms maintenance  : %d\n", maint);
    printf("Appointments       : %d\n", apptCount);
    printf("Medicines in list  : %d\n", medCount);
    printf("Lab orders         : %d\n", labOrderCount);
    printf("Revenue (discharged): %.2f Tk\n", revenue);
    printf("------------------------\n");
}

void revenueReport(void) {
    int i;
    double room = 0, doc = 0, med = 0, lab = 0, disc = 0, total = 0;

    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].status, "Discharged") != 0)
            continue;
        room += patients[i].roomCharges;
        doc += patients[i].doctorFee;
        med += patients[i].medicineCharges;
        lab += patients[i].labCharges;
        disc += patients[i].discount;
        total += patients[i].totalBill;
    }

    printf("\nRevenue from discharged patients:\n");
    printf("Rooms     %.2f\n", room);
    printf("Doctors   %.2f\n", doc);
    printf("Pharmacy  %.2f\n", med);
    printf("Lab       %.2f\n", lab);
    printf("Discounts -%.2f\n", disc);
    printf("Net       %.2f Tk\n", total);
}

void occupancyReport(void) {
    int i;
    int gen = 0, priv = 0, icu = 0, er = 0;
    int genU = 0, privU = 0, icuU = 0, erU = 0;
    int used;

    for (i = 0; i < roomCount; i++) {
        if (strcasecmp(rooms[i].type, "General") == 0) {
            gen++;
            if (rooms[i].occupied) genU++;
        } else if (strcasecmp(rooms[i].type, "Private") == 0) {
            priv++;
            if (rooms[i].occupied) privU++;
        } else if (strcasecmp(rooms[i].type, "ICU") == 0) {
            icu++;
            if (rooms[i].occupied) icuU++;
        } else if (strcasecmp(rooms[i].type, "Emergency") == 0) {
            er++;
            if (rooms[i].occupied) erU++;
        }
    }

    printf("\nOccupancy:\n");
    printf("General   %d/%d\n", genU, gen);
    printf("Private   %d/%d\n", privU, priv);
    printf("ICU       %d/%d\n", icuU, icu);
    printf("Emergency %d/%d\n", erU, er);
    if (roomCount > 0) {
        used = genU + privU + icuU + erU;
        printf("Overall   %.1f%%\n", 100.0 * used / roomCount);
    }
}

void emergencyReport(void) {
    int i, found = 0;

    printf("\nActive emergency patients:\n");
    for (i = 0; i < patientCount; i++) {
        if (!patients[i].isEmergency)
            continue;
        if (strcmp(patients[i].status, "Discharged") == 0)
            continue;
        printf("%d %s room=%d doctor=%d | %s | since %s\n",
               patients[i].id, patients[i].name, patients[i].roomNumber,
               patients[i].doctorId, patients[i].condition, patients[i].admitDate);
        found = 1;
    }
    if (!found)
        printf("None right now.\n");
}

void reportsMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Reports --\n");
        printf("1. Summary\n");
        printf("2. Revenue\n");
        printf("3. Occupancy\n");
        printf("4. Emergencies\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) hospitalSummary();
        else if (ch == 2) revenueReport();
        else if (ch == 3) occupancyReport();
        else if (ch == 4) emergencyReport();
        else if (ch == 5) return;
        else printf("Invalid.\n");
    }
}
