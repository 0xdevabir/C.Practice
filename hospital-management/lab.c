#include "hospital.h"

void listLabTests(void) {
    int i;
    printf("\nAvailable tests:\n");
    for (i = 0; i < labCount; i++) {
        printf("%d. %s (%s) - %.0f Tk, ~%d hour(s)\n",
               labTests[i].id, labTests[i].name, labTests[i].category,
               labTests[i].price, labTests[i].turnaroundHours);
    }
}

void orderLabTest(void) {
    int pid, tid, pi, li;
    LabOrder o;

    if (labOrderCount >= MAX_LAB_ORDERS) {
        printf("Too many lab orders.\n");
        return;
    }

    if (!readInt("Patient id: ", &pid))
        return;
    pi = findPatientIndex(pid);
    if (pi < 0) {
        printf("Patient not found.\n");
        return;
    }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }

    listLabTests();
    if (!readInt("Test id: ", &tid))
        return;
    li = findLabIndex(tid);
    if (li < 0) {
        printf("No such test.\n");
        return;
    }

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

    printf("Ordered %s. Order id %d. Cost %.0f Tk\n",
           labTests[li].name, o.id, o.amount);
}

void completeLabOrder(void) {
    int id, i, found = -1;

    if (!readInt("Lab order id: ", &id))
        return;

    for (i = 0; i < labOrderCount; i++) {
        if (labOrders[i].id == id) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        printf("Not found.\n");
        return;
    }
    if (strcmp(labOrders[found].status, "Cancelled") == 0) {
        printf("This one was cancelled.\n");
        return;
    }

    strcpy(labOrders[found].status, "Completed");
    printf("Marked completed.\n");
}

void listLabOrders(void) {
    int i;
    printf("\nLab orders:\n");
    if (labOrderCount == 0) {
        printf("(none yet)\n");
        return;
    }
    for (i = 0; i < labOrderCount; i++) {
        printf("#%d patient=%d test=%d status=%s amount=%.0f date=%s\n",
               labOrders[i].id, labOrders[i].patientId, labOrders[i].labTestId,
               labOrders[i].status, labOrders[i].amount, labOrders[i].date);
    }
}

void labMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Lab --\n");
        printf("1. List tests\n");
        printf("2. Order test\n");
        printf("3. Complete order\n");
        printf("4. Show orders\n");
        printf("5. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) listLabTests();
        else if (ch == 2) orderLabTest();
        else if (ch == 3) completeLabOrder();
        else if (ch == 4) listLabOrders();
        else if (ch == 5) return;
        else printf("Invalid.\n");
    }
}
