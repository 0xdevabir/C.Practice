#include "student.h"
#include "utils.h"
#include "file_ops.h"

Student* findStudentById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active && students[i].id == id) return &students[i];
    }
    return NULL;
}

void addStudent(void) {
    header("ADD NEW STUDENT");
    if (studentCount >= MAX_STUDENTS) {
        printf("Student storage full!\n");
        pauseScreen();
        return;
    }

    Student s;
    s.id = nextStudentId++;
    s.active = 1;
    s.roomNo = 0;
    s.feePaid = 0.0f;

    printf("Student ID (auto): %d\n", s.id);
    printf("Name: ");       readString(s.name, MAX_NAME);
    printf("Phone: ");      readString(s.phone, MAX_PHONE);
    printf("Department: "); readString(s.department, MAX_DEPT);
    printf("Age: ");        readInt(&s.age);
    printf("Total Fee (this term): "); readFloat(&s.feeTotal);

    if (strlen(s.name) == 0) {
        printf("Name cannot be empty. Aborting.\n");
        nextStudentId--;
        pauseScreen();
        return;
    }

    students[studentCount++] = s;
    saveStudents();
    saveCounters();
    printf("\nStudent %s added with ID %d.\n", s.name, s.id);
    pauseScreen();
}

void viewAllStudents(void) {
    header("ALL STUDENTS");
    printf("%-6s %-20s %-13s %-12s %-5s %-8s %-10s\n",
           "ID", "Name", "Phone", "Dept", "Age", "Room", "Fee");
    printLine('-', 80);
    int shown = 0;
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].active) continue;
        Student *s = &students[i];
        printf("%-6d %-20s %-13s %-12s %-5d %-8d %.0f/%.0f\n",
               s->id, s->name, s->phone, s->department, s->age,
               s->roomNo, s->feePaid, s->feeTotal);
        shown++;
    }
    if (shown == 0) printf("No students found.\n");
    printf("\nTotal active students: %d\n", shown);
    pauseScreen();
}

void searchStudent(void) {
    header("SEARCH STUDENT");
    printf("Search by:\n");
    printf("  1. ID\n");
    printf("  2. Name\n");
    printf("Choice: ");
    int ch; readInt(&ch);

    if (ch == 1) {
        printf("Enter ID: ");
        int id; readInt(&id);
        Student *s = findStudentById(id);
        if (!s) { printf("Not found.\n"); pauseScreen(); return; }
        printf("\nID: %d\nName: %s\nPhone: %s\nDept: %s\nAge: %d\nRoom: %d\nFee: %.0f / %.0f\n",
               s->id, s->name, s->phone, s->department, s->age, s->roomNo,
               s->feePaid, s->feeTotal);
    } else {
        printf("Enter name (or part of): ");
        char q[MAX_NAME]; readString(q, MAX_NAME);
        int found = 0;
        for (int i = 0; i < studentCount; i++) {
            if (!students[i].active) continue;
            if (strstr(students[i].name, q) != NULL) {
                Student *s = &students[i];
                printf("%d | %s | %s | Room %d\n",
                       s->id, s->name, s->department, s->roomNo);
                found++;
            }
        }
        if (!found) printf("No matches.\n");
    }
    pauseScreen();
}

void updateStudent(void) {
    header("UPDATE STUDENT");
    printf("Enter student ID: ");
    int id; readInt(&id);
    Student *s = findStudentById(id);
    if (!s) { printf("Not found.\n"); pauseScreen(); return; }

    printf("Leave field empty to keep current value.\n");
    char buf[128];

    printf("Name [%s]: ", s->name);
    readString(buf, sizeof(buf));
    if (strlen(buf) > 0) strncpy(s->name, buf, MAX_NAME);

    printf("Phone [%s]: ", s->phone);
    readString(buf, sizeof(buf));
    if (strlen(buf) > 0) strncpy(s->phone, buf, MAX_PHONE);

    printf("Department [%s]: ", s->department);
    readString(buf, sizeof(buf));
    if (strlen(buf) > 0) strncpy(s->department, buf, MAX_DEPT);

    printf("Age [%d]: ", s->age);
    readString(buf, sizeof(buf));
    if (strlen(buf) > 0) s->age = atoi(buf);

    printf("Total Fee [%.0f]: ", s->feeTotal);
    readString(buf, sizeof(buf));
    if (strlen(buf) > 0) s->feeTotal = atof(buf);

    saveStudents();
    printf("Updated.\n");
    pauseScreen();
}

void deleteStudent(void) {
    header("DELETE STUDENT");
    printf("Enter student ID: ");
    int id; readInt(&id);
    Student *s = findStudentById(id);
    if (!s) { printf("Not found.\n"); pauseScreen(); return; }

    printf("Are you sure you want to delete %s? (y/n): ", s->name);
    char c; readString((char[]){0}, 1); /* ignore */
    c = getchar();
    if (c != 'y' && c != 'Y') { printf("Cancelled.\n"); pauseScreen(); return; }

    /* Free the room */
    if (s->roomNo > 0) {
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].roomNo == s->roomNo && rooms[i].occupied > 0) {
                rooms[i].occupied--;
                break;
            }
        }
    }
    s->active = 0;
    s->roomNo = 0;
    saveStudents();
    saveRooms();
    printf("Student deleted; room freed.\n");
    pauseScreen();
}

void studentMenu(void) {
    int ch;
    do {
        clearScreen();
        header("STUDENT MANAGEMENT");
        printf("  1. Add student\n");
        printf("  2. View all students\n");
        printf("  3. Search student\n");
        printf("  4. Update student\n");
        printf("  5. Delete student\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
        }
    } while (ch != 0);
}