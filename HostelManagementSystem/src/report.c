#include "report.h"
#include "utils.h"
#include "file_ops.h"

void vacancyReport(void) {
    header("VACANCY REPORT");
    int totalCap = 0, totalOcc = 0, fullRooms = 0, empty = 0;
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].active) continue;
        totalCap += rooms[i].capacity;
        totalOcc += rooms[i].occupied;
        if (rooms[i].occupied >= rooms[i].capacity) fullRooms++;
        if (rooms[i].occupied == 0) empty++;
    }
    int free = totalCap - totalOcc;
    float pct = (totalCap > 0) ? (100.0f * totalOcc / totalCap) : 0.0f;

    printf("Total rooms:        %d\n", roomCount);
    printf("Total capacity:     %d beds\n", totalCap);
    printf("Currently occupied: %d beds\n", totalOcc);
    printf("Available beds:     %d\n", free);
    printf("Occupancy rate:     %.2f%%\n", pct);
    printf("Fully occupied:     %d rooms\n", fullRooms);
    printf("Completely empty:   %d rooms\n", empty);
    pauseScreen();
}

void feeReport(void) {
    header("FEE REPORT");
    float totalExpected = 0, totalCollected = 0;
    int paidCount = 0, dueCount = 0;
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].active) continue;
        totalExpected  += students[i].feeTotal;
        totalCollected += students[i].feePaid;
        if (students[i].feePaid >= students[i].feeTotal) paidCount++;
        else dueCount++;
    }
    printf("Total students: %d | Fully paid: %d | With dues: %d\n",
           paidCount + dueCount, paidCount, dueCount);
    printf("Total expected: %.2f\n", totalExpected);
    printf("Total collected: %.2f\n", totalCollected);
    printf("Outstanding: %.2f\n", totalExpected - totalCollected);
    if (totalExpected > 0) {
        printf("Collection rate: %.2f%%\n", 100.0f * totalCollected / totalExpected);
    }
    pauseScreen();
}

void complaintReport(void) {
    header("COMPLAINT REPORT");
    int open = 0, inprog = 0, resolved = 0;
    /* category frequency */
    int catMess = 0, catMaint = 0, catHyg = 0, catSec = 0, catOther = 0;

    for (int i = 0; i < complaintCount; i++) {
        if (!complaints[i].active) continue;
        if (strcmp(complaints[i].status, "OPEN") == 0) open++;
        else if (strcmp(complaints[i].status, "IN_PROGRESS") == 0) inprog++;
        else if (strcmp(complaints[i].status, "RESOLVED") == 0) resolved++;

        char cat[30];
        strncpy(cat, complaints[i].category, sizeof(cat) - 1);
        cat[sizeof(cat) - 1] = '\0';
        for (int k = 0; cat[k]; k++) cat[k] = toupper((unsigned char)cat[k]);

        if (strcmp(cat, "MESS") == 0) catMess++;
        else if (strcmp(cat, "MAINTENANCE") == 0) catMaint++;
        else if (strcmp(cat, "HYGIENE") == 0) catHyg++;
        else if (strcmp(cat, "SECURITY") == 0) catSec++;
        else catOther++;
    }
    printf("Total complaints: %d\n", open + inprog + resolved);
    printf("  Open:           %d\n", open);
    printf("  In progress:    %d\n", inprog);
    printf("  Resolved:       %d\n", resolved);
    printf("\nBy category:\n");
    printf("  Mess:         %d\n", catMess);
    printf("  Maintenance:  %d\n", catMaint);
    printf("  Hygiene:      %d\n", catHyg);
    printf("  Security:     %d\n", catSec);
    printf("  Other:        %d\n", catOther);
    pauseScreen();
}

void dashboardReport(void) {
    header("DASHBOARD SUMMARY");
    int activeStudent = 0;
    for (int i = 0; i < studentCount; i++)
        if (students[i].active) activeStudent++;

    int totalCap = 0, totalOcc = 0;
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].active) continue;
        totalCap += rooms[i].capacity;
        totalOcc += rooms[i].occupied;
    }

    int openC = 0;
    for (int i = 0; i < complaintCount; i++)
        if (complaints[i].active && strcmp(complaints[i].status, "RESOLVED") != 0)
            openC++;

    printf("Active students: %d\n", activeStudent);
    printf("Occupancy:       %d / %d  (%.1f%%)\n",
           totalOcc, totalCap,
           (totalCap > 0) ? (100.0f * totalOcc / totalCap) : 0.0f);
    printf("Open complaints: %d\n", openC);
    pauseScreen();
}

void reportMenu(void) {
    int ch;
    do {
        clearScreen();
        header("REPORTS");
        printf("  1. Dashboard summary\n");
        printf("  2. Vacancy report\n");
        printf("  3. Fee report\n");
        printf("  4. Complaint report\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: dashboardReport(); break;
            case 2: vacancyReport(); break;
            case 3: feeReport(); break;
            case 4: complaintReport(); break;
        }
    } while (ch != 0);
}