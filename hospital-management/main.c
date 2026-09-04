#include "hospital.h"

static void dataMenu(void) {
    int c;
    while (1) {
        printf("\n=== DATA ===\n");
        printf("1. Save All Data\n");
        printf("2. Load Saved Data\n");
        printf("3. Reset to Fresh Seed Data\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1:
                if (saveAll()) printf("Saved to data/ folder.\n");
                else printf("Save failed.\n");
                break;
            case 2:
                if (loadAll()) printf("Loaded from data/ folder.\n");
                else printf("Load failed (no saved data?).\n");
                break;
            case 3:
                seedAll();
                break;
            case 4:
                return;
            default:
                printf("Invalid.\n");
        }
    }
}

static void printBanner(void) {
    printf("\n");
    printf("################################################\n");
    printf("#   CITY CARE HOSPITAL MANAGEMENT SYSTEM      #\n");
    printf("#   CSE115 Advanced Hospital Console App      #\n");
    printf("################################################\n");
}

int main(void) {
    ensureDataDir();
    if (!loadAll()) {
        seedAll();
        printf("Starting with seeded hospital data.\n");
    } else {
        printf("Previous session data loaded.\n");
    }

    int choice;
    while (1) {
        printBanner();
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Room Management\n");
        printf("4. Appointments\n");
        printf("5. Pharmacy\n");
        printf("6. Laboratory\n");
        printf("7. Billing & Discharge\n");
        printf("8. Reports\n");
        printf("9. Save / Load / Reset Data\n");
        printf("0. Exit (auto-save)\n");
        if (!readInt("\nEnter choice: ", &choice)) {
            printf("Invalid input.\n");
            continue;
        }
        switch (choice) {
            case 1: patientMenu(); break;
            case 2: doctorMenu(); break;
            case 3: roomMenu(); break;
            case 4: appointmentMenu(); break;
            case 5: pharmacyMenu(); break;
            case 6: labMenu(); break;
            case 7: billingMenu(); break;
            case 8: reportsMenu(); break;
            case 9: dataMenu(); break;
            case 0:
                if (saveAll()) printf("Data saved. Goodbye!\n");
                else printf("Exit without successful save. Goodbye!\n");
                return 0;
            default:
                printf("Invalid menu choice.\n");
        }
    }
}
