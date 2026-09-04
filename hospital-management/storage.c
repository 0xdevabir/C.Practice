#include "hospital.h"

/* sample doctors so the program is usable without adding everything first */
static void seedDoctors(void) {
    Doctor d[10];
    int i;

    d[0] = (Doctor){101, "Dr. Rahman", "Cardiology", "Cardiac Care", "01711000001", 1, 1500, 0, 8, 12};
    d[1] = (Doctor){102, "Dr. Sultana", "Neurology", "Neuro", "01711000002", 1, 1800, 0, 6, 15};
    d[2] = (Doctor){103, "Dr. Hasan", "Orthopedics", "Ortho", "01711000003", 1, 1400, 0, 10, 10};
    d[3] = (Doctor){104, "Dr. Karim", "Cardiology", "Cardiac Care", "01711000004", 1, 1200, 0, 8, 8};
    d[4] = (Doctor){105, "Dr. Akter", "Pediatrics", "Child Care", "01711000005", 1, 1000, 0, 12, 9};
    d[5] = (Doctor){106, "Dr. Naznin", "Gynecology", "Women Health", "01711000006", 1, 1600, 0, 8, 14};
    d[6] = (Doctor){107, "Dr. Imran", "Emergency Medicine", "ER", "01711000007", 1, 2000, 0, 15, 7};
    d[7] = (Doctor){108, "Dr. Farhana", "Dermatology", "Skin", "01711000008", 1, 1100, 0, 10, 6};
    d[8] = (Doctor){109, "Dr. Kabir", "General Medicine", "OPD", "01711000009", 1, 800, 0, 20, 20};
    d[9] = (Doctor){110, "Dr. Mehnaz", "Oncology", "Cancer Care", "01711000010", 1, 2500, 0, 5, 18};

    doctorCount = 10;
    for (i = 0; i < doctorCount; i++)
        doctors[i] = d[i];
    meta.nextDoctorId = 111;
}

static void seedRooms(void) {
    int i, n = 0;

    /* floor 1 - general wards */
    for (i = 101; i <= 110; i++) {
        rooms[n].number = i;
        strcpy(rooms[n].type, "General");
        strcpy(rooms[n].floor, "1");
        rooms[n].dailyRate = 2000;
        rooms[n].occupied = 0;
        rooms[n].patientId = -1;
        strcpy(rooms[n].status, "Available");
        n++;
    }

    /* private rooms are more expensive */
    for (i = 201; i <= 208; i++) {
        rooms[n].number = i;
        strcpy(rooms[n].type, "Private");
        strcpy(rooms[n].floor, "2");
        rooms[n].dailyRate = 4500;
        rooms[n].occupied = 0;
        rooms[n].patientId = -1;
        strcpy(rooms[n].status, "Available");
        n++;
    }

    for (i = 301; i <= 306; i++) {
        rooms[n].number = i;
        strcpy(rooms[n].type, "ICU");
        strcpy(rooms[n].floor, "3");
        rooms[n].dailyRate = 8000;
        rooms[n].occupied = 0;
        rooms[n].patientId = -1;
        strcpy(rooms[n].status, "Available");
        n++;
    }

    for (i = 401; i <= 404; i++) {
        rooms[n].number = i;
        strcpy(rooms[n].type, "Emergency");
        strcpy(rooms[n].floor, "G");
        rooms[n].dailyRate = 3500;
        rooms[n].occupied = 0;
        rooms[n].patientId = -1;
        strcpy(rooms[n].status, "Available");
        n++;
    }

    roomCount = n;
}

static void seedMedicines(void) {
    /* prices are approx, not real pharmacy prices */
    medicines[0] = (Medicine){1, "Paracetamol 500mg", "Analgesic", 5, 500, 50};
    medicines[1] = (Medicine){2, "Amoxicillin 250mg", "Antibiotic", 12, 300, 40};
    medicines[2] = (Medicine){3, "Omeprazole 20mg", "Gastro", 8, 250, 30};
    medicines[3] = (Medicine){4, "Amlodipine 5mg", "Cardiac", 10, 200, 25};
    medicines[4] = (Medicine){5, "Metformin 500mg", "Diabetes", 6, 400, 40};
    medicines[5] = (Medicine){6, "Cetirizine 10mg", "Allergy", 4, 350, 30};
    medicines[6] = (Medicine){7, "ORS Sachet", "Electrolyte", 15, 180, 20};
    medicines[7] = (Medicine){8, "Insulin Vial", "Diabetes", 450, 40, 10};
    medicines[8] = (Medicine){9, "Saline 500ml", "IV Fluid", 80, 120, 20};
    medicines[9] = (Medicine){10, "Azithromycin 500mg", "Antibiotic", 25, 150, 20};
    medicines[10] = (Medicine){11, "Ibuprofen 400mg", "Analgesic", 7, 280, 30};
    medicines[11] = (Medicine){12, "Vitamin D3", "Supplement", 20, 200, 25};
    medCount = 12;
    meta.nextMedId = 13;
}

static void seedLabs(void) {
    labTests[0] = (LabTest){1, "Complete Blood Count", "Hematology", 500, 4};
    labTests[1] = (LabTest){2, "Blood Glucose (FBS)", "Biochemistry", 250, 2};
    labTests[2] = (LabTest){3, "Lipid Profile", "Biochemistry", 800, 6};
    labTests[3] = (LabTest){4, "Liver Function Test", "Biochemistry", 900, 8};
    labTests[4] = (LabTest){5, "Kidney Function Test", "Biochemistry", 850, 8};
    labTests[5] = (LabTest){6, "ECG", "Cardiology", 600, 1};
    labTests[6] = (LabTest){7, "Chest X-Ray", "Radiology", 700, 2};
    labTests[7] = (LabTest){8, "Urine R/E", "Pathology", 200, 3};
    labTests[8] = (LabTest){9, "COVID Antigen", "Infectious", 450, 1};
    labTests[9] = (LabTest){10, "MRI Brain", "Radiology", 8000, 24};
    labCount = 10;
    meta.nextLabId = 11;
}

void seedAll(void) {
    patientCount = 0;
    apptCount = 0;
    prescCount = 0;
    labOrderCount = 0;

    meta.nextPatientId = 1001;
    meta.nextApptId = 5001;
    meta.nextPrescId = 1;
    meta.nextLabOrderId = 1;

    seedDoctors();
    seedRooms();
    seedMedicines();
    seedLabs();

    printf("Loaded default doctors/rooms/pharmacy/lab data.\n");
}

static int writeArr(const char *path, const void *data, size_t size, int count) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL)
        return 0;
    fwrite(&count, sizeof(int), 1, fp);
    if (count > 0)
        fwrite(data, size, (size_t)count, fp);
    fclose(fp);
    return 1;
}

static int readArr(const char *path, void *data, size_t size, int max, int *count) {
    FILE *fp = fopen(path, "rb");
    int c;

    if (fp == NULL)
        return 0;

    if (fread(&c, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }

    if (c < 0 || c > max) {
        fclose(fp);
        return 0;
    }

    if (c > 0) {
        if (fread(data, size, (size_t)c, fp) != (size_t)c) {
            fclose(fp);
            return 0;
        }
    }

    *count = c;
    fclose(fp);
    return 1;
}

int saveAll(void) {
    FILE *fp;
    int ok = 1;

    ensureDataDir();

    ok = writeArr(F_PATIENTS, patients, sizeof(Patient), patientCount) && ok;
    ok = writeArr(F_DOCTORS, doctors, sizeof(Doctor), doctorCount) && ok;
    ok = writeArr(F_ROOMS, rooms, sizeof(Room), roomCount) && ok;
    ok = writeArr(F_APPTS, appointments, sizeof(Appointment), apptCount) && ok;
    ok = writeArr(F_MEDS, medicines, sizeof(Medicine), medCount) && ok;
    ok = writeArr(F_LABS, labTests, sizeof(LabTest), labCount) && ok;
    ok = writeArr(F_PRESC, prescriptions, sizeof(Prescription), prescCount) && ok;
    ok = writeArr(F_LABORD, labOrders, sizeof(LabOrder), labOrderCount) && ok;

    fp = fopen(F_META, "wb");
    if (fp == NULL)
        return 0;
    fwrite(&meta, sizeof(Meta), 1, fp);
    fclose(fp);

    return ok;
}

int loadAll(void) {
    FILE *fp;
    int ok;

    ensureDataDir();

    ok = readArr(F_PATIENTS, patients, sizeof(Patient), MAX_PATIENTS, &patientCount);
    ok = readArr(F_DOCTORS, doctors, sizeof(Doctor), MAX_DOCTORS, &doctorCount) && ok;
    ok = readArr(F_ROOMS, rooms, sizeof(Room), MAX_ROOMS, &roomCount) && ok;
    ok = readArr(F_APPTS, appointments, sizeof(Appointment), MAX_APPTS, &apptCount) && ok;
    ok = readArr(F_MEDS, medicines, sizeof(Medicine), MAX_MEDS, &medCount) && ok;
    ok = readArr(F_LABS, labTests, sizeof(LabTest), MAX_LABS, &labCount) && ok;
    ok = readArr(F_PRESC, prescriptions, sizeof(Prescription), MAX_PRESCRIPTIONS, &prescCount) && ok;
    ok = readArr(F_LABORD, labOrders, sizeof(LabOrder), MAX_LAB_ORDERS, &labOrderCount) && ok;

    fp = fopen(F_META, "rb");
    if (fp == NULL)
        return 0;
    if (fread(&meta, sizeof(Meta), 1, fp) != 1)
        ok = 0;
    fclose(fp);

    return ok;
}
