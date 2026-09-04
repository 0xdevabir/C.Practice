#include "hospital.h"

void addMedicine(void) {
    if (medCount >= MAX_MEDS) { printf("Medicine list full.\n"); return; }
    Medicine m;
    memset(&m, 0, sizeof(m));
    m.id = meta.nextMedId++;
    printf("Auto Med ID: %d\n", m.id);
    printf("Name: ");
    readLine(m.name, MAX_NAME);
    printf("Category: ");
    readLine(m.category, 30);
    if (!readDouble("Price: ", &m.price) || m.price < 0) {
        printf("Invalid price.\n"); return;
    }
    if (!readInt("Stock qty: ", &m.stock) || m.stock < 0) {
        printf("Invalid stock.\n"); return;
    }
    if (!readInt("Reorder level: ", &m.reorderLevel) || m.reorderLevel < 0) {
        m.reorderLevel = 10;
    }
    medicines[medCount++] = m;
    printf("Medicine added.\n");
}

void listMedicines(void) {
    printf("\n%-6s %-24s %-14s %-8s %-8s %-8s\n",
           "ID", "Name", "Category", "Price", "Stock", "Reorder");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < medCount; i++) {
        Medicine *m = &medicines[i];
        printf("%-6d %-24s %-14s %-8.0f %-8d %-8d%s\n",
               m->id, m->name, m->category, m->price, m->stock, m->reorderLevel,
               m->stock <= m->reorderLevel ? " *LOW*" : "");
    }
}

void updateMedicineStock(void) {
    int id, qty;
    if (!readInt("Medicine ID: ", &id)) return;
    int mi = findMedIndex(id);
    if (mi < 0) { printf("Not found.\n"); return; }
    printf("1.Add stock  2.Set stock  3.Update price\n");
    int c;
    if (!readInt("Choice: ", &c)) return;
    if (c == 1) {
        if (!readInt("Quantity to add: ", &qty) || qty <= 0) {
            printf("Invalid.\n"); return;
        }
        medicines[mi].stock += qty;
    } else if (c == 2) {
        if (!readInt("New stock: ", &qty) || qty < 0) {
            printf("Invalid.\n"); return;
        }
        medicines[mi].stock = qty;
    } else if (c == 3) {
        double price;
        if (!readDouble("New price: ", &price) || price < 0) {
            printf("Invalid.\n"); return;
        }
        medicines[mi].price = price;
    } else {
        printf("Invalid.\n");
        return;
    }
    printf("Updated. Stock=%d Price=%.0f\n", medicines[mi].stock, medicines[mi].price);
}

void prescribeMedicine(void) {
    if (prescCount >= MAX_PRESCRIPTIONS) {
        printf("Prescription log full.\n");
        return;
    }
    int pid, mid, qty;
    if (!readInt("Patient ID: ", &pid)) return;
    int pi = findPatientIndex(pid);
    if (pi < 0) { printf("Patient not found.\n"); return; }
    if (strcmp(patients[pi].status, "Discharged") == 0) {
        printf("Patient discharged.\n");
        return;
    }
    listMedicines();
    if (!readInt("Medicine ID: ", &mid)) return;
    int mi = findMedIndex(mid);
    if (mi < 0) { printf("Medicine not found.\n"); return; }
    if (!readInt("Quantity: ", &qty) || qty <= 0) {
        printf("Invalid quantity.\n");
        return;
    }
    if (medicines[mi].stock < qty) {
        printf("Insufficient stock (have %d).\n", medicines[mi].stock);
        return;
    }
    medicines[mi].stock -= qty;
    Prescription pr;
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
    printf("Prescribed %s x%d = Tk. %.0f\n", medicines[mi].name, qty, pr.amount);
}

void lowStockAlert(void) {
    printf("\n=== LOW STOCK ALERT ===\n");
    int found = 0;
    for (int i = 0; i < medCount; i++) {
        if (medicines[i].stock <= medicines[i].reorderLevel) {
            printf("ID %d | %s | stock %d (reorder %d)\n",
                   medicines[i].id, medicines[i].name,
                   medicines[i].stock, medicines[i].reorderLevel);
            found = 1;
        }
    }
    if (!found) printf("All medicines above reorder level.\n");
}

void pharmacyMenu(void) {
    int c;
    while (1) {
        printf("\n=== PHARMACY ===\n");
        printf("1. Add Medicine\n");
        printf("2. List Medicines\n");
        printf("3. Update Stock / Price\n");
        printf("4. Prescribe to Patient\n");
        printf("5. Low Stock Alert\n");
        printf("6. Back\n");
        if (!readInt("Choice: ", &c)) continue;
        switch (c) {
            case 1: addMedicine(); break;
            case 2: listMedicines(); break;
            case 3: updateMedicineStock(); break;
            case 4: prescribeMedicine(); break;
            case 5: lowStockAlert(); break;
            case 6: return;
            default: printf("Invalid.\n");
        }
    }
}
