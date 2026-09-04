#include "hospital.h"

void scheduleAppointment(void) {
    Appointment a;
    int i;

    if (apptCount >= MAX_APPTS) {
        printf("Too many appointments.\n");
        return;
    }

    memset(&a, 0, sizeof(a));
    a.id = meta.nextApptId++;

    if (!readInt("Patient id: ", &a.patientId))
        return;
    if (findPatientIndex(a.patientId) < 0) {
        printf("Register the patient first.\n");
        return;
    }

    if (!readInt("Doctor id: ", &a.doctorId))
        return;
    if (findDoctorIndex(a.doctorId) < 0) {
        printf("Doctor id wrong.\n");
        return;
    }

    printf("Date (DD/MM/YYYY): ");
    readLine(a.date, MAX_DATE);
    printf("Time (like 10:30): ");
    readLine(a.timeSlot, MAX_TIME);
    printf("Reason: ");
    readLine(a.reason, MAX_TEXT);
    strcpy(a.status, "Scheduled");

    /* don't double book same doctor same slot */
    for (i = 0; i < apptCount; i++) {
        if (appointments[i].doctorId == a.doctorId &&
            strcmp(appointments[i].date, a.date) == 0 &&
            strcmp(appointments[i].timeSlot, a.timeSlot) == 0 &&
            strcmp(appointments[i].status, "Cancelled") != 0) {
            printf("That slot is taken.\n");
            return;
        }
    }

    appointments[apptCount++] = a;
    printf("Appointment booked. id = %d\n", a.id);
}

void listAppointments(void) {
    int filter, i, docId = 0;
    char date[MAX_DATE];

    printf("1. All\n");
    printf("2. Only scheduled\n");
    printf("3. One doctor\n");
    printf("4. One date\n");
    if (!readInt("Filter: ", &filter))
        return;

    if (filter == 3) {
        if (!readInt("Doctor id: ", &docId))
            return;
    }
    if (filter == 4) {
        printf("Date: ");
        readLine(date, MAX_DATE);
    }

    printf("\nAppt  Pat   Doc   Date         Time   Status\n");
    for (i = 0; i < apptCount; i++) {
        if (filter == 2 && strcmp(appointments[i].status, "Scheduled") != 0)
            continue;
        if (filter == 3 && appointments[i].doctorId != docId)
            continue;
        if (filter == 4 && strcmp(appointments[i].date, date) != 0)
            continue;

        printf("%-5d %-5d %-5d %-12s %-6s %s  (%s)\n",
               appointments[i].id, appointments[i].patientId, appointments[i].doctorId,
               appointments[i].date, appointments[i].timeSlot,
               appointments[i].status, appointments[i].reason);
    }
}

void updateAppointmentStatus(void) {
    int id, ai, c;

    if (!readInt("Appointment id: ", &id))
        return;
    ai = findApptIndex(id);
    if (ai < 0) {
        printf("Not found.\n");
        return;
    }

    printf("1 Completed\n");
    printf("2 No show\n");
    printf("3 Back to scheduled\n");
    if (!readInt("Set to: ", &c))
        return;

    if (c == 1)
        strcpy(appointments[ai].status, "Completed");
    else if (c == 2)
        strcpy(appointments[ai].status, "NoShow");
    else if (c == 3)
        strcpy(appointments[ai].status, "Scheduled");
    else {
        printf("Invalid.\n");
        return;
    }
    printf("Status is now %s\n", appointments[ai].status);
}

void cancelAppointment(void) {
    int id, ai;

    if (!readInt("Appointment id: ", &id))
        return;
    ai = findApptIndex(id);
    if (ai < 0) {
        printf("Not found.\n");
        return;
    }
    if (strcmp(appointments[ai].status, "Cancelled") == 0) {
        printf("Already cancelled.\n");
        return;
    }
    strcpy(appointments[ai].status, "Cancelled");
    printf("Cancelled.\n");
}

void appointmentMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Appointments --\n");
        printf("1. Schedule\n");
        printf("2. List\n");
        printf("3. Update status\n");
        printf("4. Cancel\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) scheduleAppointment();
        else if (ch == 2) listAppointments();
        else if (ch == 3) updateAppointmentStatus();
        else if (ch == 4) cancelAppointment();
        else if (ch == 5) return;
        else printf("Invalid.\n");
    }
}
