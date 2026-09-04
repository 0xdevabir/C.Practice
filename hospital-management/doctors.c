#include "hospital.h"

void releaseDoctorFromPatient(int patientIndex) {
    int did, di;

    did = patients[patientIndex].doctorId;
    if (did < 0)
        return;

    di = findDoctorIndex(did);
    if (di < 0)
        return;

    if (doctors[di].patientsAssigned > 0)
        doctors[di].patientsAssigned--;

    /* free again if under max */
    if (doctors[di].patientsAssigned < doctors[di].maxPatients)
        doctors[di].available = 1;
}

void addDoctor(void) {
    Doctor d;

    if (doctorCount >= MAX_DOCTORS) {
        printf("Can't add more doctors.\n");
        return;
    }

    memset(&d, 0, sizeof(d));
    d.id = meta.nextDoctorId++;
    printf("Doctor id: %d\n", d.id);

    printf("Name: ");
    readLine(d.name, MAX_NAME);
    printf("Specialization: ");
    readLine(d.specialization, MAX_SPEC);
    printf("Department: ");
    readLine(d.department, MAX_DEPT);
    printf("Phone: ");
    readLine(d.phone, MAX_PHONE);

    if (!readDouble("Consultation fee: ", &d.consultationFee) || d.consultationFee < 0) {
        printf("Bad fee.\n");
        return;
    }

    if (!readInt("Max patients at once: ", &d.maxPatients) || d.maxPatients <= 0)
        d.maxPatients = 5;

    if (!readInt("Years experience: ", &d.yearsExperience) || d.yearsExperience < 0)
        d.yearsExperience = 0;

    d.available = 1;
    d.patientsAssigned = 0;
    doctors[doctorCount++] = d;
    printf("Doctor saved.\n");
}

void searchDoctor(void) {
    int mode, id, i, found;
    char key[MAX_SPEC];
    Doctor *d;

    printf("1. By id\n");
    printf("2. Available by specialization\n");
    printf("3. By department\n");
    if (!readInt("Choice: ", &mode))
        return;

    if (mode == 1) {
        if (!readInt("Doctor id: ", &id))
            return;
        i = findDoctorIndex(id);
        if (i < 0) {
            printf("Not found.\n");
            return;
        }
        d = &doctors[i];
        printf("\n%d - %s\n", d->id, d->name);
        printf("%s / %s\n", d->specialization, d->department);
        printf("Fee: %.0f  Phone: %s\n", d->consultationFee, d->phone);
        printf("Assigned: %d/%d  %s\n", d->patientsAssigned, d->maxPatients,
               d->available ? "available" : "busy");
        return;
    }

    if (mode == 2)
        printf("Specialization: ");
    else if (mode == 3)
        printf("Department: ");
    else {
        printf("Wrong choice.\n");
        return;
    }
    readLine(key, MAX_SPEC);

    found = 0;
    printf("\nID   Name                 Spec             Fee\n");
    for (i = 0; i < doctorCount; i++) {
        d = &doctors[i];
        if (mode == 2) {
            if (!d->available)
                continue;
            if (strcasecmp(d->specialization, key) != 0)
                continue;
        } else {
            if (strcasecmp(d->department, key) != 0)
                continue;
        }
        printf("%-4d %-20s %-16s %.0f\n", d->id, d->name, d->specialization, d->consultationFee);
        found = 1;
    }
    if (!found)
        printf("Nobody matched.\n");
}

void listDoctors(void) {
    int i;
    printf("\nAll doctors:\n");
    for (i = 0; i < doctorCount; i++) {
        printf("%d. %s (%s) fee=%.0f [%s]\n",
               doctors[i].id, doctors[i].name, doctors[i].specialization,
               doctors[i].consultationFee,
               doctors[i].available ? "free" : "busy");
    }
}

void updateDoctor(void) {
    int id, idx, field;
    Doctor *d;

    if (!readInt("Doctor id: ", &id))
        return;
    idx = findDoctorIndex(id);
    if (idx < 0) {
        printf("Not found.\n");
        return;
    }
    d = &doctors[idx];

    printf("1. Change fee\n");
    printf("2. Change phone\n");
    printf("3. Change max patients\n");
    printf("4. Toggle available/busy\n");
    if (!readInt("Field: ", &field))
        return;

    if (field == 1) {
        if (!readDouble("New fee: ", &d->consultationFee) || d->consultationFee < 0) {
            printf("Invalid.\n");
            return;
        }
    } else if (field == 2) {
        printf("Phone: ");
        readLine(d->phone, MAX_PHONE);
    } else if (field == 3) {
        if (!readInt("Max patients: ", &d->maxPatients) || d->maxPatients <= 0) {
            printf("Invalid.\n");
            return;
        }
    } else if (field == 4) {
        d->available = !d->available;
        printf("Now %s\n", d->available ? "available" : "unavailable");
    } else {
        printf("Invalid.\n");
        return;
    }
    printf("Done.\n");
}

void assignDoctor(void) {
    int pid, did, pi, di;

    if (!readInt("Patient id: ", &pid))
        return;
    if (!readInt("Doctor id: ", &did))
        return;

    pi = findPatientIndex(pid);
    if (pi < 0) {
        printf("Patient not found.\n");
        return;
    }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("That patient is discharged.\n");
        return;
    }

    di = findDoctorIndex(did);
    if (di < 0) {
        printf("Doctor not found.\n");
        return;
    }
    if (!doctors[di].available) {
        printf("Doctor is busy.\n");
        return;
    }
    if (doctors[di].patientsAssigned >= doctors[di].maxPatients) {
        printf("Doctor already has too many patients.\n");
        return;
    }

    if (patients[pi].doctorId != -1)
        releaseDoctorFromPatient(pi);

    patients[pi].doctorId = did;
    patients[pi].doctorFee = doctors[di].consultationFee;
    doctors[di].patientsAssigned++;
    if (doctors[di].patientsAssigned >= doctors[di].maxPatients)
        doctors[di].available = 0;

    patients[pi].totalBill = patients[pi].roomCharges + patients[pi].doctorFee +
                             patients[pi].medicineCharges + patients[pi].labCharges -
                             patients[pi].discount;

    printf("%s is now assigned to %s.\n", doctors[di].name, patients[pi].name);
}

void doctorMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Doctors --\n");
        printf("1. Add doctor\n");
        printf("2. Search\n");
        printf("3. List all\n");
        printf("4. Update\n");
        printf("5. Assign to patient\n");
        printf("6. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;

        if (ch == 1) addDoctor();
        else if (ch == 2) searchDoctor();
        else if (ch == 3) listDoctors();
        else if (ch == 4) updateDoctor();
        else if (ch == 5) assignDoctor();
        else if (ch == 6) return;
        else printf("Invalid.\n");
    }
}
