#include "hospital.h"

void releaseDoctorFromPatient(int patientIndex) {
    int did = patients[patientIndex].doctorId;
    if (did < 0) return;
    int di = findDoctorIndex(did);
    if (di < 0) return;
    if (doctors[di].patientsAssigned > 0) doctors[di].patientsAssigned--;
    if (doctors[di].patientsAssigned < doctors[di].maxPatients) {
        doctors[di].available = 1;
    }
}

void addDoctor(void) {
    if (doctorCount >= MAX_DOCTORS) {
        printf("Doctor list full.\n");
        return;
    }
    Doctor d;
    memset(&d, 0, sizeof(d));
    d.id = meta.nextDoctorId++;
    printf("Auto Doctor ID: %d\n", d.id);
    printf("Name: ");
    readLine(d.name, MAX_NAME);
    printf("Specialization: ");
    readLine(d.specialization, MAX_SPEC);
    printf("Department: ");
    readLine(d.department, MAX_DEPT);
    printf("Phone: ");
    readLine(d.phone, MAX_PHONE);
    if (!readDouble("Consultation Fee: ", &d.consultationFee) || d.consultationFee < 0) {
        printf("Invalid fee.\n");
        return;
    }
    if (!readInt("Max concurrent patients: ", &d.maxPatients) || d.maxPatients <= 0) {
        d.maxPatients = 5;
    }
    if (!readInt("Years of experience: ", &d.yearsExperience) || d.yearsExperience < 0) {
        d.yearsExperience = 0;
    }
    d.available = 1;
    d.patientsAssigned = 0;
    doctors[doctorCount++] = d;
    printf("Doctor added.\n");
}

void searchDoctor(void) {
    int mode;
    printf("1. By ID  2. By Specialization (available only)  3. By Department\n");
    if (!readInt("Choice: ", &mode)) return;

    if (mode == 1) {
        int id;
        if (!readInt("Doctor ID: ", &id)) return;
        int di = findDoctorIndex(id);
        if (di < 0) { printf("Not found.\n"); return; }
        Doctor *d = &doctors[di];
        printf("\nID %d | %s | %s | Dept: %s\n", d->id, d->name, d->specialization, d->department);
        printf("Phone %s | Fee %.0f | Exp %d yrs | Assigned %d/%d | %s\n",
               d->phone, d->consultationFee, d->yearsExperience,
               d->patientsAssigned, d->maxPatients,
               d->available ? "Available" : "Busy");
        return;
    }

    char key[MAX_SPEC];
    printf(mode == 2 ? "Specialization: " : "Department: ");
    readLine(key, MAX_SPEC);
    printf("\n%-6s %-20s %-16s %-10s %-10s\n", "ID", "Name", "Spec", "Fee", "Status");
    int found = 0;
    for (int i = 0; i < doctorCount; i++) {
        Doctor *d = &doctors[i];
        int match = 0;
        if (mode == 2) {
            match = d->available && strcasecmp(d->specialization, key) == 0;
        } else {
            match = strcasecmp(d->department, key) == 0;
        }
        if (!match) continue;
        printf("%-6d %-20s %-16s %-10.0f %-10s\n",
               d->id, d->name, d->specialization, d->consultationFee,
               d->available ? "Available" : "Busy");
        found = 1;
    }
    if (!found) printf("No matching doctors.\n");
}

void listDoctors(void) {
    printf("\n%-6s %-20s %-16s %-14s %-8s %-8s\n",
           "ID", "Name", "Specialization", "Department", "Fee", "Status");
    printf("------------------------------------------------------------------------------\n");
    for (int i = 0; i < doctorCount; i++) {
        Doctor *d = &doctors[i];
        printf("%-6d %-20s %-16s %-14s %-8.0f %-8s\n",
               d->id, d->name, d->specialization, d->department,
               d->consultationFee, d->available ? "Free" : "Busy");
    }
}

void updateDoctor(void) {
    int id;
    if (!readInt("Doctor ID: ", &id)) return;
    int di = findDoctorIndex(id);
    if (di < 0) { printf("Not found.\n"); return; }
    Doctor *d = &doctors[di];
    int c;
    printf("1.Fee 2.Phone 3.Max patients 4.Toggle availability\n");
    if (!readInt("Field: ", &c)) return;
    switch (c) {
        case 1:
            if (!readDouble("New fee: ", &d->consultationFee) || d->consultationFee < 0) {
                printf("Invalid.\n"); return;
            }
            break;
        case 2: printf("New phone: "); readLine(d->phone, MAX_PHONE); break;
        case 3:
            if (!readInt("Max patients: ", &d->maxPatients) || d->maxPatients <= 0) {
                printf("Invalid.\n"); return;
            }
            break;
        case 4:
            d->available = !d->available;
            printf("Now: %s\n", d->available ? "Available" : "Unavailable");
            break;
        default: printf("Invalid.\n"); return;
    }
    printf("Updated.\n");
}

void assignDoctor(void) {
    int pid, did;
    if (!readInt("Patient ID: ", &pid)) return;
    if (!readInt("Doctor ID: ", &did)) return;
    int pi = findPatientIndex(pid);
    if (pi < 0) { printf("Patient not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }
    int di = findDoctorIndex(did);
    if (di < 0) { printf("Doctor not found.\n"); return; }
    if (!doctors[di].available) {
        printf("Doctor unavailable.\n");
        return;
    }
    if (doctors[di].patientsAssigned >= doctors[di].maxPatients) {
        printf("Doctor at max patient load.\n");
        return;
    }
    if (patients[pi].doctorId != -1) {
        releaseDoctorFromPatient(pi);
    }
    patients[pi].doctorId = did;
    patients[pi].doctorFee = doctors[di].consultationFee;
    doctors[di].patientsAssigned++;
    if (doctors[di].patientsAssigned >= doctors[di].maxPatients) {
        doctors[di].available = 0;
    }
    patients[pi].totalBill = patients[pi].roomCharges + patients[pi].doctorFee +
                             patients[pi].medicineCharges + patients[pi].labCharges -
                             patients[pi].discount;
    printf("Assigned %s to %s.\n", doctors[di].name, patients[pi].name);
}

void doctorMenu(void) {
    int c;
    while (1) {
        printf("\n=== DOCTOR MANAGEMENT ===\n");
        printf("1. Add Doctor\n");
        printf("2. Search Doctor\n");
        printf("3. List Doctors\n");
        printf("4. Update Doctor\n");
        printf("5. Assign Doctor to Patient\n");
        printf("6. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: addDoctor(); break;
            case 2: searchDoctor(); break;
            case 3: listDoctors(); break;
            case 4: updateDoctor(); break;
            case 5: assignDoctor(); break;
            case 6: return;
            default: printf("Invalid.\n");
        }
    }
}
