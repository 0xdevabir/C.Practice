#define MAX_PRODUCTS 10
#define MAX_DEALERS 5
#define MAX_RETAILERS 5

extern int product_id[MAX_PRODUCTS];
extern char product_name[MAX_PRODUCTS][50];
extern int company_stock[MAX_PRODUCTS];
extern int product_total;

extern int dealer_id[MAX_DEALERS];
extern char dealer_name[MAX_DEALERS][50];
extern int dealer_stock[MAX_DEALERS][MAX_PRODUCTS];
extern int dealer_total;

extern int retailer_id[MAX_RETAILERS];
extern char retailer_name[MAX_RETAILERS][50];
extern int retailer_dealer[MAX_RETAILERS];
extern int retailer_stock[MAX_RETAILERS][MAX_PRODUCTS];
extern int retailer_total;

void init_data();
void show_company_products();
void show_dealer_products(int dealer_index);


