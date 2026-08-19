#include "fee.h"
#include "student.h"
#include "utils.h"
#include "file_ops.h"

void collectFee(void) {
    header("COLLECT FEE");
    int sid;
    printf("Student ID: "); readInt(&sid);
    Student *s = findStudentById(sid);
    if (!s) { printf("Student not found.\n"); pauseScreen(); return; }

    printf("Student: %s | Room: %d\n", s->name, s->roomNo);
    printf("Total fee: %.2f | Paid: %.2f | Due: %.2f\n",
           s->feeTotal, s->feePaid, s->feeTotal - s->feePaid);

    if (s->feePaid >= s->feeTotal) {
        printf("No dues. Already fully paid.\n");
        pauseScreen();
        return;
    }

    float amt;
    printf("Amount being paid: ");
    readFloat(&amt);
    if (amt <= 0) {
        printf("Invalid amount.\n");
        pauseScreen();
        return;
    }
    if (s->feePaid + amt > s->feeTotal) {
        printf("Amount exceeds total fee. Capping at %.2f.\n",
               s->feeTotal - s->feePaid);
        amt = s->feeTotal - s->feePaid;
    }
    s->feePaid += amt;
    saveStudents();
    printf("Payment accepted. New paid: %.2f | Due: %.2f\n",
           s->feePaid, s->feeTotal - s->feePaid);
    pauseScreen();
}

void viewDueList(void) {
    header("STUDENTS WITH DUES");
    printf("%-6s %-20s %-8s %-10s %-10s\n",
           "ID", "Name", "Room", "Paid", "Due");
    printLine('-', 60);
    int n = 0;
    float totalDue = 0.0f;
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].active) continue;
        Student *s = &students[i];
        float due = s->feeTotal - s->feePaid;
        if (due > 0.01f) {
            printf("%-6d %-20s %-8d %-10.2f %-10.2f\n",
                   s->id, s->name, s->roomNo, s->feePaid, due);
            totalDue += due;
            n++;
        }
    }
    if (n == 0) printf("All students have cleared their dues.\n");
    else printf("\n%d student(s) with dues. Total due = %.2f\n", n, totalDue);
    pauseScreen();
}

void viewAllFees(void) {
    header("ALL FEE STATUS");
    printf("%-6s %-20s %-10s %-10s %-12s\n",
           "ID", "Name", "Total", "Paid", "Status");
    printLine('-', 60);
    float totalCollected = 0, totalExpected = 0;
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].active) continue;
        Student *s = &students[i];
        const char *status = (s->feePaid >= s->feeTotal) ? "PAID" : "DUE";
        printf("%-6d %-20s %-10.0f %-10.2f %-12s\n",
               s->id, s->name, s->feeTotal, s->feePaid, status);
        totalCollected += s->feePaid;
        totalExpected  += s->feeTotal;
    }
    printf("\nTotal expected: %.2f | Total collected: %.2f | Outstanding: %.2f\n",
           totalExpected, totalCollected, totalExpected - totalCollected);
    pauseScreen();
}

void setTotalFee(void) {
    header("SET/UPDATE TOTAL FEE");
    int sid;
    printf("Student ID: "); readInt(&sid);
    Student *s = findStudentById(sid);
    if (!s) { printf("Student not found.\n"); pauseScreen(); return; }

    float newTotal;
    printf("Current total: %.2f. Enter new total: ", s->feeTotal);
    readFloat(&newTotal);
    if (newTotal < 0) newTotal = 0;
    if (newTotal < s->feePaid) {
        printf("New total is less than amount already paid. Adjusting paid to %.2f.\n",
               newTotal);
        s->feePaid = newTotal;
    }
    s->feeTotal = newTotal;
    saveStudents();
    printf("Total fee updated.\n");
    pauseScreen();
}

void feeMenu(void) {
    int ch;
    do {
        clearScreen();
        header("FEE MANAGEMENT");
        printf("  1. Collect fee payment\n");
        printf("  2. View students with dues\n");
        printf("  3. View all fee status\n");
        printf("  4. Set/update total fee\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: collectFee(); break;
            case 2: viewDueList(); break;
            case 3: viewAllFees(); break;
            case 4: setTotalFee(); break;
        }
    } while (ch != 0);
}