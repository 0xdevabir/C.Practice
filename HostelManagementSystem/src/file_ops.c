#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Global in-memory storage */
Student   students[MAX_STUDENTS];
Room      rooms[MAX_ROOMS];
Complaint complaints[MAX_COMPLAINTS];
Visitor   visitors[MAX_VISITOR];
int studentCount   = 0;
int roomCount      = 0;
int complaintCount = 0;
int visitorCount   = 0;
int nextStudentId  = 1001;
int nextComplaintId = 1;
int nextVisitorId  = 1;

void ensureDataDir(void) {
#ifdef _WIN32
    mkdir(DATA_DIR);
#else
    mkdir(DATA_DIR, 0777);
#endif
}

static void seedRoomsIfEmpty(void) {
    if (roomCount > 0) return;
    int caps[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    for (int i = 0; i < 10; i++) {
        rooms[roomCount].roomNo   = 101 + i;
        rooms[roomCount].capacity = caps[i];
        rooms[roomCount].occupied = 0;
        rooms[roomCount].active   = 1;
        roomCount++;
    }
}

void loadRooms(void) {
    FILE *fp = fopen(F_ROOMS, "rb");
    if (!fp) { seedRoomsIfEmpty(); saveRooms(); return; }
    roomCount = fread(rooms, sizeof(Room), MAX_ROOMS, fp);
    fclose(fp);
    if (roomCount == 0) seedRoomsIfEmpty();
}

void saveRooms(void) {
    FILE *fp = fopen(F_ROOMS, "wb");
    if (!fp) { perror("saveRooms"); return; }
    fwrite(rooms, sizeof(Room), roomCount, fp);
    fclose(fp);
}

void loadStudents(void) {
    FILE *fp = fopen(F_STUDENTS, "rb");
    if (!fp) return;
    studentCount = fread(students, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
}

void saveStudents(void) {
    FILE *fp = fopen(F_STUDENTS, "wb");
    if (!fp) { perror("saveStudents"); return; }
    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}

void loadComplaints(void) {
    FILE *fp = fopen(F_COMPLAINTS, "rb");
    if (!fp) return;
    complaintCount = fread(complaints, sizeof(Complaint), MAX_COMPLAINTS, fp);
    fclose(fp);
}

void saveComplaints(void) {
    FILE *fp = fopen(F_COMPLAINTS, "wb");
    if (!fp) { perror("saveComplaints"); return; }
    fwrite(complaints, sizeof(Complaint), complaintCount, fp);
    fclose(fp);
}

void loadVisitors(void) {
    FILE *fp = fopen(F_VISITORS, "rb");
    if (!fp) return;
    visitorCount = fread(visitors, sizeof(Visitor), MAX_VISITOR, fp);
    fclose(fp);
}

void saveVisitors(void) {
    FILE *fp = fopen(F_VISITORS, "wb");
    if (!fp) { perror("saveVisitors"); return; }
    fwrite(visitors, sizeof(Visitor), visitorCount, fp);
    fclose(fp);
}

void loadCounters(void) {
    FILE *fp = fopen(F_COUNTERS, "r");
    if (!fp) return;
    if (fscanf(fp, "%d %d %d",
               &nextStudentId, &nextComplaintId, &nextVisitorId) != 3) {
        nextStudentId = 1001;
        nextComplaintId = 1;
        nextVisitorId = 1;
    }
    fclose(fp);
}

void saveCounters(void) {
    FILE *fp = fopen(F_COUNTERS, "w");
    if (!fp) return;
    fprintf(fp, "%d %d %d\n", nextStudentId, nextComplaintId, nextVisitorId);
    fclose(fp);
}

void loadAll(void) {
    ensureDataDir();
    loadRooms();
    loadStudents();
    loadComplaints();
    loadVisitors();
    loadCounters();
}

void saveAll(void) {
    ensureDataDir();
    saveRooms();
    saveStudents();
    saveComplaints();
    saveVisitors();
    saveCounters();
}