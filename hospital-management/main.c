#include "hospital.h"

/* main menu + save/load stuff */

static void dataMenu(void) {
    int ch;

    while (1) {
        printf("\n-- Data --\n");
        printf("1. Save\n");
        printf("2. Load\n");
        printf("3. Reset to defaults (wipes patients etc)\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;

        if (ch == 1) {
            if (saveAll())
                printf("Saved in data/ folder.\n");
            else
                printf("Save failed :(\n");
        } else if (ch == 2) {
            if (loadAll())
                printf("Loaded ok.\n");
            else
                printf("Couldnt load. Maybe nothing saved yet?\n");
        } else if (ch == 3) {
            seedAll();
        } else if (ch == 4) {
            return;
        } else {
            printf("Invalid.\n");
        }
    }
}

int main(void) {
    int choice;

    ensureDataDir();

    /* try old data first, otherwise start fresh */
    if (loadAll()) {
        printf("Loaded previous data.\n");
    } else {
        seedAll();
        printf("Starting with sample hospital data.\n");
    }

    while (1) {
        printf("\n");
        printf("================================\n");
        printf("  Hospital Management System\n");
        printf("================================\n");
        printf("1. Patients\n");
        printf("2. Doctors\n");
        printf("3. Rooms\n");
        printf("4. Appointments\n");
        printf("5. Pharmacy\n");
        printf("6. Laboratory\n");
        printf("7. Billing / Discharge\n");
        printf("8. Reports\n");
        printf("9. Save / Load / Reset\n");
        printf("0. Exit\n");

        if (!readInt("Enter choice: ", &choice)) {
            printf("Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                patientMenu();
                break;
            case 2:
                doctorMenu();
                break;
            case 3:
                roomMenu();
                break;
            case 4:
                appointmentMenu();
                break;
            case 5:
                pharmacyMenu();
                break;
            case 6:
                labMenu();
                break;
            case 7:
                billingMenu();
                break;
            case 8:
                reportsMenu();
                break;
            case 9:
                dataMenu();
                break;
            case 0:
                if (saveAll())
                    printf("Saved. Bye!\n");
                else
                    printf("Exit (save failed). Bye!\n");
                return 0;
            default:
                printf("Wrong choice, try again.\n");
        }
    }

    return 0;
}
