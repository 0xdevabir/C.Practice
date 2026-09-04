#include "hospital.h"

Room *findFreeRoomOfType(const char *type) {
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].occupied &&
            strcmp(rooms[i].status, "Available") == 0 &&
            strcasecmp(rooms[i].type, type) == 0) {
            return &rooms[i];
        }
    }
    return NULL;
}

void listRooms(void) {
    int filter;
    printf("1.All 2.Available 3.Occupied 4.By type\n");
    if (!readInt("Filter: ", &filter)) return;
    char type[20] = "";
    if (filter == 4) {
        printf("Type (General/Private/ICU/Emergency): ");
        readLine(type, 20);
    }
    printf("\n%-6s %-12s %-6s %-10s %-10s %-10s\n",
           "Room", "Type", "Floor", "Rate/Day", "Status", "Patient");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < roomCount; i++) {
        Room *r = &rooms[i];
        int show = 1;
        if (filter == 2 && (r->occupied || strcmp(r->status, "Available") != 0)) show = 0;
        if (filter == 3 && !r->occupied) show = 0;
        if (filter == 4 && strcasecmp(r->type, type) != 0) show = 0;
        if (!show) continue;
        printf("%-6d %-12s %-6s %-10.0f %-10s %-10d\n",
               r->number, r->type, r->floor, r->dailyRate, r->status,
               r->patientId >= 0 ? r->patientId : 0);
    }
}

void assignRoom(void) {
    int pid, rnum;
    if (!readInt("Patient ID: ", &pid)) return;
    int pi = findPatientIndex(pid);
    if (pi < 0) { printf("Patient not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }
    if (patients[pi].roomNumber > 0) {
        printf("Already in room %d. Use Transfer Room.\n", patients[pi].roomNumber);
        return;
    }
    printf("Quick assign by type? 1=Yes 2=Pick room number\n");
    int mode;
    if (!readInt("Choice: ", &mode)) return;
    int ri = -1;
    if (mode == 1) {
        char type[20];
        printf("Type (General/Private/ICU/Emergency): ");
        readLine(type, 20);
        Room *r = findFreeRoomOfType(type);
        if (!r) { printf("No free room of that type.\n"); return; }
        ri = (int)(r - rooms);
    } else {
        if (!readInt("Room number: ", &rnum)) return;
        ri = findRoomIndex(rnum);
        if (ri < 0) { printf("Room not found.\n"); return; }
        if (rooms[ri].occupied || strcmp(rooms[ri].status, "Available") != 0) {
            printf("Room not available.\n");
            return;
        }
    }
    rooms[ri].occupied = 1;
    rooms[ri].patientId = pid;
    strcpy(rooms[ri].status, "Occupied");
    patients[pi].roomNumber = rooms[ri].number;
    if (patients[pi].daysAdmitted < 1) patients[pi].daysAdmitted = 1;
    printf("Room %d (%s) assigned. Rate Tk. %.0f/day.\n",
           rooms[ri].number, rooms[ri].type, rooms[ri].dailyRate);
}

void setRoomMaintenance(void) {
    int rnum;
    if (!readInt("Room number: ", &rnum)) return;
    int ri = findRoomIndex(rnum);
    if (ri < 0) { printf("Not found.\n"); return; }
    if (rooms[ri].occupied) {
        printf("Cannot mark occupied room as maintenance.\n");
        return;
    }
    if (strcmp(rooms[ri].status, "Maintenance") == 0) {
        strcpy(rooms[ri].status, "Available");
        printf("Room %d back to Available.\n", rnum);
    } else {
        strcpy(rooms[ri].status, "Maintenance");
        printf("Room %d set to Maintenance.\n", rnum);
    }
}

void roomMenu(void) {
    int c;
    while (1) {
        printf("\n=== ROOM MANAGEMENT ===\n");
        printf("1. List Rooms\n");
        printf("2. Assign Room to Patient\n");
        printf("3. Toggle Maintenance\n");
        printf("4. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: listRooms(); break;
            case 2: assignRoom(); break;
            case 3: setRoomMaintenance(); break;
            case 4: return;
            default: printf("Invalid.\n");
        }
    }
}
