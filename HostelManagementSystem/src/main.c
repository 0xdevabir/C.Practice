#include "structs.h"
#include "utils.h"
#include "file_ops.h"
#include "student.h"
#include "room.h"
#include "fee.h"
#include "complaint.h"
#include "visitor.h"
#include "report.h"

static int login(void) {
    char pass[64];
    printf("\n  ====== HOSTEL MANAGEMENT SYSTEM ======\n");
    printf("  Admin password: ");
    readString(pass, sizeof(pass));
    if (strcmp(pass, PASSWORD) == 0) {
        printf("\n  Login successful.\n");
        pauseScreen();
        return 1;
    }
    printf("\n  Wrong password.\n");
    return 0;
}

int main(void) {
    loadAll();

    if (!login()) return 0;

    int ch;
    do {
        clearScreen();
        header("HOSTEL MANAGEMENT SYSTEM - MAIN MENU");
        printf("  1. Student management\n");
        printf("  2. Room management\n");
        printf("  3. Fee management\n");
        printf("  4. Complaint management\n");
        printf("  5. Visitor tracking\n");
        printf("  6. Reports\n");
        printf("  7. Save all data\n");
        printf("  0. Exit\n");
        printf("Choice: ");
        readInt(&ch);

        switch (ch) {
            case 1: studentMenu();  break;
            case 2: roomMenu();     break;
            case 3: feeMenu();      break;
            case 4: complaintMenu();break;
            case 5: visitorMenu();  break;
            case 6: reportMenu();   break;
            case 7:
                saveAll();
                printf("All data saved.\n");
                pauseScreen();
                break;
            case 0:
                saveAll();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                pauseScreen();
        }
    } while (ch != 0);

    return 0;
}