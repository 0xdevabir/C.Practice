#include "hospital.h"

void addMedicine(void) {
    Medicine m;

    if (medCount >= MAX_MEDS) {
        printf("Medicine list full.\n");
        return;
    }

    memset(&m, 0, sizeof(m));
    m.id = meta.nextMedId++;
    printf("Medicine id: %d\n", m.id);

    printf("Name: ");
    readLine(m.name, MAX_NAME);
    printf("Category: ");
    readLine(m.category, 30);

    if (!readDouble("Price: ", &m.price) || m.price < 0) {
        printf("Bad price.\n");
        return;
    }
    if (!readInt("Stock: ", &m.stock) || m.stock < 0) {
        printf("Bad stock.\n");
        return;
    }
    if (!readInt("Reorder when below: ", &m.reorderLevel) || m.reorderLevel < 0)
        m.reorderLevel = 10;

    medicines[medCount++] = m;
    printf("Added.\n");
}

void listMedicines(void) {
    int i;
    printf("\nID  Name                     Cat            Price  Stock\n");
    for (i = 0; i < medCount; i++) {
        printf("%-3d %-24s %-14s %-6.0f %-5d",
               medicines[i].id, medicines[i].name, medicines[i].category,
               medicines[i].price, medicines[i].stock);
        if (medicines[i].stock <= medicines[i].reorderLevel)
            printf("  << low");
        printf("\n");
    }
}

void updateMedicineStock(void) {
    int id, mi, ch, qty;
    double price;

    if (!readInt("Medicine id: ", &id))
        return;
    mi = findMedIndex(id);
    if (mi < 0) {
        printf("Not found.\n");
        return;
    }

    printf("1. Add to stock\n");
    printf("2. Set stock number\n");
    printf("3. Change price\n");
    if (!readInt("Choice: ", &ch))
        return;

    if (ch == 1) {
        if (!readInt("How many to add: ", &qty) || qty <= 0) {
            printf("Invalid.\n");
            return;
        }
        medicines[mi].stock += qty;
    } else if (ch == 2) {
        if (!readInt("New stock: ", &qty) || qty < 0) {
            printf("Invalid.\n");
            return;
        }
        medicines[mi].stock = qty;
    } else if (ch == 3) {
        if (!readDouble("New price: ", &price) || price < 0) {
            printf("Invalid.\n");
            return;
        }
        medicines[mi].price = price;
    } else {
        printf("Invalid.\n");
        return;
    }

    printf("Stock now %d, price %.0f\n", medicines[mi].stock, medicines[mi].price);
}

void prescribeMedicine(void) {
    int pid, mid, qty, pi, mi;
    Prescription pr;

    if (prescCount >= MAX_PRESCRIPTIONS) {
        printf("Prescription log full.\n");
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
        printf("Patient is discharged.\n");
        return;
    }

    listMedicines();
    if (!readInt("Medicine id: ", &mid))
        return;
    mi = findMedIndex(mid);
    if (mi < 0) {
        printf("Medicine not found.\n");
        return;
    }

    if (!readInt("Quantity: ", &qty) || qty <= 0) {
        printf("Bad quantity.\n");
        return;
    }
    if (medicines[mi].stock < qty) {
        printf("Only %d left in stock.\n", medicines[mi].stock);
        return;
    }

    medicines[mi].stock -= qty;

    pr.id = meta.nextPrescId++;
    pr.patientId = pid;
    pr.medicineId = mid;
    pr.quantity = qty;
    pr.amount = qty * medicines[mi].price;
    todayDate(pr.date, MAX_DATE);
    prescriptions[prescCount++] = pr;

    patients[pi].medicineCharges += pr.amount;
    patients[pi].totalBill = patients[pi].roomCharges + patients[pi].doctorFee +
                             patients[pi].medicineCharges + patients[pi].labCharges -
                             patients[pi].discount;

    printf("Given %s x%d = %.0f Tk\n", medicines[mi].name, qty, pr.amount);
}

void lowStockAlert(void) {
    int i, found = 0;
    printf("\nLow stock:\n");
    for (i = 0; i < medCount; i++) {
        if (medicines[i].stock <= medicines[i].reorderLevel) {
            printf("- %s (id %d): %d left, reorder at %d\n",
                   medicines[i].name, medicines[i].id,
                   medicines[i].stock, medicines[i].reorderLevel);
            found = 1;
        }
    }
    if (!found)
        printf("Everything looks fine.\n");
}

void pharmacyMenu(void) {
    int ch;
    while (1) {
        printf("\n-- Pharmacy --\n");
        printf("1. Add medicine\n");
        printf("2. List medicines\n");
        printf("3. Update stock/price\n");
        printf("4. Prescribe\n");
        printf("5. Low stock check\n");
        printf("6. Back\n");
        if (!readInt("Choice: ", &ch))
            continue;
        if (ch == 1) addMedicine();
        else if (ch == 2) listMedicines();
        else if (ch == 3) updateMedicineStock();
        else if (ch == 4) prescribeMedicine();
        else if (ch == 5) lowStockAlert();
        else if (ch == 6) return;
        else printf("Invalid.\n");
    }
}
