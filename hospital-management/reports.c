#include "hospital.h"

void hospitalSummary(void) {
    int admitted = 0, discharged = 0, emergency = 0;
    int availDoc = 0, busyDoc = 0;
    int freeRoom = 0, usedRoom = 0, maint = 0;
    double revenue = 0;

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].status, "Discharged") == 0) {
            discharged++;
            revenue += patients[i].totalBill;
        } else if (strcmp(patients[i].status, "Emergency") == 0) {
            emergency++;
            admitted++;
        } else {
            admitted++;
        }
    }
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].available) availDoc++;
        else busyDoc++;
    }
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].status, "Maintenance") == 0) maint++;
        else if (rooms[i].occupied) usedRoom++;
        else freeRoom++;
    }

    printf("\n========================================\n");
    printf("HOSPITAL SUMMARY\n");
    printf("========================================\n");
    printf("Total Patients        : %d\n", patientCount);
    printf("Currently Admitted    : %d\n", admitted);
    printf("  (Emergency cases)   : %d\n", emergency);
    printf("Discharged            : %d\n", discharged);
    printf("Doctors Available     : %d\n", availDoc);
    printf("Doctors Busy          : %d\n", busyDoc);
    printf("Rooms Free            : %d\n", freeRoom);
    printf("Rooms Occupied        : %d\n", usedRoom);
    printf("Rooms Maintenance     : %d\n", maint);
    printf("Appointments          : %d\n", apptCount);
    printf("Medicine SKUs         : %d\n", medCount);
    printf("Lab Orders            : %d\n", labOrderCount);
    printf("Total Revenue         : Tk. %.2f\n", revenue);
    printf("========================================\n");
}

void revenueReport(void) {
    double room = 0, doc = 0, med = 0, lab = 0, disc = 0, total = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].status, "Discharged") != 0) continue;
        room += patients[i].roomCharges;
        doc += patients[i].doctorFee;
        med += patients[i].medicineCharges;
        lab += patients[i].labCharges;
        disc += patients[i].discount;
        total += patients[i].totalBill;
    }
    printf("\n=== REVENUE BY CATEGORY (Discharged) ===\n");
    printf("Room Charges : Tk. %.2f\n", room);
    printf("Doctor Fees  : Tk. %.2f\n", doc);
    printf("Pharmacy     : Tk. %.2f\n", med);
    printf("Laboratory   : Tk. %.2f\n", lab);
    printf("Discounts    : Tk. %.2f\n", disc);
    printf("NET REVENUE  : Tk. %.2f\n", total);
}

void occupancyReport(void) {
    int gen = 0, priv = 0, icu = 0, er = 0;
    int genU = 0, privU = 0, icuU = 0, erU = 0;
    for (int i = 0; i < roomCount; i++) {
        if (strcasecmp(rooms[i].type, "General") == 0) {
            gen++; if (rooms[i].occupied) genU++;
        } else if (strcasecmp(rooms[i].type, "Private") == 0) {
            priv++; if (rooms[i].occupied) privU++;
        } else if (strcasecmp(rooms[i].type, "ICU") == 0) {
            icu++; if (rooms[i].occupied) icuU++;
        } else if (strcasecmp(rooms[i].type, "Emergency") == 0) {
            er++; if (rooms[i].occupied) erU++;
        }
    }
    printf("\n=== ROOM OCCUPANCY ===\n");
    printf("General   : %d / %d\n", genU, gen);
    printf("Private   : %d / %d\n", privU, priv);
    printf("ICU       : %d / %d\n", icuU, icu);
    printf("Emergency : %d / %d\n", erU, er);
    if (roomCount > 0) {
        int used = genU + privU + icuU + erU;
        printf("Overall   : %.1f%%\n", 100.0 * used / roomCount);
    }
}

void emergencyReport(void) {
    printf("\n=== ACTIVE EMERGENCY CASES ===\n");
    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (!patients[i].isEmergency) continue;
        if (strcmp(patients[i].status, "Discharged") == 0) continue;
        printf("ID %d | %s | Room %d | Doctor %d | %s | Admitted %s\n",
               patients[i].id, patients[i].name, patients[i].roomNumber,
               patients[i].doctorId, patients[i].condition, patients[i].admitDate);
        found = 1;
    }
    if (!found) printf("No active emergencies.\n");
}

void reportsMenu(void) {
    int c;
    while (1) {
        printf("\n=== REPORTS ===\n");
        printf("1. Hospital Summary\n");
        printf("2. Revenue Report\n");
        printf("3. Occupancy Report\n");
        printf("4. Emergency Report\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: hospitalSummary(); break;
            case 2: revenueReport(); break;
            case 3: occupancyReport(); break;
            case 4: emergencyReport(); break;
            case 5: return;
            default: printf("Invalid.\n");
        }
    }
}
