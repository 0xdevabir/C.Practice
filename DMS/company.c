#include<stdio.h>
#include "company.h"
#include "data.h"
#include "display.h"

void list_dealers() {
    int i;

    print_subtitle("All Dealers");
    print_table_dealer_header();
    for (i = 0; i < dealer_total; i++) {
        print_table_dealer_row(dealer_id[i], dealer_name[i]);
    }
    printf("+------+----------------------+\n");
}

void list_products() {
    int i;

    print_subtitle("All Products");
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], company_stock[i]);
    }
    print_table_footer();
}

void show_company_stock() {
    int i;

    print_subtitle("Company Warehouse Stock");
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], company_stock[i]);
    }
    print_table_footer();
}

void company_menu() {
    int choice;

    do {
        print_menu_header("COMPANY PANEL");
        print_menu_item(1, "View All Dealers");
        print_menu_item(2, "View All Products");
        print_menu_item(3, "View Company Stock");
        print_menu_item(0, "Back to Main Menu");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            list_dealers();
        } else if (choice == 2) {
            list_products();
        } else if (choice == 3) {
            show_company_stock();
        } else if (choice != 0) {
            print_error("Invalid choice. Please try again.");
        }
    } while (choice != 0);
}
