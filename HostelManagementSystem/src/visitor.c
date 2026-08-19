#include "visitor.h"
#include "student.h"
#include "utils.h"
#include "file_ops.h"

void logVisitorIn(void) {
    header("LOG VISITOR IN");
    if (visitorCount >= MAX_VISITOR) {
        printf("Visitor storage full.\n");
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

    Visitor v;
    v.id = nextVisitorId++;
    v.studentId = sid;
    v.active = 1;
    currentDate(v.date);
    currentTime(v.inTime);
    strncpy(v.outTime, "-", sizeof(v.outTime) - 1);

    printf("Visitor name: "); readString(v.visitorName, MAX_NAME);
    printf("Relation: ");    readString(v.relation, sizeof(v.relation));
    printf("Phone: ");       readString(v.phone, MAX_PHONE);

    if (strlen(v.visitorName) == 0) {
        printf("Visitor name required.\n");
        nextVisitorId--;
        pauseScreen();
        return;
    }

    visitors[visitorCount++] = v;
    saveVisitors();
    saveCounters();
    printf("Visitor logged in at %s on %s.\n", v.inTime, v.date);
    pauseScreen();
}

void logVisitorOut(void) {
    header("LOG VISITOR OUT");
    printf("Visitor ID to mark OUT: ");
    int id; readInt(&id);
    int found = 0;
    for (int i = 0; i < visitorCount; i++) {
        if (!visitors[i].active) continue;
        if (visitors[i].id == id) {
            if (strcmp(visitors[i].outTime, "-") != 0) {
                printf("Visitor already checked out at %s.\n", visitors[i].outTime);
            } else {
                currentTime(visitors[i].outTime);
                saveVisitors();
                printf("Visitor checked out at %s.\n", visitors[i].outTime);
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("Visitor not found.\n");
    pauseScreen();
}

void viewVisitors(void) {
    header("VISITOR LOG");
    printf("Filter: 1 = All, 2 = Inside only, 3 = By Student ID: ");
    int f; readInt(&f);
    int sidQ = 0;
    if (f == 3) { printf("Student ID: "); readInt(&sidQ); }

    printf("\n%-5s %-8s %-18s %-12s %-8s %-8s %-12s\n",
           "ID", "StudID", "Name", "Relation", "In", "Out", "Date");
    printLine('-', 80);
    int n = 0;
    for (int i = 0; i < visitorCount; i++) {
        Visitor *v = &visitors[i];
        if (!v->active) continue;
        if (f == 2 && strcmp(v->outTime, "-") != 0) continue;
        if (f == 3 && v->studentId != sidQ) continue;
        printf("%-5d %-8d %-18s %-12s %-8s %-8s %-12s\n",
               v->id, v->studentId, v->visitorName, v->relation,
               v->inTime, v->outTime, v->date);
        n++;
    }
    if (n == 0) printf("No visitors match.\n");
    pauseScreen();
}

void visitorMenu(void) {
    int ch;
    do {
        clearScreen();
        header("VISITOR TRACKING");
        printf("  1. Log visitor IN\n");
        printf("  2. Log visitor OUT\n");
        printf("  3. View visitor log\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: logVisitorIn(); break;
            case 2: logVisitorOut(); break;
            case 3: viewVisitors(); break;
        }
    } while (ch != 0);
}