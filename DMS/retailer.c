#include<stdio.h>
#include "retailer.h"
#include "data.h"
#include "display.h"

void show_retailer_stock(int retailer_index) {
    int i;

    print_subtitle("My Stock");
    printf("Logged in as: %s\n", retailer_name[retailer_index]);
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], retailer_stock[retailer_index][i]);
    }
    print_table_footer();
}

void order_from_dealer(int retailer_index) {
    int product_id_input;
    int quantity;
    int i;
    int product_index;
    int dealer_index;
    int found;

    dealer_index = 0;
    for (i = 0; i < dealer_total; i++) {
        if (dealer_id[i] == retailer_dealer[retailer_index]) {
            dealer_index = i;
            break;
        }
    }

    print_subtitle("Place Order to Dealer");
    printf("Your Dealer: %s\n", dealer_name[dealer_index]);
    show_dealer_products(dealer_index);

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

    if (dealer_stock[dealer_index][product_index] < quantity) {
        print_error("Dealer does not have enough stock.");
        return;
    }

    dealer_stock[dealer_index][product_index] = dealer_stock[dealer_index][product_index] - quantity;
    retailer_stock[retailer_index][product_index] = retailer_stock[retailer_index][product_index] + quantity;

    print_order_summary(product_name[product_index], quantity, dealer_name[dealer_index], retailer_name[retailer_index]);
}

void retailer_menu() {
    int retailer_id_input;
    int retailer_index;
    int dealer_index;
    int i;
    int found;
    int choice;

    print_subtitle("Retailer Login");
    printf("\n");
    printf("+------+----------------------+-------------+\n");
    printf("| ID   | Retailer Name        | Linked To   |\n");
    printf("+------+----------------------+-------------+\n");
    for (i = 0; i < retailer_total; i++) {
        print_table_retailer_row(retailer_id[i], retailer_name[i], retailer_dealer[i]);
    }
    printf("+------+----------------------+-------------+\n");

    printf("\nEnter Retailer ID: ");
    scanf("%d", &retailer_id_input);

    found = 0;
    retailer_index = 0;
    for (i = 0; i < retailer_total; i++) {
        if (retailer_id[i] == retailer_id_input) {
            found = 1;
            retailer_index = i;
            break;
        }
    }

    if (found == 0) {
        print_error("Retailer not found. Check the table above.");
        return;
    }

    dealer_index = 0;
    for (i = 0; i < dealer_total; i++) {
        if (dealer_id[i] == retailer_dealer[retailer_index]) {
            dealer_index = i;
            break;
        }
    }

    print_success("Login successful.");

    do {
        print_menu_header("RETAILER PANEL");
        printf("Welcome, %s\n", retailer_name[retailer_index]);
        printf("Your Dealer: %s\n\n", dealer_name[dealer_index]);
        print_menu_item(1, "View My Stock");
        print_menu_item(2, "View Dealer Products");
        print_menu_item(3, "Order From Dealer");
        print_menu_item(0, "Logout");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            show_retailer_stock(retailer_index);
        } else if (choice == 2) {
            show_dealer_products(dealer_index);
        } else if (choice == 3) {
            order_from_dealer(retailer_index);
        } else if (choice != 0) {
            print_error("Invalid choice. Please try again.");
        }
    } while (choice != 0);
}
