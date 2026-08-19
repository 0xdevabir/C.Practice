#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------- Constants ---------- */
#define MAX_NAME       50
#define MAX_PHONE      15
#define MAX_DEPT       30
#define MAX_COMPLAINT  200
#define MAX_VISITOR    50
#define MAX_STUDENTS   200
#define MAX_ROOMS      50
#define MAX_COMPLAINTS 200
#define PASSWORD       "admin123"

/* ---------- Room ---------- */
typedef struct {
    int  roomNo;
    int  capacity;       /* total beds */
    int  occupied;       /* beds in use */
    int  active;         /* 1 = exists, 0 = deleted */
} Room;

/* ---------- Student ---------- */
typedef struct {
    int  id;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char department[MAX_DEPT];
    int  age;
    int  roomNo;         /* 0 = unassigned */
    float feeTotal;      /* total fee for current term */
    float feePaid;       /* amount paid so far */
    int  active;         /* soft delete */
} Student;

/* ---------- Complaint ---------- */
typedef struct {
    int  id;
    int  studentId;
    char category[30];   /* Mess / Maintenance / Hygiene / Security / Other */
    char text[MAX_COMPLAINT];
    char status[20];     /* OPEN / IN_PROGRESS / RESOLVED */
    char date[15];       /* dd/mm/yyyy */
    int  active;
} Complaint;

/* ---------- Visitor ---------- */
typedef struct {
    int  id;
    int  studentId;
    char visitorName[MAX_NAME];
    char relation[20];
    char phone[MAX_PHONE];
    char inTime[10];     /* hh:mm */
    char outTime[10];    /* hh:mm - "-" if still inside */
    char date[15];
    int  active;
} Visitor;

/* ---------- Session ---------- */
typedef struct {
    int loggedIn;
} Session;

/* Global arrays - small fixed-size in-memory store */
extern Student   students[MAX_STUDENTS];
extern Room      rooms[MAX_ROOMS];
extern Complaint complaints[MAX_COMPLAINTS];
extern Visitor   visitors[MAX_VISITOR];
extern int studentCount;
extern int roomCount;
extern int complaintCount;
extern int visitorCount;
extern int nextStudentId;
extern int nextComplaintId;
extern int nextVisitorId;

#endif
