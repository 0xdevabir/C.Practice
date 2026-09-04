#include "hospital.h"

Room *findFreeRoomOfType(const char *type) {
    int i;
    for (i = 0; i < roomCount; i++) {
        if (!rooms[i].occupied &&
            strcmp(rooms[i].status, "Available") == 0 &&
            strcasecmp(rooms[i].type, type) == 0) {
            return &rooms[i];
        }
    }
    return NULL;
}

void listRooms(void) {
    int filter, i;
    char type[20];

    printf("1. All rooms\n");
    printf("2. Available only\n");
    printf("3. Occupied only\n");
    printf("4. Filter by type\n");
    if (!readInt("Choice: ", &filter))
        return;

    if (filter == 4) {
        printf("Type (General/Private/ICU/Emergency): ");
        readLine(type, 20);
    }

    printf("\nRoom  Type         Floor  Rate     Status      Patient\n");
    for (i = 0; i < roomCount; i++) {
        if (filter == 2) {
            if (rooms[i].occupied || strcmp(rooms[i].status, "Available") != 0)
                continue;
        } else if (filter == 3) {
            if (!rooms[i].occupied)
                continue;
        } else if (filter == 4) {
            if (strcasecmp(rooms[i].type, type) != 0)
                continue;
        }

        printf("%-5d %-12s %-6s %-8.0f %-11s ",
               rooms[i].number, rooms[i].type, rooms[i].floor,
               rooms[i].dailyRate, rooms[i].status);
        if (rooms[i].patientId >= 0)
            printf("%d\n", rooms[i].patientId);
        else
            printf("-\n");
    }
}

void assignRoom(void) {
    int pid, pi, mode, rnum, ri;
    char type[20];
    Room *r;

    if (!readInt("Patient id: ", &pid))
        return;
    pi = findPatientIndex(pid);
    if (pi < 0) {
        printf("Patient not found.\n");
        return;
    }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient already gone.\n");
        return;
    }
    if (patients[pi].roomNumber > 0) {
        printf("Already in room %d. Use transfer instead.\n", patients[pi].roomNumber);
        return;
    }

    printf("1. Auto pick by type\n");
    printf("2. Enter room number myself\n");
    if (!readInt("Choice: ", &mode))
        return;

    ri = -1;
    if (mode == 1) {
        printf("Type: ");
        readLine(type, 20);
        r = findFreeRoomOfType(type);
        if (r == NULL) {
            printf("No free room of that type.\n");
            return;
        }
        ri = (int)(r - rooms);
    } else {
        if (!readInt("Room number: ", &rnum))
            return;
        ri = findRoomIndex(rnum);
        if (ri < 0) {
            printf("No such room.\n");
            return;
        }
        if (rooms[ri].occupied || strcmp(rooms[ri].status, "Available") != 0) {
            printf("Not available.\n");
            return;
        }
    }

    rooms[ri].occupied = 1;
    rooms[ri].patientId = pid;
    strcpy(rooms[ri].status, "Occupied");
    patients[pi].roomNumber = rooms[ri].number;
    if (patients[pi].daysAdmitted < 1)
        patients[pi].daysAdmitted = 1;

    printf("Assigned room %d (%s) - %.0f Tk/day\n",
           rooms[ri].number, rooms[ri].type, rooms[ri].dailyRate);
}

void setRoomMaintenance(void) {
    int rnum, ri;

    if (!readInt("Room number: ", &rnum))
        return;
    ri = findRoomIndex(rnum);
    if (ri < 0) {
        printf("Not found.\n");
        return;
    }
    if (rooms[ri].occupied) {
        printf("Someone is in that room.\n");
        return;
    }

    if (strcmp(rooms[ri].status, "Maintenance") == 0) {
        strcpy(rooms[ri].status, "Available");
        printf("Room %d is available again.\n", rnum);
    } else {
        strcpy(rooms[ri].status, "Maintenance");
        printf("Room %d marked for maintenance.\n", rnum);
    }
}

void roomMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Rooms --\n");
        printf("1. List rooms\n");
        printf("2. Assign room\n");
        printf("3. Maintenance toggle\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) listRooms();
        else if (ch == 2) assignRoom();
        else if (ch == 3) setRoomMaintenance();
        else if (ch == 4) return;
        else printf("Invalid.\n");
    }
}
