#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "structs.h"

#define DATA_DIR        "data"
#define F_STUDENTS      "data/students.dat"
#define F_ROOMS         "data/rooms.dat"
#define F_COMPLAINTS    "data/complaints.dat"
#define F_VISITORS      "data/visitors.dat"
#define F_COUNTERS      "data/counters.dat"

void ensureDataDir(void);
void loadAll(void);
void saveAll(void);
void loadStudents(void);
void saveStudents(void);
void loadRooms(void);
void saveRooms(void);
void loadComplaints(void);
void saveComplaints(void);
void loadVisitors(void);
void saveVisitors(void);
void loadCounters(void);
void saveCounters(void);

#endif