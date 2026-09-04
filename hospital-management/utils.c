#include "hospital.h"

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
Room rooms[MAX_ROOMS];
Appointment appointments[MAX_APPTS];
Medicine medicines[MAX_MEDS];
LabTest labTests[MAX_LABS];
Prescription prescriptions[MAX_PRESCRIPTIONS];
LabOrder labOrders[MAX_LAB_ORDERS];
Meta meta;

int patientCount = 0;
int doctorCount = 0;
int roomCount = 0;
int apptCount = 0;
int medCount = 0;
int labCount = 0;
int prescCount = 0;
int labOrderCount = 0;

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    int n = (int)strlen(buf);
    if (n > 0 && buf[n - 1] == '\n')
        buf[n - 1] = '\0';
}

void todayDate(char *out, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    /* day/month/year is easier to type than ISO format */
    snprintf(out, (size_t)size, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
}

int readInt(const char *prompt, int *out) {
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        clearInput();
        return 0;
    }
    clearInput();
    return 1;
}

int readDouble(const char *prompt, double *out) {
    printf("%s", prompt);
    if (scanf("%lf", out) != 1) {
        clearInput();
        return 0;
    }
    clearInput();
    return 1;
}

void ensureDataDir(void) {
    /* kinda lazy but works on mac/linux */
    system("mkdir -p data");
}

int findPatientIndex(int id) {
    int i;
    for (i = 0; i < patientCount; i++) {
        if (patients[i].id == id)
            return i;
    }
    return -1;
}

int findPatientByName(const char *name) {
    int i;
    for (i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].name, name) == 0)
            return i;
    }
    return -1;
}

int findDoctorIndex(int id) {
    int i;
    for (i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id)
            return i;
    }
    return -1;
}

int findRoomIndex(int number) {
    int i;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].number == number)
            return i;
    }
    return -1;
}

int findApptIndex(int id) {
    int i;
    for (i = 0; i < apptCount; i++) {
        if (appointments[i].id == id)
            return i;
    }
    return -1;
}

int findMedIndex(int id) {
    int i;
    for (i = 0; i < medCount; i++) {
        if (medicines[i].id == id)
            return i;
    }
    return -1;
}

int findLabIndex(int id) {
    int i;
    for (i = 0; i < labCount; i++) {
        if (labTests[i].id == id)
            return i;
    }
    return -1;
}
