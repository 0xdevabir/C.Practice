#include "room.h"
#include "student.h"
#include "utils.h"
#include "file_ops.h"

Room* findRoom(int roomNo) {
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].active && rooms[i].roomNo == roomNo) return &rooms[i];
    }
    return NULL;
}

void viewRooms(void) {
    header("ALL ROOMS");
    printf("%-8s %-10s %-10s %-10s\n", "Room", "Capacity", "Occupied", "Free");
    printLine('-', 40);
    int totalCap = 0, totalOcc = 0;
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].active) continue;
        Room *r = &rooms[i];
        int free = r->capacity - r->occupied;
        printf("%-8d %-10d %-10d %-10d\n",
               r->roomNo, r->capacity, r->occupied, free);
        totalCap += r->capacity;
        totalOcc += r->occupied;
    }
    printf("\nTotal capacity: %d | Occupied: %d | Free: %d\n",
           totalCap, totalOcc, totalCap - totalOcc);
    pauseScreen();
}

void viewAvailableBeds(void) {
    header("AVAILABLE BEDS");
    int totalFree = 0;
    printf("%-8s %-10s\n", "Room", "Free Beds");
    printLine('-', 20);
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].active) continue;
        int free = rooms[i].capacity - rooms[i].occupied;
        if (free > 0) {
            printf("%-8d %-10d\n", rooms[i].roomNo, free);
            totalFree += free;
        }
    }
    if (totalFree == 0) printf("No free beds available.\n");
    else printf("\nTotal free beds: %d\n", totalFree);
    pauseScreen();
}

void allocateRoom(void) {
    header("ALLOCATE ROOM");
    int sid;
    printf("Student ID: "); readInt(&sid);
    Student *s = findStudentById(sid);
    if (!s) { printf("Student not found.\n"); pauseScreen(); return; }

    if (s->roomNo > 0) {
        printf("Student is already in room %d. Use reassign instead.\n", s->roomNo);
        pauseScreen();
        return;
    }

    int rno;
    printf("Room number to assign: "); readInt(&rno);
    Room *r = findRoom(rno);
    if (!r) { printf("Room not found.\n"); pauseScreen(); return; }

    if (r->occupied >= r->capacity) {
        printf("Room %d is full.\n", rno);
        pauseScreen();
        return;
    }

    r->occupied++;
    s->roomNo = rno;
    saveStudents();
    saveRooms();
    printf("Student %s allocated to room %d.\n", s->name, rno);
    pauseScreen();
}

void reassignRoom(void) {
    header("REASSIGN ROOM");
    int sid;
    printf("Student ID: "); readInt(&sid);
    Student *s = findStudentById(sid);
    if (!s) { printf("Student not found.\n"); pauseScreen(); return; }

    if (s->roomNo == 0) {
        printf("Student has no current room. Use allocate instead.\n");
        pauseScreen();
        return;
    }

    int oldRoom = s->roomNo;
    int newRoom;
    printf("New room number: "); readInt(&newRoom);
    if (newRoom == oldRoom) {
        printf("Same room. Nothing to do.\n");
        pauseScreen();
        return;
    }

    Room *oldR = findRoom(oldRoom);
    Room *newR = findRoom(newRoom);
    if (!newR) { printf("New room not found.\n"); pauseScreen(); return; }
    if (newR->occupied >= newR->capacity) {
        printf("New room %d is full.\n", newRoom);
        pauseScreen();
        return;
    }

    if (oldR && oldR->occupied > 0) oldR->occupied--;
    newR->occupied++;
    s->roomNo = newRoom;

    saveStudents();
    saveRooms();
    printf("Student moved from room %d to %d.\n", oldRoom, newRoom);
    pauseScreen();
}

void addRoom(void) {
    header("ADD NEW ROOM");
    if (roomCount >= MAX_ROOMS) {
        printf("Room storage full.\n");
        pauseScreen();
        return;
    }
    int rno, cap;
    printf("Room number: "); readInt(&rno);
    if (findRoom(rno)) {
        printf("Room %d already exists.\n", rno);
        pauseScreen();
        return;
    }
    printf("Capacity (beds): "); readInt(&cap);
    if (cap <= 0) cap = 2;

    rooms[roomCount].roomNo   = rno;
    rooms[roomCount].capacity = cap;
    rooms[roomCount].occupied = 0;
    rooms[roomCount].active   = 1;
    roomCount++;
    saveRooms();
    printf("Room %d added (capacity %d).\n", rno, cap);
    pauseScreen();
}

void roomMenu(void) {
    int ch;
    do {
        clearScreen();
        header("ROOM MANAGEMENT");
        printf("  1. View all rooms\n");
        printf("  2. View available beds\n");
        printf("  3. Allocate room\n");
        printf("  4. Reassign room\n");
        printf("  5. Add new room\n");
        printf("  0. Back\n");
        printf("Choice: ");
        readInt(&ch);
        switch (ch) {
            case 1: viewRooms(); break;
            case 2: viewAvailableBeds(); break;
            case 3: allocateRoom(); break;
            case 4: reassignRoom(); break;
            case 5: addRoom(); break;
        }
    } while (ch != 0);
}