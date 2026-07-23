#include<stdio.h>
#include "display.h"

void print_line() {
    printf("==============================================\n");
}

void print_title(char title[]) {
    printf("\n");
    print_line();
    printf("  %s\n", title);
    print_line();
}

void print_subtitle(char subtitle[]) {
    printf("\n--- %s ---\n", subtitle);
}

void print_menu_header(char title[]) {
    printf("\n");
    print_line();
    printf("  %s\n", title);
    print_line();
    printf("\n");
}

void print_menu_item(int number, char label[]) {
    printf("  [%d] %s\n", number, label);
}

void print_table_product_header() {
    printf("\n");
    printf("+------+----------------------+------------+\n");
    printf("| ID   | Product Name         | Stock      |\n");
    printf("+------+----------------------+------------+\n");
}

void print_table_product_row(int id, char name[], int stock) {
    printf("| %-4d | %-20s | %-10d |\n", id, name, stock);
}

void print_table_dealer_header() {
    printf("\n");
    printf("+------+----------------------+\n");
    printf("| ID   | Dealer Name          |\n");
    printf("+------+----------------------+\n");
}

void print_table_dealer_row(int id, char name[]) {
    printf("| %-4d | %-20s |\n", id, name);
}

void print_table_retailer_row(int id, char name[], int dealer_id) {
    printf("| %-4d | %-20s | Dealer: %-2d |\n", id, name, dealer_id);
}

void print_table_footer() {
    printf("+------+----------------------+------------+\n");
}

void print_success(char message[]) {
    printf("\n");
    print_line();
    printf("  SUCCESS: %s\n", message);
    print_line();
}

void print_error(char message[]) {
    printf("\n  ERROR: %s\n", message);
}

void print_order_summary(char product[], int quantity, char from[], char to[]) {
    printf("\n");
    print_line();
    printf("  ORDER PLACED SUCCESSFULLY\n");
    print_line();
    printf("  Product  : %s\n", product);
    printf("  Quantity : %d units\n", quantity);
    printf("  From     : %s\n", from);
    printf("  To       : %s\n", to);
    print_line();
}
