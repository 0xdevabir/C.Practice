#include "hospital.h"

void scheduleAppointment(void) {
    if (apptCount >= MAX_APPTS) {
        printf("Appointment capacity full.\n");
        return;
    }
    Appointment a;
    memset(&a, 0, sizeof(a));
    a.id = meta.nextApptId++;

    if (!readInt("Patient ID: ", &a.patientId)) return;
    if (findPatientIndex(a.patientId) < 0) {
        printf("Patient not found. Register first.\n");
        return;
    }
    if (!readInt("Doctor ID: ", &a.doctorId)) return;
    if (findDoctorIndex(a.doctorId) < 0) {
        printf("Doctor not found.\n");
        return;
    }
    printf("Date (DD/MM/YYYY): ");
    readLine(a.date, MAX_DATE);
    printf("Time (HH:MM): ");
    readLine(a.timeSlot, MAX_TIME);
    printf("Reason: ");
    readLine(a.reason, MAX_TEXT);
    strcpy(a.status, "Scheduled");

    for (int i = 0; i < apptCount; i++) {
        if (appointments[i].doctorId == a.doctorId &&
            strcmp(appointments[i].date, a.date) == 0 &&
            strcmp(appointments[i].timeSlot, a.timeSlot) == 0 &&
            strcmp(appointments[i].status, "Cancelled") != 0) {
            printf("Doctor already booked at that slot.\n");
            return;
        }
    }
    appointments[apptCount++] = a;
    printf("Appointment #%d scheduled.\n", a.id);
}

void listAppointments(void) {
    int filter;
    printf("1.All 2.Scheduled 3.By doctor 4.By date\n");
    if (!readInt("Filter: ", &filter)) return;
    int docId = 0;
    char date[MAX_DATE] = "";
    if (filter == 3) {
        if (!readInt("Doctor ID: ", &docId)) return;
    }
    if (filter == 4) {
        printf("Date: ");
        readLine(date, MAX_DATE);
    }
    printf("\n%-6s %-8s %-8s %-12s %-8s %-12s %s\n",
           "Appt", "Patient", "Doctor", "Date", "Time", "Status", "Reason");
    printf("------------------------------------------------------------------------------\n");
    for (int i = 0; i < apptCount; i++) {
        Appointment *a = &appointments[i];
        int show = 1;
        if (filter == 2 && strcmp(a->status, "Scheduled") != 0) show = 0;
        if (filter == 3 && a->doctorId != docId) show = 0;
        if (filter == 4 && strcmp(a->date, date) != 0) show = 0;
        if (!show) continue;
        printf("%-6d %-8d %-8d %-12s %-8s %-12s %s\n",
               a->id, a->patientId, a->doctorId, a->date, a->timeSlot,
               a->status, a->reason);
    }
}

void updateAppointmentStatus(void) {
    int id, c;
    if (!readInt("Appointment ID: ", &id)) return;
    int ai = findApptIndex(id);
    if (ai < 0) { printf("Not found.\n"); return; }
    printf("1.Completed 2.NoShow 3.Scheduled\n");
    if (!readInt("New status: ", &c)) return;
    if (c == 1) strcpy(appointments[ai].status, "Completed");
    else if (c == 2) strcpy(appointments[ai].status, "NoShow");
    else if (c == 3) strcpy(appointments[ai].status, "Scheduled");
    else { printf("Invalid.\n"); return; }
    printf("Updated to %s.\n", appointments[ai].status);
}

void cancelAppointment(void) {
    int id;
    if (!readInt("Appointment ID: ", &id)) return;
    int ai = findApptIndex(id);
    if (ai < 0) { printf("Not found.\n"); return; }
    if (strcmp(appointments[ai].status, "Cancelled") == 0) {
        printf("Already cancelled.\n");
        return;
    }
    strcpy(appointments[ai].status, "Cancelled");
    printf("Appointment cancelled.\n");
}

void appointmentMenu(void) {
    int c;
    while (1) {
        printf("\n=== APPOINTMENTS ===\n");
        printf("1. Schedule Appointment\n");
        printf("2. List Appointments\n");
        printf("3. Update Status\n");
        printf("4. Cancel Appointment\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: scheduleAppointment(); break;
            case 2: listAppointments(); break;
            case 3: updateAppointmentStatus(); break;
            case 4: cancelAppointment(); break;
            case 5: return;
            default: printf("Invalid.\n");
        }
    }
}
