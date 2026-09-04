/*
 * Hospital Management System
 * CSE115 Project - Option A
 *
 * I split the code into a few .c files so main doesn't get too long.
 * Compile with: make
 */

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>

#define MAX_PATIENTS 200
#define MAX_DOCTORS 80
#define MAX_ROOMS 60
#define MAX_APPTS 300
#define MAX_MEDS 100
#define MAX_LABS 50
#define MAX_PRESCRIPTIONS 500
#define MAX_LAB_ORDERS 400

#define MAX_NAME 60
#define MAX_PHONE 20
#define MAX_SPEC 40
#define MAX_DEPT 40
#define MAX_CONDITION 80
#define MAX_TEXT 100
#define MAX_DATE 16
#define MAX_TIME 10

#define F_PATIENTS "data/patients.dat"
#define F_DOCTORS "data/doctors.dat"
#define F_ROOMS "data/rooms.dat"
#define F_APPTS "data/appointments.dat"
#define F_MEDS "data/medicines.dat"
#define F_LABS "data/labtests.dat"
#define F_PRESC "data/prescriptions.dat"
#define F_LABORD "data/laborders.dat"
#define F_META "data/meta.dat"

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char gender[12];
    char bloodGroup[8];
    char phone[MAX_PHONE];
    char emergencyContact[MAX_NAME];
    char address[MAX_TEXT];
    char condition[MAX_CONDITION];
    int doctorId;      /* -1 means no doctor yet */
    int roomNumber;    /* 0 means no room */
    int daysAdmitted;
    double roomCharges;
    double doctorFee;
    double medicineCharges;
    double labCharges;
    double discount;
    double totalBill;
    char status[20];
    char admitDate[MAX_DATE];
    char dischargeDate[MAX_DATE];
    int isEmergency;
} Patient;

typedef struct {
    int id;
    char name[MAX_NAME];
    char specialization[MAX_SPEC];
    char department[MAX_DEPT];
    char phone[MAX_PHONE];
    int available;
    double consultationFee;
    int patientsAssigned;
    int maxPatients;
    int yearsExperience;
} Doctor;

typedef struct {
    int number;
    char type[20];
    char floor[12];
    double dailyRate;
    int occupied;
    int patientId;
    char status[16];
} Room;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[MAX_DATE];
    char timeSlot[MAX_TIME];
    char reason[MAX_TEXT];
    char status[20];
} Appointment;

typedef struct {
    int id;
    char name[MAX_NAME];
    char category[30];
    double price;
    int stock;
    int reorderLevel;
} Medicine;

typedef struct {
    int id;
    char name[MAX_NAME];
    char category[30];
    double price;
    int turnaroundHours;
} LabTest;

typedef struct {
    int id;
    int patientId;
    int medicineId;
    int quantity;
    double amount;
    char date[MAX_DATE];
} Prescription;

typedef struct {
    int id;
    int patientId;
    int labTestId;
    char status[20];
    double amount;
    char date[MAX_DATE];
} LabOrder;

/* keeps track of next ids so we dont reuse them after delete/discharge */
typedef struct {
    int nextPatientId;
    int nextDoctorId;
    int nextApptId;
    int nextMedId;
    int nextLabId;
    int nextPrescId;
    int nextLabOrderId;
} Meta;

extern Patient patients[];
extern Doctor doctors[];
extern Room rooms[];
extern Appointment appointments[];
extern Medicine medicines[];
extern LabTest labTests[];
extern Prescription prescriptions[];
extern LabOrder labOrders[];
extern Meta meta;

extern int patientCount, doctorCount, roomCount, apptCount;
extern int medCount, labCount, prescCount, labOrderCount;

void clearInput(void);
void readLine(char *buf, int size);
void todayDate(char *out, int size);
int readInt(const char *prompt, int *out);
int readDouble(const char *prompt, double *out);
void ensureDataDir(void);

int findPatientIndex(int id);
int findPatientByName(const char *name);
int findDoctorIndex(int id);
int findRoomIndex(int number);
int findApptIndex(int id);
int findMedIndex(int id);
int findLabIndex(int id);

void seedAll(void);
int saveAll(void);
int loadAll(void);

void patientMenu(void);
void registerPatient(void);
void emergencyAdmit(void);
void searchPatient(void);
void listPatients(void);
void updatePatient(void);
void transferRoom(void);

void doctorMenu(void);
void addDoctor(void);
void searchDoctor(void);
void listDoctors(void);
void updateDoctor(void);
void assignDoctor(void);
void releaseDoctorFromPatient(int patientIndex);

void roomMenu(void);
void listRooms(void);
void assignRoom(void);
void setRoomMaintenance(void);
Room *findFreeRoomOfType(const char *type);

void appointmentMenu(void);
void scheduleAppointment(void);
void listAppointments(void);
void updateAppointmentStatus(void);
void cancelAppointment(void);

void pharmacyMenu(void);
void addMedicine(void);
void listMedicines(void);
void updateMedicineStock(void);
void prescribeMedicine(void);
void lowStockAlert(void);

void labMenu(void);
void listLabTests(void);
void orderLabTest(void);
void completeLabOrder(void);
void listLabOrders(void);

void billingMenu(void);
void dischargePatient(void);
void viewPatientBill(void);
void applyDiscount(void);

void reportsMenu(void);
void hospitalSummary(void);
void revenueReport(void);
void occupancyReport(void);
void emergencyReport(void);

#endif
