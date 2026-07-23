#include<stdio.h>
#include "data.h"
#include "display.h"
#include "company.h"
#include "dealer.h"
#include "retailer.h"

int main() {
    int choice;

    init_data();

    do {
        print_menu_header("DISTRIBUTION MANAGEMENT SYSTEM");
        print_menu_item(1, "Company Login");
        print_menu_item(2, "Dealer Login");
        print_menu_item(3, "Retailer Login");
        print_menu_item(0, "Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            company_menu();
        } else if (choice == 2) {
            dealer_menu();
        } else if (choice == 3) {
            retailer_menu();
        } else if (choice != 0) {
            print_error("Invalid choice. Please try again.");
        }
    } while (choice != 0);

    printf("\nThank you for using DMS. Goodbye!\n\n");
    return 0;
}
