#include "hospital.h"

static void showPatient(Patient *p) {
    printf("\n--- Patient details ---\n");
    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Gender: %s\n", p->gender);
    printf("Blood group: %s\n", p->bloodGroup);
    printf("Phone: %s\n", p->phone);
    printf("Emergency contact: %s\n", p->emergencyContact);
    printf("Address: %s\n", p->address);
    printf("Condition: %s\n", p->condition);
    printf("Doctor id: %d\n", p->doctorId);
    printf("Room: %d\n", p->roomNumber);
    printf("Days admitted: %d\n", p->daysAdmitted);
    printf("Status: %s\n", p->status);
    if (p->isEmergency)
        printf("Emergency case: yes\n");
    printf("Admit date: %s\n", p->admitDate);
    if (p->dischargeDate[0] != '\0')
        printf("Discharge date: %s\n", p->dischargeDate);
    printf("Bill so far: %.2f Tk\n", p->totalBill);
    printf("-----------------------\n");
}

static void updateTotal(Patient *p) {
    p->totalBill = p->roomCharges + p->doctorFee + p->medicineCharges + p->labCharges - p->discount;
    if (p->totalBill < 0)
        p->totalBill = 0;
}

void registerPatient(void) {
    Patient p;
    int ok;

    if (patientCount >= MAX_PATIENTS) {
        printf("Sorry, patient list is full.\n");
        return;
    }

    memset(&p, 0, sizeof(p));
    p.id = meta.nextPatientId;
    meta.nextPatientId++;

    printf("New patient id will be: %d\n", p.id);

    printf("Name: ");
    readLine(p.name, MAX_NAME);
    if (strlen(p.name) == 0) {
        printf("Name is required.\n");
        return;
    }

    ok = readInt("Age: ", &p.age);
    if (!ok || p.age <= 0 || p.age > 120) {
        printf("Bad age.\n");
        return;
    }

    printf("Gender: ");
    readLine(p.gender, 12);
    printf("Blood group: ");
    readLine(p.bloodGroup, 8);
    printf("Phone: ");
    readLine(p.phone, MAX_PHONE);
    printf("Emergency contact: ");
    readLine(p.emergencyContact, MAX_NAME);
    printf("Address: ");
    readLine(p.address, MAX_TEXT);
    printf("Condition: ");
    readLine(p.condition, MAX_CONDITION);

    p.doctorId = -1;
    p.roomNumber = 0;
    p.daysAdmitted = 0;
    p.isEmergency = 0;
    strcpy(p.status, "Admitted");
    todayDate(p.admitDate, MAX_DATE);
    p.dischargeDate[0] = '\0';
    updateTotal(&p);

    patients[patientCount] = p;
    patientCount++;

    printf("Patient added. Status set to Admitted.\n");
}

void emergencyAdmit(void) {
    Patient p;
    Room *r;
    int i, docIndex = -1;

    if (patientCount >= MAX_PATIENTS) {
        printf("Patient list full.\n");
        return;
    }

    memset(&p, 0, sizeof(p));
    p.id = meta.nextPatientId++;
    printf("\n*** Emergency admission ***\n");
    printf("Patient id: %d\n", p.id);

    printf("Name (or Unknown): ");
    readLine(p.name, MAX_NAME);
    if (p.name[0] == '\0')
        strcpy(p.name, "Unknown");

    printf("Age (0 if unknown): ");
    if (scanf("%d", &p.age) != 1)
        p.age = 0;
    clearInput();

    strcpy(p.gender, "Unknown");
    strcpy(p.bloodGroup, "N/A");

    printf("Phone (optional): ");
    readLine(p.phone, MAX_PHONE);
    printf("Emergency contact: ");
    readLine(p.emergencyContact, MAX_NAME);
    printf("What happened / condition: ");
    readLine(p.condition, MAX_CONDITION);

    /* try emergency room first, then ICU */
    r = findFreeRoomOfType("Emergency");
    if (r == NULL)
        r = findFreeRoomOfType("ICU");

    if (r != NULL) {
        r->occupied = 1;
        r->patientId = p.id;
        strcpy(r->status, "Occupied");
        p.roomNumber = r->number;
        printf("Got room %d (%s)\n", r->number, r->type);
    } else {
        printf("No free ER/ICU room right now.\n");
    }

    for (i = 0; i < doctorCount; i++) {
        if (doctors[i].available && strcasecmp(doctors[i].specialization, "Emergency Medicine") == 0) {
            docIndex = i;
            break;
        }
    }
    if (docIndex == -1) {
        for (i = 0; i < doctorCount; i++) {
            if (doctors[i].available) {
                docIndex = i;
                break;
            }
        }
    }

    if (docIndex != -1) {
        p.doctorId = doctors[docIndex].id;
        doctors[docIndex].available = 0;
        doctors[docIndex].patientsAssigned++;
        p.doctorFee = doctors[docIndex].consultationFee;
        printf("Doctor: %s\n", doctors[docIndex].name);
    }

    p.daysAdmitted = 1;
    p.isEmergency = 1;
    strcpy(p.status, "Emergency");
    todayDate(p.admitDate, MAX_DATE);
    updateTotal(&p);

    patients[patientCount++] = p;
    printf("Emergency patient saved.\n");
}

void searchPatient(void) {
    int mode, id, idx;
    char name[MAX_NAME];

    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    if (!readInt("Choice: ", &mode))
        return;

    if (mode == 1) {
        if (!readInt("Patient id: ", &id))
            return;
        idx = findPatientIndex(id);
    } else if (mode == 2) {
        printf("Name: ");
        readLine(name, MAX_NAME);
        idx = findPatientByName(name);
    } else {
        printf("Wrong choice.\n");
        return;
    }

    if (idx == -1) {
        printf("No patient found.\n");
        return;
    }
    showPatient(&patients[idx]);
}

void listPatients(void) {
    int filter, i, shown = 0;
    Patient *p;

    printf("1. All\n");
    printf("2. Currently here (admitted/emergency)\n");
    printf("3. Discharged\n");
    printf("4. Emergency only\n");
    if (!readInt("Show: ", &filter))
        return;

    printf("\nID    Name                 Age  Status       Room\n");
    for (i = 0; i < patientCount; i++) {
        p = &patients[i];
        if (filter == 2) {
            if (strcmp(p->status, "Admitted") != 0 && strcmp(p->status, "Emergency") != 0)
                continue;
        } else if (filter == 3) {
            if (strcmp(p->status, "Discharged") != 0)
                continue;
        } else if (filter == 4) {
            if (!p->isEmergency)
                continue;
        } else if (filter != 1) {
            printf("Bad filter.\n");
            return;
        }

        printf("%-5d %-20s %-4d %-12s %d\n", p->id, p->name, p->age, p->status, p->roomNumber);
        shown++;
    }

    if (shown == 0)
        printf("(empty)\n");
}

void updatePatient(void) {
    int id, idx, field;
    Patient *p;

    if (!readInt("Patient id: ", &id))
        return;
    idx = findPatientIndex(id);
    if (idx == -1) {
        printf("Not found.\n");
        return;
    }
    p = &patients[idx];

    if (strcmp(p->status, "Discharged") == 0) {
        printf("Already discharged, can't edit.\n");
        return;
    }

    printf("What do you want to change?\n");
    printf("1 name\n");
    printf("2 age\n");
    printf("3 condition\n");
    printf("4 phone\n");
    printf("5 days admitted\n");
    printf("6 address\n");
    if (!readInt("> ", &field))
        return;

    if (field == 1) {
        printf("New name: ");
        readLine(p->name, MAX_NAME);
    } else if (field == 2) {
        if (!readInt("New age: ", &p->age) || p->age <= 0) {
            printf("Invalid.\n");
            return;
        }
    } else if (field == 3) {
        printf("New condition: ");
        readLine(p->condition, MAX_CONDITION);
    } else if (field == 4) {
        printf("New phone: ");
        readLine(p->phone, MAX_PHONE);
    } else if (field == 5) {
        int days;
        int ri;
        if (!readInt("Days: ", &days) || days < 0) {
            printf("Invalid.\n");
            return;
        }
        p->daysAdmitted = days;
        if (p->roomNumber > 0) {
            ri = findRoomIndex(p->roomNumber);
            if (ri != -1) {
                p->roomCharges = p->daysAdmitted * rooms[ri].dailyRate;
                updateTotal(p);
            }
        }
    } else if (field == 6) {
        printf("New address: ");
        readLine(p->address, MAX_TEXT);
    } else {
        printf("Nope.\n");
        return;
    }

    printf("Ok, updated.\n");
}

void transferRoom(void) {
    int id, idx, newRoom, oldRi, newRi;
    Patient *p;

    if (!readInt("Patient id: ", &id))
        return;
    idx = findPatientIndex(id);
    if (idx == -1) {
        printf("Not found.\n");
        return;
    }
    p = &patients[idx];
    if (strcmp(p->status, "Discharged") == 0) {
        printf("Discharged patient.\n");
        return;
    }

    if (!readInt("Move to room number: ", &newRoom))
        return;
    newRi = findRoomIndex(newRoom);
    if (newRi == -1) {
        printf("That room doesn't exist.\n");
        return;
    }
    if (rooms[newRi].occupied || strcmp(rooms[newRi].status, "Available") != 0) {
        printf("Room not free.\n");
        return;
    }

    /* free old room if any */
    if (p->roomNumber > 0) {
        oldRi = findRoomIndex(p->roomNumber);
        if (oldRi != -1) {
            p->roomCharges += p->daysAdmitted * rooms[oldRi].dailyRate;
            rooms[oldRi].occupied = 0;
            rooms[oldRi].patientId = -1;
            strcpy(rooms[oldRi].status, "Available");
        }
    }

    rooms[newRi].occupied = 1;
    rooms[newRi].patientId = p->id;
    strcpy(rooms[newRi].status, "Occupied");
    p->roomNumber = newRoom;
    p->daysAdmitted = 0;
    updateTotal(p);

    printf("Moved to room %d.\n", newRoom);
}

void patientMenu(void) {
    int ch;

    while (1) {
        printf("\n-- Patients --\n");
        printf("1. Register\n");
        printf("2. Emergency admit\n");
        printf("3. Search\n");
        printf("4. List\n");
        printf("5. Update\n");
        printf("6. Transfer room\n");
        printf("7. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;

        if (ch == 1) registerPatient();
        else if (ch == 2) emergencyAdmit();
        else if (ch == 3) searchPatient();
        else if (ch == 4) listPatients();
        else if (ch == 5) updatePatient();
        else if (ch == 6) transferRoom();
        else if (ch == 7) return;
        else printf("Invalid option.\n");
    }
}
