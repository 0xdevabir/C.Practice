#include "complaint.h"
#include "student.h"
#include "utils.h"
#include "file_ops.h"

void logComplaint(void) {
    header("LOG NEW COMPLAINT");
    if (complaintCount >= MAX_COMPLAINTS) {
        printf("Complaint storage full.\n");
        pauseScreen();
        return;
    }
    int sid;
    printf("Student ID: "); readInt(&sid);
    if (!findStudentById(sid)) {
        printf("Student not found.\n");
        pauseScreen();
        return;
    }

    Complaint c;
    c.id = nextComplaintId++;
    c.studentId = sid;
    c.active = 1;
    strncpy(c.status, "OPEN", sizeof(c.status) - 1);
    currentDate(c.date);

    printf("Category (Mess / Maintenance / Hygiene / Security / Other): ");
    readString(c.category, sizeof(c.category));
    if (strlen(c.category) == 0) strncpy(c.category, "Other", sizeof(c.category) - 1);

    printf("Describe the issue: ");
    readString(c.text, sizeof(c.text));

    complaints[complaintCount++] = c;
    saveComplaints();
    saveCounters();
    printf("Complaint logged with ID %d on %s.\n", c.id, c.date);
    pauseScreen();
}

void viewComplaints(void) {
    header("COMPLAINTS LOG");
    printf("Filter: 1 = All, 2 = Open only, 3 = By Student ID: ");
    int f; readInt(&f);
    int sidQ = 0;
    if (f == 3) { printf("Student ID: "); readInt(&sidQ); }

    printf("\n%-5s %-8s %-12s %-12s %-11s\n",
           "ID", "StudID", "Category", "Date", "Status");
    printLine('-', 55);
    int n = 0;
    for (int i = 0; i < complaintCount; i++) {
        Complaint *c = &complaints[i];
        if (!c->active) continue;
        if (f == 2 && strcmp(c->status, "RESOLVED") == 0) continue;
        if (f == 3 && c->studentId != sidQ) continue;
        printf("%-5d %-8d %-12s %-12s %-11s\n",
               c->id, c->studentId, c->category, c->date, c->status);
        n++;
    }
    if (n == 0) printf("No complaints match.\n");
    pauseScreen();
}

void updateComplaintStatus(void) {
    header("UPDATE COMPLAINT STATUS");
    printf("Complaint ID: ");
    int id; readInt(&id);
    int found = 0;
    for (int i = 0; i < complaintCount; i++) {
        if (!complaints[i].active) continue;
        if (complaints[i].id == id) {
            printf("Current status: %s\n", complaints[i].status);
            printf("New status (1=IN_PROGRESS, 2=RESOLVED, 3=REOPEN): ");
            int ch; readInt(&ch);
            if (ch == 1) strncpy(complaints[i].status, "IN_PROGRESS", sizeof(complaints[i].status) - 1);
            else if (ch == 2) strncpy(complaints[i].status, "RESOLVED", sizeof(complaints[i].status) - 1);
            else if (ch == 3) strncpy(complaints[i].status, "OPEN", sizeof(complaints[i].status) - 1);
            saveComplaints();
            printf("Status updated.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Complaint not found.\n");
    pauseScreen();
}

void complaintMenu(void) {
    int ch;
    do {
        clearScreen();
        header("COMPLAINT MANAGEMENT");
        printf("  1. Log new complaint\n");
        printf("  2. View complaints\n");
        printf("  3. Update complaint status\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: logComplaint(); break;
            case 2: viewComplaints(); break;
            case 3: updateComplaintStatus(); break;
        }
    } while (ch != 0);
}