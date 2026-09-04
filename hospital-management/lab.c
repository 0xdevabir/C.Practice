#include "hospital.h"

void listLabTests(void) {
    printf("\n%-6s %-28s %-14s %-8s %-8s\n",
           "ID", "Test", "Category", "Price", "Hours");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < labCount; i++) {
        LabTest *t = &labTests[i];
        printf("%-6d %-28s %-14s %-8.0f %-8d\n",
               t->id, t->name, t->category, t->price, t->turnaroundHours);
    }
}

void orderLabTest(void) {
    if (labOrderCount >= MAX_LAB_ORDERS) {
        printf("Lab order capacity full.\n");
        return;
    }
    int pid, tid;
    if (!readInt("Patient ID: ", &pid)) return;
    int pi = findPatientIndex(pid);
    if (pi < 0) { printf("Patient not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }
    listLabTests();
    if (!readInt("Lab Test ID: ", &tid)) return;
    int li = findLabIndex(tid);
    if (li < 0) { printf("Test not found.\n"); return; }

    LabOrder o;
    o.id = meta.nextLabOrderId++;
    o.patientId = pid;
    o.labTestId = tid;
    strcpy(o.status, "Ordered");
    o.amount = labTests[li].price;
    todayDate(o.date, MAX_DATE);
    labOrders[labOrderCount++] = o;

    patients[pi].labCharges += o.amount;
    patients[pi].totalBill = patients[pi].roomCharges + patients[pi].doctorFee +
                             patients[pi].medicineCharges + patients[pi].labCharges -
                             patients[pi].discount;
    printf("Lab order #%d placed: %s (Tk. %.0f) ETA ~%dh\n",
           o.id, labTests[li].name, o.amount, labTests[li].turnaroundHours);
}

void completeLabOrder(void) {
    int id;
    if (!readInt("Lab Order ID: ", &id)) return;
    int oi = -1;
    for (int i = 0; i < labOrderCount; i++) {
        if (labOrders[i].id == id) { oi = i; break; }
    }
    if (oi < 0) { printf("Not found.\n"); return; }
    if (strcmp(labOrders[oi].status, "Cancelled") == 0) {
        printf("Order cancelled.\n");
        return;
    }
    strcpy(labOrders[oi].status, "Completed");
    printf("Lab order #%d marked Completed.\n", id);
}

void listLabOrders(void) {
    printf("\n%-6s %-8s %-8s %-12s %-10s\n",
           "Order", "Patient", "TestID", "Status", "Amount");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < labOrderCount; i++) {
        LabOrder *o = &labOrders[i];
        printf("%-6d %-8d %-8d %-12s %-10.0f\n",
               o->id, o->patientId, o->labTestId, o->status, o->amount);
    }
}

void labMenu(void) {
    int c;
    while (1) {
        printf("\n=== LABORATORY ===\n");
        printf("1. List Lab Tests\n");
        printf("2. Order Lab Test\n");
        printf("3. Complete Lab Order\n");
        printf("4. List Lab Orders\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: listLabTests(); break;
            case 2: orderLabTest(); break;
            case 3: completeLabOrder(); break;
            case 4: listLabOrders(); break;
            case 5: return;
            default: printf("Invalid.\n");
        }
    }
}
