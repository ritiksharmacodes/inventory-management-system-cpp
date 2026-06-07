class admin
{
public:
    char id[20];
    char username[50];
    char password[50];
};

class emp
{
public:
    char id[20];
    char username[50];
    char password[50];
};

class stock
{
public:
    char id[20];
    char name[50];
    char cost_price[50];
    char quantity[50];
    char selling_price[50];
    char gst[50];
};

class bill
{
public:
    char employee_name[50];
    char name_of_the_recipient[50];
    char invoice_num[40];
    char invoice_date[40];
    char total_amount[50];
};

class total_gst
{
public:
    char invoice_num[40];
    char total_GST[50];
};
