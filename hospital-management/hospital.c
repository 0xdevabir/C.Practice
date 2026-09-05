/* CSE115 Project - Option A: Hospital Management System */
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define MAX_PATIENTS 50
#define MAX_DOCTORS 20
#define DAILY_ROOM_RATE 2000

typedef struct {
    int id;
    char name[50];
    int age;
    char condition[50];
    int doctorId;       /* -1 = no doctor assigned */
    int roomNumber;
    int daysAdmitted;
    double totalBill;
    char status[12];     /* "Admitted" or "Discharged" */
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[30];
    int available;       /* 1 = available, 0 = unavailable */
    double consultationFee;
} Doctor;

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int patientCount = 0;
int doctorCount = 0;

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readLine(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

int findPatient(int id) {
    for (int i = 0; i < patientCount; i++)
        if (patients[i].id == id)
            return i;
    return -1;
}

int findDoctor(int id) {
    for (int i = 0; i < doctorCount; i++)
        if (doctors[i].id == id)
            return i;
    return -1;
}

void seedDoctors(void) {
    Doctor sample[] = {
        {101, "Dr. Rahman", "Cardiology", 1, 1500},
        {102, "Dr. Nafisa", "Neurology", 1, 1800},
        {103, "Dr. Karim", "Cardiology", 1, 1200},
        {104, "Dr. Sultana", "Pediatrics", 1, 1000},
        {105, "Dr. Islam", "Orthopedics", 1, 1600},
    };
    doctorCount = sizeof(sample) / sizeof(sample[0]);
    for (int i = 0; i < doctorCount; i++)
        doctors[i] = sample[i];
}

/* ---------- 1. Register Patient ---------- */
void registerPatient(void) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient list is full.\n");
        return;
    }
    Patient p;
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    clearInput();

    if (findPatient(p.id) != -1) {
        printf("A patient with that ID already exists.\n");
        return;
    }

    printf("Enter name: ");
    readLine(p.name, sizeof(p.name));

    printf("Enter age: ");
    scanf("%d", &p.age);
    clearInput();
    if (p.age < 0) {
        printf("Age cannot be negative.\n");
        return;
    }

    printf("Enter condition: ");
    readLine(p.condition, sizeof(p.condition));

    printf("Enter room number: ");
    scanf("%d", &p.roomNumber);
    clearInput();

    printf("Enter days admitted: ");
    scanf("%d", &p.daysAdmitted);
    clearInput();
    if (p.daysAdmitted < 0) {
        printf("Days admitted cannot be negative.\n");
        return;
    }

    p.doctorId = -1;
    p.totalBill = 0;
    strcpy(p.status, "Admitted");

    patients[patientCount++] = p;
    printf("Patient registered with status Admitted.\n");
}

void listAllDoctors(void) {
    if (doctorCount == 0) {
        printf("No doctors on record.\n");
        return;
    }
    printf("\n%-6s %-20s %-15s %-10s %-10s\n", "ID", "Name", "Specialization", "Fee", "Status");
    for (int i = 0; i < doctorCount; i++) {
        printf("%-6d %-20s %-15s %-10.2f %-10s\n",
               doctors[i].id, doctors[i].name, doctors[i].specialization,
               doctors[i].consultationFee, doctors[i].available ? "Available" : "Unavailable");
    }
}

/* ---------- 2. Search Doctor by Specialization ---------- */
void searchDoctorBySpecialization(void) {
    printf("1. List all doctors\n2. Search by specialization\n");
    int mode;
    printf("Choice: ");
    scanf("%d", &mode);
    clearInput();

    if (mode == 1) {
        listAllDoctors();
        return;
    }
    if (mode != 2) {
        printf("Invalid choice.\n");
        return;
    }

    char spec[30];
    printf("Enter specialization: ");
    readLine(spec, sizeof(spec));

    printf("\nAvailable Doctors:\n");
    printf("%-6s %-20s %-10s\n", "ID", "Name", "Fee");
    int found = 0;
    for (int i = 0; i < doctorCount; i++) {
        if (strcasecmp(doctors[i].specialization, spec) == 0 && doctors[i].available) {
            printf("%-6d %-20s %-10.2f\n", doctors[i].id, doctors[i].name, doctors[i].consultationFee);
            found = 1;
        }
    }
    if (!found)
        printf("No available doctors found for that specialization.\n");
}

/* ---------- 3. Assign Doctor to Patient ---------- */
void assignDoctor(void) {
    int pid, did;
    printf("Enter Patient ID: ");
    scanf("%d", &pid);
    clearInput();
    int pi = findPatient(pid);
    if (pi == -1) {
        printf("Patient not found.\n");
        return;
    }

    printf("Enter Doctor ID: ");
    scanf("%d", &did);
    clearInput();
    int di = findDoctor(did);
    if (di == -1) {
        printf("Doctor not found.\n");
        return;
    }
    if (!doctors[di].available) {
        printf("That doctor is not available.\n");
        return;
    }

    patients[pi].doctorId = did;
    doctors[di].available = 0;
    printf("Doctor %s assigned to patient %s.\n", doctors[di].name, patients[pi].name);
}

void listAllPatients(void) {
    if (patientCount == 0) {
        printf("No patients on record.\n");
        return;
    }
    printf("\n%-6s %-20s %-5s %-20s %-10s\n", "ID", "Name", "Age", "Condition", "Status");
    for (int i = 0; i < patientCount; i++) {
        printf("%-6d %-20s %-5d %-20s %-10s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].condition, patients[i].status);
    }
}

/* ---------- 4. Search Patient ---------- */
void searchPatient(void) {
    printf("1. List all patients\n2. Search by Patient ID\n");
    int mode;
    printf("Choice: ");
    scanf("%d", &mode);
    clearInput();

    if (mode == 1) {
        listAllPatients();
        return;
    }
    if (mode != 2) {
        printf("Invalid choice.\n");
        return;
    }

    int id;
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    clearInput();

    int i = findPatient(id);
    if (i == -1) {
        printf("Patient not found.\n");
        return;
    }
    Patient *p = &patients[i];
    printf("\nPatient ID     : %d\n", p->id);
    printf("Name           : %s\n", p->name);
    printf("Age            : %d\n", p->age);
    printf("Condition      : %s\n", p->condition);
    if (p->doctorId == -1)
        printf("Doctor ID      : None\n");
    else
        printf("Doctor ID      : %d\n", p->doctorId);
    printf("Room Number    : %d\n", p->roomNumber);
    printf("Days Admitted  : %d\n", p->daysAdmitted);
    printf("Total Bill     : %.2f\n", p->totalBill);
    printf("Status         : %s\n", p->status);
}

/* ---------- 5. Update Patient Information ---------- */
void updatePatient(void) {
    int id;
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    clearInput();

    int i = findPatient(id);
    if (i == -1) {
        printf("Patient not found.\n");
        return;
    }

    printf("1. Name\n2. Age\n3. Condition\n4. Room number\n5. Days admitted\n");
    int choice;
    printf("What do you want to update: ");
    scanf("%d", &choice);
    clearInput();

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            readLine(patients[i].name, sizeof(patients[i].name));
            break;
        case 2: {
            int age;
            printf("Enter new age: ");
            scanf("%d", &age);
            clearInput();
            if (age < 0) {
                printf("Age cannot be negative.\n");
                return;
            }
            patients[i].age = age;
            break;
        }
        case 3:
            printf("Enter new condition: ");
            readLine(patients[i].condition, sizeof(patients[i].condition));
            break;
        case 4:
            printf("Enter new room number: ");
            scanf("%d", &patients[i].roomNumber);
            clearInput();
            break;
        case 5: {
            int days;
            printf("Enter new days admitted: ");
            scanf("%d", &days);
            clearInput();
            if (days < 0) {
                printf("Days admitted cannot be negative.\n");
                return;
            }
            patients[i].daysAdmitted = days;
            break;
        }
        default:
            printf("Invalid choice.\n");
            return;
    }
    printf("Patient updated.\n");
}

/* ---------- 6. Discharge Patient and Calculate Bill ---------- */
void dischargePatient(void) {
    int id;
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    clearInput();

    int i = findPatient(id);
    if (i == -1) {
        printf("Patient not found.\n");
        return;
    }
    Patient *p = &patients[i];
    if (strcmp(p->status, "Discharged") == 0) {
        printf("Patient is already discharged.\n");
        return;
    }

    double roomCharge = p->daysAdmitted * DAILY_ROOM_RATE;
    double doctorFee = 0;
    int di = findDoctor(p->doctorId);
    if (di != -1)
        doctorFee = doctors[di].consultationFee;

    p->totalBill = roomCharge + doctorFee;
    strcpy(p->status, "Discharged");

    if (di != -1)
        doctors[di].available = 1;

    printf("\n========================================\n");
    printf("            HOSPITAL BILL\n");
    printf("========================================\n");
    printf("Patient ID     : %d\n", p->id);
    printf("Patient Name   : %s\n", p->name);
    printf("Room Number    : %d\n", p->roomNumber);
    printf("Days Admitted  : %d\n", p->daysAdmitted);
    printf("Room Charge    : Tk. %.2f\n", roomCharge);
    printf("Doctor Fee     : Tk. %.2f\n", doctorFee);
    printf("----------------------------------------\n");
    printf("TOTAL BILL     : Tk. %.2f\n", p->totalBill);
    printf("Status         : %s\n", p->status);
    printf("========================================\n");
}

/* ---------- 7. Display Hospital Summary ---------- */
void displaySummary(void) {
    int admitted = 0, discharged = 0, availableDocs = 0, unavailableDocs = 0;
    double revenue = 0;

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].status, "Admitted") == 0)
            admitted++;
        else {
            discharged++;
            revenue += patients[i].totalBill;
        }
    }
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].available)
            availableDocs++;
        else
            unavailableDocs++;
    }

    printf("\n===== Hospital Summary =====\n");
    printf("Total patients        : %d\n", patientCount);
    printf("Admitted patients     : %d\n", admitted);
    printf("Discharged patients   : %d\n", discharged);
    printf("Available doctors     : %d\n", availableDocs);
    printf("Unavailable doctors   : %d\n", unavailableDocs);
    printf("Total revenue         : Tk. %.2f\n", revenue);
}

int main(void) {
    seedDoctors();
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("       HOSPITAL MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Register Patient\n");
        printf("2. Search Patient\n");
        printf("3. Search Doctor\n");
        printf("4. Assign Doctor\n");
        printf("5. Update Patient\n");
        printf("6. Discharge Patient\n");
        printf("7. Hospital Summary\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid menu choice.\n");
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: searchPatient(); break;
            case 3: searchDoctorBySpecialization(); break;
            case 4: assignDoctor(); break;
            case 5: updatePatient(); break;
            case 6: dischargePatient(); break;
            case 7: displaySummary(); break;
            case 8:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid menu choice.\n");
        }
    }
    return 0;
}
