#include "hospital.h"

static void printPatient(const Patient *p) {
    printf("\n----------------------------------------\n");
    printf("ID: %d | %s | Age %d | %s | Blood %s\n",
           p->id, p->name, p->age, p->gender, p->bloodGroup);
    printf("Phone: %s | Emergency: %s\n", p->phone, p->emergencyContact);
    printf("Address: %s\n", p->address);
    printf("Condition: %s\n", p->condition);
    printf("Doctor ID: %d | Room: %d | Days: %d\n",
           p->doctorId, p->roomNumber, p->daysAdmitted);
    printf("Status: %s | Emergency: %s\n",
           p->status, p->isEmergency ? "YES" : "No");
    printf("Admit: %s | Discharge: %s\n",
           p->admitDate, p->dischargeDate[0] ? p->dischargeDate : "-");
    printf("Bill so far: Room %.0f + Doctor %.0f + Meds %.0f + Lab %.0f - Disc %.0f = %.0f\n",
           p->roomCharges, p->doctorFee, p->medicineCharges, p->labCharges,
           p->discount, p->totalBill);
    printf("----------------------------------------\n");
}

static double calcRunningTotal(Patient *p) {
    p->totalBill = p->roomCharges + p->doctorFee + p->medicineCharges +
                   p->labCharges - p->discount;
    if (p->totalBill < 0) p->totalBill = 0;
    return p->totalBill;
}

void registerPatient(void) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient capacity full.\n");
        return;
    }
    Patient p;
    memset(&p, 0, sizeof(p));
    p.id = meta.nextPatientId++;

    printf("Auto Patient ID: %d\n", p.id);
    printf("Enter Name: ");
    readLine(p.name, MAX_NAME);
    if (!p.name[0]) { printf("Name required.\n"); return; }

    if (!readInt("Enter Age: ", &p.age) || p.age <= 0 || p.age > 120) {
        printf("Invalid age.\n");
        return;
    }
    printf("Enter Gender (Male/Female/Other): ");
    readLine(p.gender, 12);
    printf("Enter Blood Group (e.g. B+): ");
    readLine(p.bloodGroup, 8);
    printf("Enter Phone: ");
    readLine(p.phone, MAX_PHONE);
    printf("Enter Emergency Contact: ");
    readLine(p.emergencyContact, MAX_NAME);
    printf("Enter Address: ");
    readLine(p.address, MAX_TEXT);
    printf("Enter Medical Condition: ");
    readLine(p.condition, MAX_CONDITION);

    p.doctorId = -1;
    p.roomNumber = 0;
    p.daysAdmitted = 0;
    p.isEmergency = 0;
    strcpy(p.status, "Admitted");
    todayDate(p.admitDate, MAX_DATE);
    p.dischargeDate[0] = '\0';
    calcRunningTotal(&p);

    patients[patientCount++] = p;
    printf("Patient registered. ID=%d Status=Admitted Date=%s\n",
           p.id, p.admitDate);
}

void emergencyAdmit(void) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient capacity full.\n");
        return;
    }
    Patient p;
    memset(&p, 0, sizeof(p));
    p.id = meta.nextPatientId++;
    printf("EMERGENCY ADMISSION — Auto ID: %d\n", p.id);

    printf("Enter Name (or Unknown): ");
    readLine(p.name, MAX_NAME);
    if (!p.name[0]) strcpy(p.name, "Unknown");

    printf("Enter Age (0 if unknown): ");
    if (scanf("%d", &p.age) != 1) p.age = 0;
    clearInput();
    strcpy(p.gender, "Unknown");
    strcpy(p.bloodGroup, "N/A");
    printf("Enter Phone (optional): ");
    readLine(p.phone, MAX_PHONE);
    printf("Enter Emergency Contact: ");
    readLine(p.emergencyContact, MAX_NAME);
    printf("Enter Critical Condition: ");
    readLine(p.condition, MAX_CONDITION);

    Room *er = findFreeRoomOfType("Emergency");
    if (!er) er = findFreeRoomOfType("ICU");
    if (er) {
        er->occupied = 1;
        er->patientId = p.id;
        strcpy(er->status, "Occupied");
        p.roomNumber = er->number;
        printf("Assigned %s room %d (Tk. %.0f/day).\n", er->type, er->number, er->dailyRate);
    } else {
        printf("WARNING: No Emergency/ICU room free — admitted without room.\n");
    }

    int erDoc = -1;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].available &&
            strcasecmp(doctors[i].specialization, "Emergency Medicine") == 0) {
            erDoc = i;
            break;
        }
    }
    if (erDoc == -1) {
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].available) { erDoc = i; break; }
        }
    }
    if (erDoc != -1) {
        p.doctorId = doctors[erDoc].id;
        doctors[erDoc].available = 0;
        doctors[erDoc].patientsAssigned++;
        p.doctorFee = doctors[erDoc].consultationFee;
        printf("Assigned %s (ID %d).\n", doctors[erDoc].name, doctors[erDoc].id);
    }

    p.daysAdmitted = 1;
    p.isEmergency = 1;
    strcpy(p.status, "Emergency");
    todayDate(p.admitDate, MAX_DATE);
    calcRunningTotal(&p);
    patients[patientCount++] = p;
    printf("Emergency patient admitted. ID=%d\n", p.id);
}

void searchPatient(void) {
    int mode;
    printf("1. By ID  2. By Name\n");
    if (!readInt("Choice: ", &mode)) return;
    int pi = -1;
    if (mode == 1) {
        int id;
        if (!readInt("Patient ID: ", &id)) return;
        pi = findPatientIndex(id);
    } else if (mode == 2) {
        char name[MAX_NAME];
        printf("Patient Name: ");
        readLine(name, MAX_NAME);
        pi = findPatientByName(name);
    } else {
        printf("Invalid.\n");
        return;
    }
    if (pi < 0) { printf("Patient not found.\n"); return; }
    printPatient(&patients[pi]);
}

void listPatients(void) {
    int filter;
    printf("1. All  2. Admitted  3. Discharged  4. Emergency only\n");
    if (!readInt("Filter: ", &filter)) return;
    printf("\n%-6s %-20s %-6s %-12s %-8s %-10s\n",
           "ID", "Name", "Age", "Status", "Room", "Emergency");
    printf("------------------------------------------------------------------\n");
    int shown = 0;
    for (int i = 0; i < patientCount; i++) {
        Patient *p = &patients[i];
        int show = 0;
        if (filter == 1) show = 1;
        else if (filter == 2 &&
                 (strcmp(p->status, "Admitted") == 0 ||
                  strcmp(p->status, "Emergency") == 0)) show = 1;
        else if (filter == 3 && strcmp(p->status, "Discharged") == 0) show = 1;
        else if (filter == 4 && p->isEmergency) show = 1;
        if (!show) continue;
        printf("%-6d %-20s %-6d %-12s %-8d %-10s\n",
               p->id, p->name, p->age, p->status, p->roomNumber,
               p->isEmergency ? "YES" : "No");
        shown++;
    }
    if (!shown) printf("No matching patients.\n");
}

void updatePatient(void) {
    int id;
    if (!readInt("Patient ID: ", &id)) return;
    int pi = findPatientIndex(id);
    if (pi < 0) { printf("Not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Cannot update discharged patient.\n");
        return;
    }
    Patient *p = &patients[pi];
    int c;
    printf("1.Name 2.Age 3.Condition 4.Phone 5.Days Admitted 6.Address\n");
    if (!readInt("Field: ", &c)) return;
    switch (c) {
        case 1: printf("New name: "); readLine(p->name, MAX_NAME); break;
        case 2:
            if (!readInt("New age: ", &p->age) || p->age <= 0) {
                printf("Invalid.\n"); return;
            }
            break;
        case 3: printf("New condition: "); readLine(p->condition, MAX_CONDITION); break;
        case 4: printf("New phone: "); readLine(p->phone, MAX_PHONE); break;
        case 5:
            if (!readInt("Days admitted: ", &p->daysAdmitted) || p->daysAdmitted < 0) {
                printf("Invalid.\n"); return;
            }
            if (p->roomNumber > 0) {
                int ri = findRoomIndex(p->roomNumber);
                if (ri >= 0) {
                    p->roomCharges = p->daysAdmitted * rooms[ri].dailyRate;
                    calcRunningTotal(p);
                }
            }
            break;
        case 6: printf("New address: "); readLine(p->address, MAX_TEXT); break;
        default: printf("Invalid.\n"); return;
    }
    printf("Updated.\n");
}

void transferRoom(void) {
    int id;
    if (!readInt("Patient ID: ", &id)) return;
    int pi = findPatientIndex(id);
    if (pi < 0) { printf("Not found.\n"); return; }
    Patient *p = &patients[pi];
    if (strcmp(p->status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }
    int newRoom;
    if (!readInt("New room number: ", &newRoom)) return;
    int nri = findRoomIndex(newRoom);
    if (nri < 0) { printf("Room not found.\n"); return; }
    if (rooms[nri].occupied || strcmp(rooms[nri].status, "Available") != 0) {
        printf("Room not available.\n");
        return;
    }
    if (p->roomNumber > 0) {
        int ori = findRoomIndex(p->roomNumber);
        if (ori >= 0) {
            rooms[ori].occupied = 0;
            rooms[ori].patientId = -1;
            strcpy(rooms[ori].status, "Available");
            p->roomCharges += p->daysAdmitted * rooms[ori].dailyRate;
        }
    }
    rooms[nri].occupied = 1;
    rooms[nri].patientId = p->id;
    strcpy(rooms[nri].status, "Occupied");
    p->roomNumber = newRoom;
    p->daysAdmitted = 0;
    calcRunningTotal(p);
    printf("Transferred to room %d (%s, Tk. %.0f/day).\n",
           newRoom, rooms[nri].type, rooms[nri].dailyRate);
}

void patientMenu(void) {
    int c;
    while (1) {
        printf("\n=== PATIENT MANAGEMENT ===\n");
        printf("1. Register Patient\n");
        printf("2. Emergency Admission\n");
        printf("3. Search Patient\n");
        printf("4. List Patients\n");
        printf("5. Update Patient\n");
        printf("6. Transfer Room\n");
        printf("7. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: registerPatient(); break;
            case 2: emergencyAdmit(); break;
            case 3: searchPatient(); break;
            case 4: listPatients(); break;
            case 5: updatePatient(); break;
            case 6: transferRoom(); break;
            case 7: return;
            default: printf("Invalid.\n");
        }
    }
}
