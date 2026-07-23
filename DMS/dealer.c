#include<stdio.h>
#include "dealer.h"
#include "data.h"
#include "display.h"

void show_dealer_stock(int dealer_index) {
    int i;

    print_subtitle("My Stock");
    printf("Logged in as: %s\n", dealer_name[dealer_index]);
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], dealer_stock[dealer_index][i]);
    }
    print_table_footer();
}

void order_from_company(int dealer_index) {
    int product_id_input;
    int quantity;
    int i;
    int product_index;
    int found;

    print_subtitle("Place Order to Company");
    show_company_products();

    printf("\nEnter Product ID: ");
    scanf("%d", &product_id_input);

    found = 0;
    product_index = 0;
    for (i = 0; i < product_total; i++) {
        if (product_id[i] == product_id_input) {
            found = 1;
            product_index = i;
            break;
        }
    }

    if (found == 0) {
        print_error("Product not found. Check the table above.");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        print_error("Quantity must be greater than 0.");
        return;
    }

    if (company_stock[product_index] < quantity) {
        print_error("Not enough stock in company warehouse.");
        return;
    }

    company_stock[product_index] = company_stock[product_index] - quantity;
    dealer_stock[dealer_index][product_index] = dealer_stock[dealer_index][product_index] + quantity;

    print_order_summary(product_name[product_index], quantity, "Company", dealer_name[dealer_index]);
}

void dealer_menu() {
    int dealer_id_input;
    int dealer_index;
    int i;
    int found;
    int choice;

    print_subtitle("Dealer Login");
    print_table_dealer_header();
    for (i = 0; i < dealer_total; i++) {
        print_table_dealer_row(dealer_id[i], dealer_name[i]);
    }
    printf("+------+----------------------+\n");

    printf("\nEnter Dealer ID: ");
    scanf("%d", &dealer_id_input);

    found = 0;
    dealer_index = 0;
    for (i = 0; i < dealer_total; i++) {
        if (dealer_id[i] == dealer_id_input) {
            found = 1;
            dealer_index = i;
            break;
        }
    }

    if (found == 0) {
        print_error("Dealer not found. Check the table above.");
        return;
    }

    print_success("Login successful.");

    do {
        print_menu_header("DEALER PANEL");
        printf("Welcome, %s\n\n", dealer_name[dealer_index]);
        print_menu_item(1, "View My Stock");
        print_menu_item(2, "View Company Products");
        print_menu_item(3, "Order From Company");
        print_menu_item(0, "Logout");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            show_dealer_stock(dealer_index);
        } else if (choice == 2) {
            show_company_products();
        } else if (choice == 3) {
            order_from_company(dealer_index);
        } else if (choice != 0) {
            print_error("Invalid choice. Please try again.");
        }
    } while (choice != 0);
}
