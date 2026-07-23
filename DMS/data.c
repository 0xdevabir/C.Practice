#include <stdio.h>
#include <string.h>
#include "data.h"
#include "display.h"

int product_id[MAX_PRODUCTS];
char product_name[MAX_PRODUCTS][50];
int company_stock[MAX_PRODUCTS];
int product_total;

int dealer_id[MAX_DEALERS];
char dealer_name[MAX_DEALERS][50];
int dealer_stock[MAX_DEALERS][MAX_PRODUCTS];
int dealer_total;

int retailer_id[MAX_RETAILERS];
char retailer_name[MAX_RETAILERS][50];
int retailer_dealer[MAX_RETAILERS];
int retailer_stock[MAX_RETAILERS][MAX_PRODUCTS];
int retailer_total;

void init_data() {
    product_total = 3;
    dealer_total = 2;
    retailer_total = 2;

    product_id[0] = 1;
    strcpy(product_name[0], "Rice");
    company_stock[0] = 100;

    product_id[1] = 2;
    strcpy(product_name[1], "Oil");
    company_stock[1] = 80;

    product_id[2] = 3;
    strcpy(product_name[2], "Sugar");
    company_stock[2] = 60;

    dealer_id[0] = 1;
    strcpy(dealer_name[0], "Dhaka Dealer");

    dealer_id[1] = 2;
    strcpy(dealer_name[1], "Chittagong Dealer");

    dealer_stock[0][0] = 20;
    dealer_stock[0][1] = 15;
    dealer_stock[0][2] = 10;

    dealer_stock[1][0] = 25;
    dealer_stock[1][1] = 12;
    dealer_stock[1][2] = 18;

    retailer_id[0] = 1;
    strcpy(retailer_name[0], "Mirpur Shop");
    retailer_dealer[0] = 1;

    retailer_id[1] = 2;
    strcpy(retailer_name[1], "Gulshan Shop");
    retailer_dealer[1] = 2;

    retailer_stock[0][0] = 5;
    retailer_stock[0][1] = 3;
    retailer_stock[0][2] = 2;

    retailer_stock[1][0] = 4;
    retailer_stock[1][1] = 6;
    retailer_stock[1][2] = 1;
}

void show_company_products() {
    int i;

    print_subtitle("Company Products (Available to Order)");
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], company_stock[i]);
    }
    print_table_footer();
}

void show_dealer_products(int dealer_index) {
    int i;

    print_subtitle("Dealer Products (Available to Order)");
    printf("Dealer: %s\n", dealer_name[dealer_index]);
    print_table_product_header();
    for (i = 0; i < product_total; i++) {
        print_table_product_row(product_id[i], product_name[i], dealer_stock[dealer_index][i]);
    }
    print_table_footer();
}
