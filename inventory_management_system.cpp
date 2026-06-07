#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include "main_classes.h"
using namespace std;

class ims
{
private:
    int admin_found, i_of_rev_gen, num_of_dates_in_rev_gen;
    int emp_found, admin_in_emp_found;
    admin  ad_obj;
    emp  emp_obj;
    fstream  empF_ip_obj, empF_op_obj, admin_in_emp_io_object, temp_r_object_inp_outp;
    stock  stock_obj_ip, stock_obj_op, main_stock_obj_emp, temp_bill_stock_obj, temp_bill_st_refu_obj, display_temp_bill_stock_obj;
    stock display_temp_bill_stock_obj_RP;
    bill bill_obj_ip, bill_obj_op, temp_bill_r_obj, temp_bill_ReGP_obj;
    fstream  ip_obj, op_obj, io_obj_recycle, bill_gen_IP_obj, bill_gen_OP_obj, refund_bill_gen_OP_obj;
    char address_of_bill_stocks_Refund_page[80];
    char temp_address_of_bill_stocks_Refund_page[80];
    char invoice_num_for_later_use[50];
    total_gst total_gst_object;
    float total_val_earned_rev_gen_page;
    float in_valueF_rev_gen_page;
    string total_amt_for_rev_gen_page;

    int no_data_available()
    {
        fstream temp_ip_obj;
        temp_ip_obj.open("stocks.txt", ios::in|ios::app);
        temp_ip_obj.seekg(0, ios::end);
        if(temp_ip_obj.tellg()==0)
        {
            temp_ip_obj.close();
            return 1;
        }
        temp_ip_obj.close();
        return 0;
    }
    int autoid()
    {
        fstream temp_ip_obj_for_aID;

        // checking for empty file
        temp_ip_obj_for_aID.open("stocks.txt", ios::in | ios::app);
        temp_ip_obj_for_aID.seekg(0, ios::end);
        if(temp_ip_obj_for_aID.tellg()==0)
        {
            temp_ip_obj_for_aID.close();
            return 101;
        }
        temp_ip_obj_for_aID.close();

        // if not empty then...
        int id;
        temp_ip_obj_for_aID.open("stocks.txt", ios::in);
        while(temp_ip_obj_for_aID.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)));

        id = atoi(stock_obj_ip.id);
        temp_ip_obj_for_aID.close();
        return id+1;
    }
    int autoidEMP()
    {
        fstream temp_ip_obj_for_aID_EMPLOYeE;

        // checking for empty file
        temp_ip_obj_for_aID_EMPLOYeE.open("employee_accounts.txt", ios::in | ios::app);
        temp_ip_obj_for_aID_EMPLOYeE.seekg(0, ios::end);
        if(temp_ip_obj_for_aID_EMPLOYeE.tellg()==0)
        {
            temp_ip_obj_for_aID_EMPLOYeE.close();
            return 101;
        }
        temp_ip_obj_for_aID_EMPLOYeE.close();

        // if not empty then...
        int id;
        temp_ip_obj_for_aID_EMPLOYeE.open("employee_accounts.txt", ios::in);
        while(temp_ip_obj_for_aID_EMPLOYeE.read((char*)&emp_obj, sizeof(emp_obj)));

        id = atoi(emp_obj.id);
        temp_ip_obj_for_aID_EMPLOYeE.close();
        return id+1;
    }
    int auto_invoice_num()
    {
        fstream temp_ip_obj_for_aInvNum;

        // checking for empty file
        temp_ip_obj_for_aInvNum.open("bill_files/generated_invoices.txt", ios::in | ios::app);
        temp_ip_obj_for_aInvNum.seekg(0, ios::end);
        if(temp_ip_obj_for_aInvNum.tellg()==0)
        {
            temp_ip_obj_for_aInvNum.close();
            return 101;
        }
        temp_ip_obj_for_aInvNum.close();

        // if not empty then...
        int invoice_num;
        temp_ip_obj_for_aInvNum.open("bill_files/generated_invoices.txt", ios::in);
        while(temp_ip_obj_for_aInvNum.read((char*)&bill_obj_ip, sizeof(bill_obj_ip)));

        invoice_num = atoi(bill_obj_ip.invoice_num);
        temp_ip_obj_for_aInvNum.close();
        return invoice_num+1;
    }
    string charArrtoString(char charArr[])
    {
        string retStr="";

        for(int i=0; charArr[i]!='\0'; i++)
        {
            retStr += charArr[i];
        }

        return retStr;
    }
    string float_to_string_part_1(float val)
    {
        string ret_str="";
        char c;

        float f = val*100.00; //example -- 1546.52 = 154652.00
        long int i = static_cast<long int>(f);

        while(i>0)
        {
            c = 48+(i%10);
            ret_str = c + ret_str;
            i/=10;
        }
        return ret_str;
    }
    void getdata()
    {
        itoa(autoid(), stock_obj_op.id, 10);
        cout<<"Enter name: "; cin.getline(stock_obj_op.name, sizeof(stock_obj_op.name));
        cout<<"Enter quantity: "; cin.getline(stock_obj_op.quantity, sizeof(stock_obj_op.quantity));
        cout<<"Enter cost price: "; cin.getline(stock_obj_op.cost_price, sizeof(stock_obj_op.cost_price));
        cout<<"Enter selling price: "; cin.getline(stock_obj_op.selling_price, sizeof(stock_obj_op.selling_price));
        cout<<"Enter GST rate applicable: "; cin.getline(stock_obj_op.gst, sizeof(stock_obj_op.gst));
    }
    void storedata()
    {
        op_obj.open("stocks.txt", ios::app);
        op_obj.write((char*)&stock_obj_op, sizeof(stock_obj_op));
        op_obj.close();
    }
    void showData()
    {
        // Printing the column names
        cout<<"ID";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Name of the product";
        cout<<setw(33)<<setfill(' ')<<"";
        cout<<"Quantity";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Cost price";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"Selling price";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"GST rate applicable\n";

        // Printing the main data
        ip_obj.open("stocks.txt", ios::in);

        while(ip_obj.read((char *)&stock_obj_ip, sizeof(stock_obj_ip)))
        {
            cout<<left<<setw(10)<<stock_obj_ip.id;
            cout<<left<<setw(50)<<stock_obj_ip.name;
            cout<<setw(9)<<right<<stock_obj_ip.quantity<<"n";
            cout<<setw(18)<<right<<stock_obj_ip.cost_price;
            cout<<setw(20)<<right<<stock_obj_ip.selling_price;
            cout<<setw(25)<<right<<stock_obj_ip.gst<<"%";
            cout<<endl;
        }
        ip_obj.close();
        cout<<endl<<endl;
    }
    void show_data_recycle_bin_ADHP()
    {
        // Printing the column names
        cout<<"ID";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Name of the stock";
        cout<<setw(35)<<setfill(' ')<<"";
        cout<<"Quantity";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Cost price";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"Selling price";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"GST rate applicable\n";

        // Printing the main data
        ip_obj.open("stock_recycle_bin.txt", ios::in);

        while(ip_obj.read((char *)&stock_obj_ip, sizeof(stock_obj_ip)))
        {
            cout<<left<<setw(10)<<stock_obj_ip.id;
            cout<<left<<setw(50)<<stock_obj_ip.name;
            cout<<setw(9)<<right<<stock_obj_ip.quantity<<"n";
            cout<<setw(18)<<right<<stock_obj_ip.cost_price;
            cout<<setw(20)<<right<<stock_obj_ip.selling_price;
            cout<<setw(25)<<right<<stock_obj_ip.gst<<"%";
            cout<<endl;
        }
        ip_obj.close();
    }
    void showData_employee_homepage()
    {
        // Printing the column names
        cout<<"ID";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Name of the product";
        cout<<setw(21)<<setfill(' ')<<"";
        cout<<"Selling price\n";

        // Printing the main data
        ip_obj.open("stocks.txt", ios::in);

        while(ip_obj.read((char *)&stock_obj_ip, sizeof(stock_obj_ip)))
        {
            cout<<setw(10)<<left<<stock_obj_ip.id;
            cout<<setw(42)<<left<<stock_obj_ip.name;
            cout<<setw(11)<<right<<stock_obj_ip.selling_price;
            cout<<endl;
        }
        ip_obj.close();
        cout<<endl<<endl;
    }
    void createEmployeeAcc()
    {
        int retVal = autoidEMP();

        if(retVal==101)cout<<"\nFIRST EMPLOYEE ACCOUNT\n";
        itoa(retVal, emp_obj.id, 10);
        cout<<"\nEnter username: "; cin.getline(emp_obj.username, sizeof(emp_obj.username));
        cout<<"Enter password: "; cin.getline(emp_obj.password, sizeof(emp_obj.password));

        empF_op_obj.open("employee_accounts.txt", ios::app);
        empF_op_obj.write((char*)&emp_obj, sizeof(emp_obj));
        empF_op_obj.close();
    }
    void readEmployeeAccs()
    {
        // below code is to check if emp_accs file exists
        char d_DEC_for_user_CHOiCE;
        char temp_id[30];
        FILE *fptr = fopen("employee_accounts.txt","r");
        if(fptr == NULL)
        {
            fclose(fptr);
            return;
        }
        fclose(fptr);

        cout<<"\nEMPLOYEE ACCOUNTS ALREADY PRESENT IN THE FILE...\n\n";
        // Printing the column names
        cout<<"ID";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"USERNAME";
        cout<<setw(18)<<setfill(' ')<<"";
        cout<<"PASSWORD";
        cout<<setw(8)<<setfill(' ')<<""<<endl;

        empF_ip_obj.open("employee_accounts.txt", ios::in);
        while(empF_ip_obj.read((char*)&emp_obj, sizeof(emp_obj)))
        {
            cout<<left<<setw(10)<<emp_obj.id;
            cout<<left<<setw(25)<<emp_obj.username;
            cout<<setw(9)<<right<<emp_obj.password;
            cout<<endl;
        }
        empF_ip_obj.close();
    }
    int invalid_quantiy(char* temp_id, char* temp_quantity)
    {
        stock temp_stock_object;
        int found_AND_ok=0;

        ip_obj.open("stocks.txt", ios::in);
        while(ip_obj.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                if(atoi(temp_stock_object.quantity) >= atoi(temp_quantity)) found_AND_ok=1;
                break;
            }
        }
        ip_obj.close();

        if(found_AND_ok == 1) return 0;
        else return 1;
    }
    int temp_stocks_quantity_more_than_available(char* temp_id)
    {
        fstream temp_ip_obj;
        stock temp_stock_obj, temp_stock_obj_2;

        ip_obj.open("stocks.txt", ios::in);
        while(ip_obj.read((char*)&temp_stock_obj_2, sizeof(temp_stock_obj_2)))
        {
            if(strcmp(temp_stock_obj_2.id, temp_id)==0)
            {
                break;
            }
        }
        ip_obj.close();

        temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        while(temp_ip_obj.read((char*)&temp_stock_obj, sizeof(temp_stock_obj)))
        {
            if(strcmp(temp_stock_obj.id, temp_id)==0)
            {
                if( atoi(temp_stock_obj.quantity)> atoi(temp_stock_obj_2.quantity) )
                {
                    temp_ip_obj.close();
                    return 1;
                }
            }
        }
        temp_ip_obj.close();

        return 0;
    }
    void SOLUTION_temp_stocks_quantity_more_than_available(char* temp_id)
    {
        char c;
        stock temp_stock_obj, temp_stock_obj_2;
        fstream temp_io_object;

        cout<<"\nWhat do you want to do now? \n";
        cout<<"\n1. remove the product entirely from the bill";
        cout<<"\n2. set the quantity of the product to maximum quantity available\n"; c = getch();

        if(c=='1')
        {
            ip_obj.open("bill_files/temp_bill_stocks.txt",ios::in);
            op_obj.open("bill_files/temp_temp_bill_stocks.txt", ios::app);
            while(ip_obj.read((char*)&temp_stock_obj, sizeof(temp_stock_obj)))
            {
                if(strcmp(temp_stock_obj.id, temp_id)!=0)
                {
                    op_obj.write((char*)&temp_stock_obj, sizeof(temp_stock_obj));
                }
            }
            op_obj.close();
            ip_obj.close();

            remove("bill_files/temp_bill_stocks.txt");
            rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");
        }
        else if(c=='2')
        {
            // stocks.txt file ka data jaa rha hai neeche waale loop se temp_stock_obj_2 mein
            temp_io_object.open("stocks.txt", ios::in);
            while(temp_io_object.read((char*)&temp_stock_obj_2, sizeof(temp_stock_obj_2)))
            {
                if(strcmp(temp_stock_obj_2.id, temp_id)==0)
                {
                    break;
                }
            }
            temp_io_object.close();

            // main kaam neeche wala code krega
            ip_obj.open("bill_files/temp_bill_stocks.txt",ios::in);
            op_obj.open("bill_files/temp_temp_bill_stocks.txt", ios::app);
            while(ip_obj.read((char*)&temp_stock_obj, sizeof(temp_stock_obj)))
            {
                if(strcmp(temp_stock_obj.id, temp_id)==0)
                {
                    strcpy(temp_stock_obj.quantity, temp_stock_obj_2.quantity);
                    op_obj.write((char*)&temp_stock_obj, sizeof(temp_stock_obj));
                }
                else
                {
                    op_obj.write((char*)&temp_stock_obj, sizeof(temp_stock_obj));
                }
            }

            op_obj.close();
            ip_obj.close();

            remove("bill_files/temp_bill_stocks.txt");
            rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");
        }
        else
        {
            cout<<"\nWRONG INPUT!\n";
            SOLUTION_temp_stocks_quantity_more_than_available(temp_id);
        }
    }
    void write_into_temp_stocks(char* temp_id, char* temp_quantity)
    {
        stock temp_stock_object;
        fstream temp_ip_obj;

        ip_obj.open("stocks.txt", ios::in);
        while(ip_obj.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                break;
            }
        }
        ip_obj.close();

        strcpy(temp_stock_object.quantity, temp_quantity);
        temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::app);
        temp_ip_obj.write((char*)&temp_stock_object, sizeof(temp_stock_object));
        temp_ip_obj.close();
    }
    int occurs_in_temp_stocks(char* temp_id)
    {
        fstream temp_ip_obj;
        stock temp_stock_object;

        temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        while(temp_ip_obj.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                temp_ip_obj.close();
                return 1;
            }
        }
        temp_ip_obj.close();

        return 0;
    }
    void update_stock_in_temp_stocks(char* temp_id, char* temp_quantity)
    {
        fstream temp_ip_obj, temp_ip_obj_2;
        stock temp_stock_object, temp_stock_object_2;

        temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        temp_ip_obj_2.open("bill_files/temp_temp_bill_stocks.txt", ios::app);
        while(temp_ip_obj.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                int val = atoi(temp_stock_object.quantity) + atoi(temp_quantity);
                itoa(val, temp_stock_object.quantity, 10);

                temp_ip_obj_2.write((char*)&temp_stock_object, sizeof(temp_stock_object));
            }
            else
            {
                temp_ip_obj_2.write((char*)&temp_stock_object, sizeof(temp_stock_object));
            }
        }
        temp_ip_obj_2.close();
        temp_ip_obj.close();

        remove("bill_files/temp_bill_stocks.txt");
        rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");
    }
    void show_temp_bill_stocks()
    {
        stock stock_obj_ip_2;
        fstream tempp;
        tempp.open("bill_files/temp_bill_stocks.txt", ios::in);

        cout<<"\nProducts in the bill so far -->\n";
        while(tempp.read((char*)&stock_obj_ip_2, sizeof(stock_obj_ip_2)))
        {
            cout<<"ID: "<<stock_obj_ip_2.id<<endl;
            cout<<"Name: "<<stock_obj_ip_2.name<<endl;
            cout<<"Quantity: "<<stock_obj_ip_2.quantity<<endl<<endl<<endl;
        }
        tempp.close();
    }
    void show_temp_bill_stocks_tabular_for_option_3()
    {
        stock stock_obj_ip_2;
        fstream tempp;

        // Printing the column names
        cout<<"\nName";
        cout<<setw(27)<<setfill(' ')<<"";
        cout<<"Quantity\n";

        tempp.open("bill_files/temp_bill_stocks.txt", ios::in);
        while(tempp.read((char*)&stock_obj_ip_2, sizeof(stock_obj_ip_2)))
        {
            cout<<left<<setw(25)<<stock_obj_ip_2.name;
            cout<<setw(14)<<right<<stock_obj_ip_2.quantity;
            cout<<endl;
        }
        tempp.close();
    }
    void modify_the_quantity_in_the_bill(char* temp_id, char* temp_quantity)
    {
        fstream temp_ip_obj, temp_ip_obj_2;
        stock temp_stock_object, temp_stock_object_2;

        temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        temp_ip_obj_2.open("bill_files/temp_temp_bill_stocks.txt", ios::app);
        while(temp_ip_obj.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                strcpy(temp_stock_object.quantity, temp_quantity);
                temp_ip_obj_2.write((char*)&temp_stock_object, sizeof(temp_stock_object));
            }
            else
            {
                temp_ip_obj_2.write((char*)&temp_stock_object, sizeof(temp_stock_object));
            }
        }
        temp_ip_obj_2.close();
        temp_ip_obj.close();

        remove("bill_files/temp_bill_stocks.txt");
        rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");
    }
    void bill_generator()
    {
        int spaces = 0;
        // following code creates the name of the invoice
        char name_of_the_bill[50];
        strcpy(name_of_the_bill, "bill_files/");
        strcat(name_of_the_bill,"Invoice ");
        strcat(name_of_the_bill, bill_obj_op.invoice_num);
        strcat(name_of_the_bill,".txt");

        // (CODE START) Opening the bill for editing
        bill_gen_OP_obj.open(name_of_the_bill, ios::app);

        // creating the header line in the file
        bill_gen_OP_obj<<setw(32)<<setfill(' ')<<""<<"INVENTORY MANAGEMENT SYSTEM"<<endl;
        bill_gen_OP_obj<<setw(34)<<setfill(' ')<<""<<"Ajmer, Rajasthan, 305011"<<endl<<endl;
        bill_gen_OP_obj<<"Bill to -- "<<bill_obj_op.name_of_the_recipient;

        spaces = 70-(11+strlen(bill_obj_op.name_of_the_recipient)); // counting the number of spaces (for invoice number)
        bill_gen_OP_obj<<setw(spaces)<<setfill(' ')<<""; // printing the spaces (for invoice number)

        bill_gen_OP_obj<<"Invoice number -- "<<bill_obj_op.invoice_num<<endl; // printing the invoice number
        bill_gen_OP_obj<<setw(70)<<setfill(' ')<<""; // printing the spaces (for invoice date)
        bill_gen_OP_obj<<"Invoice date -- "<<bill_obj_op.invoice_date<<endl; // printing the invoice date
        // header line created

        // col-name row (code start)
        bill_gen_OP_obj<<setw(97)<<setfill('-')<<""<<endl; //printing the column-name row ceiling
        bill_gen_OP_obj<<"|"<<setw(13)<<setfill(' ')<<""<<"Items"<<setw(13)<<setfill(' ')<<""<<"|";
        bill_gen_OP_obj<<setw(1)<<setfill(' ')<<""<<"Quantity"<<setw(1)<<setfill(' ')<<""<<"|";
        bill_gen_OP_obj<<setw(1)<<setfill(' ')<<""<<"Selling price(per unit)"<<setw(1)<<setfill(' ')<<""<<"|";
        bill_gen_OP_obj<<setw(4)<<setfill(' ')<<""<<"GST"<<setw(4)<<setfill(' ')<<""<<"|";
        bill_gen_OP_obj<<setw(4)<<setfill(' ')<<""<<"Amount"<<setw(4)<<setfill(' ')<<""<<"|"<<endl;
        bill_gen_OP_obj<<setw(97)<<setfill('-')<<""<<endl; //printing the column-name row floor
        // col-name row (code end)

        bill_gen_OP_obj.fill(' '); // Restoring the default value of the fill character

        // following code prints the main item details
        bill_gen_IP_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        float calculated_GST=0;
        float subTGST=0, amount=0, subTamt=0;
        int subTsp=0, subTq=0;
        while(bill_gen_IP_obj.read((char*)&temp_bill_stock_obj, sizeof(temp_bill_stock_obj)))
        {
            bill_gen_OP_obj<<"|"<<setw(31)<<left<<temp_bill_stock_obj.name<<"|";
            bill_gen_OP_obj<<setw(10)<<right<<temp_bill_stock_obj.quantity<<"|";
            bill_gen_OP_obj<<setw(25)<<right<<temp_bill_stock_obj.selling_price<<"|";
            bill_gen_OP_obj<<setw(10)<<right<<temp_bill_stock_obj.gst<<"%"<<"|";

            calculated_GST = (static_cast<float>(atoi(temp_bill_stock_obj.quantity))) * (( static_cast<float>(atoi(temp_bill_stock_obj.selling_price)) * static_cast<float>(atoi(temp_bill_stock_obj.gst)) )/100);
            amount = ( static_cast<float>(atoi(temp_bill_stock_obj.selling_price)) * static_cast<float>(atoi(temp_bill_stock_obj.quantity)) )+ calculated_GST;
            subTamt += amount;
            subTGST += calculated_GST;
            subTsp += atoi(temp_bill_stock_obj.selling_price);
            subTq += atoi(temp_bill_stock_obj.quantity);

            bill_gen_OP_obj<<setw(14)<<right<<fixed<<setprecision(2)<<amount<<"|"<<endl;

            // printing the underlines
            bill_gen_OP_obj<<setw(1)<<setfill('+')<<""<<setw(31)<<setfill('-')<<""<<setw(1)<<setfill('+')<<""; // underline below 'name'
            bill_gen_OP_obj<<setw(10)<<setfill('-')<<""<<setw(1)<<setfill('+')<<""; // underline below 'quantity'
            bill_gen_OP_obj<<setw(25)<<setfill('-')<<""<<setw(1)<<setfill('+')<<""; // underline below 'SP'
            bill_gen_OP_obj<<setw(11)<<setfill('-')<<""<<setw(1)<<setfill('+')<<""; // underline below 'GST'
            bill_gen_OP_obj<<setw(14)<<setfill('-')<<""<<setw(1)<<setfill('+')<<""<<endl; // underline below 'amount'

            bill_gen_OP_obj.fill(' '); // Restoring the default value of the fill character
        }
        bill_gen_IP_obj.close();
        // main item details printing DONE

            // Printing the sub-total row (START)
            bill_gen_OP_obj<<setw(97)<<setfill('-')<<""<<endl; //printing the sub-total row ceiling
            bill_gen_OP_obj.fill(' '); // Restoring the default value of the fill character
            bill_gen_OP_obj<<"|"<<setw(31)<<left<<"Sub-total ->"<<"|";
            bill_gen_OP_obj<<setw(10)<<right<<subTq<<"|";
            bill_gen_OP_obj<<setw(25)<<right<<subTsp<<"|";
            bill_gen_OP_obj<<setw(11)<<right<<fixed<<setprecision(2)<<subTGST<<"|";
            bill_gen_OP_obj<<setw(14)<<right<<subTamt<<"|"<<endl;
            bill_gen_OP_obj<<setw(97)<<setfill('-')<<""<<endl; //printing the sub-total row floor
        // Printing the sub-total row (END)

        // printing the 'footer' and the 'total amount' (START)
        bill_gen_OP_obj<<setw(66)<<setfill(' ')<<""; // printing spaces for the total-amt-box ceiling
        bill_gen_OP_obj<<"+"<<setw(29)<<setfill('-')<<""<<"+"<<endl; // printing the total-amt-box ceiling
        bill_gen_OP_obj<<"Note -- Items refundable for 1 week"; // printing the NOTE
        bill_gen_OP_obj<<setw(31)<<setfill(' ')<<""; // printing the spaces
        bill_gen_OP_obj<<"|"<<"Total amount ->"; // printing the total-amt-line
        bill_gen_OP_obj.fill(' '); // Restoring the default value of the fill character
        bill_gen_OP_obj<<setw(14)<<right<<subTamt<<"|"<<endl; // printing the total-amt-value
        bill_gen_OP_obj<<setw(66)<<setfill(' ')<<""; // printing spaces for the total-amt-box floor
        bill_gen_OP_obj<<"+"<<setw(29)<<setfill('-')<<""<<"+"<<endl; // printing the total-amt-box floor
        // printing the 'footer' and the 'total amount' (END)

        bill_gen_OP_obj.close();


        // COVERINTG THE subTamt(FLOAT) & subTgst(FLOAT) TO CHARACTER ARRAY
        // Below logic works only for floats having ONLY 2 decimal digits
        string returned_str = float_to_string_part_1(subTamt);
        string returned_str_gst = float_to_string_part_1(subTGST);

        // float_to_string_part_2 --> BELOW
        char char_arr[100], char_arr_gst[100];
        int len = returned_str.length();
        int len_gst = returned_str_gst.length();

        // for subTamt
        int i=0;
        while(i<=len)
        {
            if(i>(len-2))
            {
                char_arr[i] = returned_str[i-1];
                i++;
            }
            else
            {
                char_arr[i] = returned_str[i];
                i++;
            }

            if(i==(len-2))
            {
                char_arr[i] = '.';
                i++;
            }
        }
        char_arr[i] = '\0';

        // for subTgst
        int j=0;
        while(j<=len_gst)
        {
            if(j>(len_gst-2))
            {
                char_arr_gst[j] = returned_str_gst[j-1];
                j++;
            }
            else
            {
                char_arr_gst[j] = returned_str_gst[j];
                j++;
            }

            if(j==(len_gst-2))
            {
                char_arr_gst[j] = '.';
                j++;
            }
        }
        char_arr_gst[j] = '\0';

        // DRAWBACK --> above logic won't work for testcase 0.29
        strcpy(bill_obj_op.total_amount, char_arr);
        strcpy(total_gst_object.total_GST, char_arr_gst);

        // Writing the data into their respective files
        fstream temp_output_object, temp_output_object_for_gst;
        temp_output_object.open("bill_files/generated_invoices.txt", ios::app);
        temp_output_object.write((char*)&bill_obj_op, sizeof(bill_obj_op));
        temp_output_object.close();

        strcpy(total_gst_object.invoice_num, bill_obj_op.invoice_num);
        temp_output_object_for_gst.open("bill_files/total_gst_of_all_invoices.txt", ios::app);
        temp_output_object_for_gst.write((char*)&total_gst_object, sizeof(total_gst_object));
        temp_output_object_for_gst.close();
    }
    void stocks_updater_after_bill_has_been_generated_DELETING(char* id)
    {
        fstream stocks_updater_io_obj_D, temp_stocks_updater_io_obj_D;
        stock temp_R_S_obj;

        stocks_updater_io_obj_D.open("bill_files/temp_bill_stocks.txt", ios::in);
        temp_stocks_updater_io_obj_D.open("bill_files/temp_temp_bill_stocks.txt", ios::app);

        while(stocks_updater_io_obj_D.read((char*)&temp_R_S_obj, sizeof(temp_R_S_obj)))
        {
            if(strcmp(temp_R_S_obj.id, id)!=0)
            {
                temp_stocks_updater_io_obj_D.write((char*)&temp_R_S_obj, sizeof(temp_R_S_obj));
            }
        }

        temp_stocks_updater_io_obj_D.close();
        stocks_updater_io_obj_D.close();

        remove("bill_files/temp_bill_stocks.txt");
        rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");
    }
    void stocks_updater_after_bill_has_been_generated_R_D_U()
    {
        stock temp_R_S_obj;
        fstream stocks_updater_io_obj_R;
        char temp_id[50];
        char temp_quantity[50];

        stocks_updater_io_obj_R.open("bill_files/temp_bill_stocks.txt", ios::in);
        stocks_updater_io_obj_R.read((char*)&temp_R_S_obj, sizeof(temp_R_S_obj));
        stocks_updater_io_obj_R.close();

        strcpy(temp_id, temp_R_S_obj.id);
        strcpy(temp_quantity, temp_R_S_obj.quantity);

        stocks_updater_after_bill_has_been_generated_UPDATING(temp_id, temp_quantity);
        stocks_updater_after_bill_has_been_generated_DELETING(temp_id);
    }
    void stocks_updater_after_bill_has_been_generated_UPDATING(char* id, char* quantity)
    {
        fstream stocks_updater_io_obj_U, temp_stocks_updater_io_obj_U;
        stock temp_R_S_obj;

        stocks_updater_io_obj_U.open("stocks.txt", ios::in);
        temp_stocks_updater_io_obj_U.open("temp_stocks.txt", ios::app);

        while(stocks_updater_io_obj_U.read((char*)&temp_R_S_obj, sizeof(temp_R_S_obj)))
        {
            if(strcmp(temp_R_S_obj.id, id)==0)
            {
                int val = atoi(temp_R_S_obj.quantity) - atoi(quantity);
                itoa(val, temp_R_S_obj.quantity, 10);
                temp_stocks_updater_io_obj_U.write((char*)&temp_R_S_obj, sizeof(temp_R_S_obj));
            }
            else
            {
                temp_stocks_updater_io_obj_U.write((char*)&temp_R_S_obj, sizeof(temp_R_S_obj));
            }
        }
        temp_stocks_updater_io_obj_U.close();
        stocks_updater_io_obj_U.close();

        remove("stocks.txt");
        rename("temp_stocks.txt", "stocks.txt");
    }
    int count_the_num_of_items_in_bill()
    {
        int counter = 0;
        fstream count_io_obj;
        stock temp_S_obj;

        count_io_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
        while(count_io_obj.read((char*)&temp_S_obj, sizeof(temp_S_obj)))
        {
            counter++;
        }
        count_io_obj.close();

        return counter;
    }
    int is_leap(char* year)
    {
        int y = atoi(year);

        if(y%4==0)
        {
            if(y%100==0)
            {
                if(y%400==0) return 1; // year is leap
                else return 0; // year is NOT leap
            }
            else return 1; // year is leap
        }
        else return 0; // year is NOT leap
    }
    int is_thirty(char* month)
    {
        if(strcmp(month, "Apr")==0) return 1;
        else if(strcmp(month, "Jun")==0) return 1;
        else if(strcmp(month, "Sep")==0) return 1;
        else if(strcmp(month, "Nov")==0) return 1;
        else return 0;
    }
    int is_thirty_one(char* month)
    {
        if(strcmp(month, "Jan")==0) return 1;
        else if(strcmp(month, "Mar")==0) return 1;
        else if(strcmp(month, "May")==0) return 1;
        else if(strcmp(month, "Jul")==0) return 1;
        else if(strcmp(month, "Aug")==0) return 1;
        else if(strcmp(month, "Oct")==0) return 1;
        else if(strcmp(month, "Dec")==0) return 1;
        else return 0;
    }
    string next_month_func(char* current_month)
    {
        if(strcmp(current_month, "Jan")==0) return "Feb";
        else if(strcmp(current_month, "Feb")==0) return "Mar";
        else if(strcmp(current_month, "Mar")==0) return "Apr";
        else if(strcmp(current_month, "Apr")==0) return "May";
        else if(strcmp(current_month, "May")==0) return "Jun";
        else if(strcmp(current_month, "Jun")==0) return "Jul";
        else if(strcmp(current_month, "Jul")==0) return "Aug";
        else if(strcmp(current_month, "Aug")==0) return "Sep";
        else if(strcmp(current_month, "Sep")==0) return "Oct";
        else if(strcmp(current_month, "Oct")==0) return "Nov";
        else if(strcmp(current_month, "Nov")==0) return "Dec";
        else if(strcmp(current_month, "Dec")==0) return "Jan";
        else return "";
    }
    void displaying_the_bill_BGP()
    {
        // Printing the column names
        cout<<"\nItems";
        cout<<setw(33)<<setfill(' ')<<"";
        cout<<"Quantity";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Selling price(per unit)";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"GST rate applicable";
        cout<<setw(18)<<setfill(' ')<<"";
        cout<<"Amount\n";

        // Printing the main data
        ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);

        float calculated_GST=0;
        float subTGST=0, amount=0, subTamt=0;
        int subTsp=0, subTq=0;
        while(ip_obj.read((char*)&display_temp_bill_stock_obj, sizeof(display_temp_bill_stock_obj)))
        {
            cout<<setw(31)<<left<<display_temp_bill_stock_obj.name;
            cout<<setw(15)<<right<<display_temp_bill_stock_obj.quantity;
            cout<<setw(31)<<right<<display_temp_bill_stock_obj.selling_price;
            cout<<setw(25)<<right<<display_temp_bill_stock_obj.gst<<"%";

            calculated_GST = (static_cast<float>(atoi(display_temp_bill_stock_obj.quantity))) * (( static_cast<float>(atoi(display_temp_bill_stock_obj.selling_price)) * static_cast<float>(atoi(display_temp_bill_stock_obj.gst)) )/100);
            amount = ( static_cast<float>(atoi(display_temp_bill_stock_obj.selling_price)) * static_cast<float>(atoi(display_temp_bill_stock_obj.quantity)) )+ calculated_GST;
            subTamt += amount;
            subTGST += calculated_GST;
            subTsp += atoi(display_temp_bill_stock_obj.selling_price);
            subTq += atoi(display_temp_bill_stock_obj.quantity);

            cout<<setw(24)<<right<<fixed<<setprecision(2)<<amount<<endl;

            cout.fill(' '); // Restoring the default value of the fill character
        }
        ip_obj.close();

//        Printing the sub-total row (START)
        cout<<setw(127)<<setfill('-')<<""<<endl; //printing the sub-total row ceiling
        cout.fill(' '); // Restoring the default value of the fill character
        cout<<setw(31)<<left<<"Sub-total ->";
        cout<<setw(15)<<right<<subTq;
        cout<<setw(31)<<right<<subTsp;
        cout<<setw(26)<<right<<fixed<<setprecision(2)<<subTGST;
        cout<<setw(24)<<right<<subTamt<<endl;
//        Printing the sub-total row (END)

    }
    void displaying_the_bill_RP()
    {
        fstream temp_d_t_b_RP_IO_obj;

        // Printing the column names
        cout<<"\nId";
        cout<<setw(5)<<setfill(' ')<<"";
        cout<<"Items";
        cout<<setw(33)<<setfill(' ')<<"";
        cout<<"Quantity\n";

        // Printing the main data
        temp_d_t_b_RP_IO_obj.open(address_of_bill_stocks_Refund_page, ios::in);
        while(temp_d_t_b_RP_IO_obj.read((char*)&display_temp_bill_stock_obj_RP, sizeof(display_temp_bill_stock_obj_RP)))
        {
            cout<<setw(7)<<left<<display_temp_bill_stock_obj_RP.id;
            cout<<setw(31)<<left<<display_temp_bill_stock_obj_RP.name;
            cout<<setw(15)<<right<<display_temp_bill_stock_obj_RP.quantity<<endl;
            cout.fill(' '); // Restoring the default value of the fill character
        }
        temp_d_t_b_RP_IO_obj.close();

    }
    void showData_refund()
    {
        fstream temp_d_t_b_RP_IO_obj;

        // Printing the column names
        cout<<"\nId";
        cout<<setw(5)<<setfill(' ')<<"";
        cout<<"Items";
        cout<<setw(33)<<setfill(' ')<<"";
        cout<<"Quantity(refunded)";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Selling price(per unit)";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"GST rate applicable";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Amount(to be paid back)\n";

        // Printing the main data
        temp_d_t_b_RP_IO_obj.open(temp_address_of_bill_stocks_Refund_page, ios::in);

        float calculated_GST=0;
        float subTGST=0, amount=0, subTamt=0;
        int subTsp=0, subTq=0;
        while(temp_d_t_b_RP_IO_obj.read((char*)&display_temp_bill_stock_obj_RP, sizeof(display_temp_bill_stock_obj_RP)))
        {
            cout<<setw(7)<<left<<display_temp_bill_stock_obj_RP.id;
            cout<<setw(31)<<left<<display_temp_bill_stock_obj_RP.name;
            cout<<setw(15)<<right<<display_temp_bill_stock_obj_RP.quantity;
            cout<<setw(31)<<right<<display_temp_bill_stock_obj_RP.selling_price;
            cout<<setw(25)<<right<<display_temp_bill_stock_obj_RP.gst<<"%";

            calculated_GST = ( static_cast<float>(atoi(display_temp_bill_stock_obj_RP.selling_price)) * static_cast<float>(atoi(display_temp_bill_stock_obj_RP.gst)) )/100;
            amount = ( static_cast<float>(atoi(display_temp_bill_stock_obj_RP.selling_price)) * static_cast<float>(atoi(display_temp_bill_stock_obj_RP.quantity)) )+ calculated_GST;
            subTamt += amount;
            subTGST += calculated_GST;
            subTsp += atoi(display_temp_bill_stock_obj_RP.selling_price);
            subTq += atoi(display_temp_bill_stock_obj_RP.quantity);

            cout<<setw(14)<<right<<fixed<<setprecision(2)<<amount<<endl;

            cout.fill(' '); // Restoring the default value of the fill character
        }
        temp_d_t_b_RP_IO_obj.close();

//        Printing the sub-total row (START)
        cout<<setw(124)<<setfill('-')<<""<<endl; //printing the sub-total row ceiling
        cout.fill(' '); // Restoring the default value of the fill character
        cout<<setw(38)<<left<<"Sub-total ->";
        cout<<setw(15)<<right<<subTq;
        cout<<setw(31)<<right<<subTsp;
        cout<<setw(26)<<right<<fixed<<setprecision(2)<<subTGST;
        cout<<setw(14)<<right<<subTamt<<endl;
//        Printing the sub-total row (END)

    }
    int invalid_quantiy_romt(char* temp_id, char* temp_quantity)
    {
        stock temp_stock_object;
        fstream iq_romt;
        int found_AND_ok=0;

        iq_romt.open(address_of_bill_stocks_Refund_page, ios::in);
        while(iq_romt.read((char*)&temp_stock_object, sizeof(temp_stock_object)))
        {
            if(strcmp(temp_stock_object.id, temp_id)==0)
            {
                if(atoi(temp_stock_object.quantity) >= atoi(temp_quantity)) found_AND_ok=1;
                break;
            }
        }
        iq_romt.close();

        if(found_AND_ok == 1) return 0;
        else return 1;
    }
    void making_new_temp_bill_stocks_romt(char* id, char* quantity)
    {
        fstream temp_io_obj_urmot, temp_io_obj_urmot_2;
        stock temp_stock_obj_urmot;
        char temp_quantity_urmot[50];

        // forming the temp_address_of_bill_stocks_Refund_page
        strcpy(temp_address_of_bill_stocks_Refund_page, "bill_files/");
        strcat(temp_address_of_bill_stocks_Refund_page, "temp_2_Invoice_");
        strcat(temp_address_of_bill_stocks_Refund_page, temp_bill_r_obj.invoice_num);
        strcat(temp_address_of_bill_stocks_Refund_page, "_bill_stocks.txt");

        // then continuing ahead
        temp_io_obj_urmot.open(address_of_bill_stocks_Refund_page, ios::in);
        temp_io_obj_urmot_2.open(temp_address_of_bill_stocks_Refund_page, ios::app);
        while(temp_io_obj_urmot.read((char*)&temp_stock_obj_urmot, sizeof(temp_stock_obj_urmot)))
        {
            if(strcmp(temp_stock_obj_urmot.id, id)==0)
            {
                strcpy(temp_stock_obj_urmot.quantity, quantity);
                temp_io_obj_urmot_2.write((char*)&temp_stock_obj_urmot, sizeof(temp_stock_obj_urmot));
            }
        }
        temp_io_obj_urmot.close();
        temp_io_obj_urmot_2.close();
    }
    void updating_bill_stocks_romt(char* id, char* quantity)
    {
        fstream temp_io_obj_urmot, temp_io_obj_urmot_2;
        stock temp_stock_obj_urmot;
        char temp_quantity_urmot[50];
        char temp_2_address_of_bill_stocks_Refund_page[80];

        // forming the temp_address_of_bill_stocks_Refund_page
        strcpy(temp_2_address_of_bill_stocks_Refund_page, "bill_files/");
        strcat(temp_2_address_of_bill_stocks_Refund_page, "temp_Invoice_");
        strcat(temp_2_address_of_bill_stocks_Refund_page, temp_bill_r_obj.invoice_num);
        strcat(temp_2_address_of_bill_stocks_Refund_page, "_bill_stocks.txt");

        // then continuing ahead
        temp_io_obj_urmot.open(address_of_bill_stocks_Refund_page, ios::in);
        temp_io_obj_urmot_2.open(temp_2_address_of_bill_stocks_Refund_page, ios::app);
        while(temp_io_obj_urmot.read((char*)&temp_stock_obj_urmot, sizeof(temp_stock_obj_urmot)))
        {
            if(strcmp(temp_stock_obj_urmot.id, id)==0)
            {
                int val = atoi(temp_stock_obj_urmot.quantity) - atoi(quantity);
                itoa(val, temp_quantity_urmot, 10);

                strcpy(temp_stock_obj_urmot.quantity, temp_quantity_urmot);

                temp_io_obj_urmot_2.write((char*)&temp_stock_obj_urmot, sizeof(temp_stock_obj_urmot));
            }
            else
            {
                temp_io_obj_urmot_2.write((char*)&temp_stock_obj_urmot, sizeof(temp_stock_obj_urmot));
            }
        }
        temp_io_obj_urmot.close();
        temp_io_obj_urmot_2.close();

        remove(address_of_bill_stocks_Refund_page);
        rename(temp_2_address_of_bill_stocks_Refund_page, address_of_bill_stocks_Refund_page);
    }
    void updating_stocks_txt_refund_option_main_task()
    {
        fstream ustromt_io_obj, ustromt_io_obj_2, ustromt_io_obj_1;
        stock temp_ustromt_st_obj, temp_ustromt_st_obj_2, temp_ustromt_st_obj_1;
        char temp_ustromt_quantity[50];

        ustromt_io_obj.open(temp_address_of_bill_stocks_Refund_page,ios::in);
        while(ustromt_io_obj.read((char*)&temp_ustromt_st_obj, sizeof(temp_ustromt_st_obj)))
        {
            ustromt_io_obj_2.open("stocks.txt",ios::in);
            ustromt_io_obj_1.open("temp_stocks.txt", ios::app);
            while(ustromt_io_obj_2.read((char*)&temp_ustromt_st_obj_2, sizeof(temp_ustromt_st_obj_2)))
            {
                if(strcmp(temp_ustromt_st_obj.id, temp_ustromt_st_obj_2.id)==0)
                {
                    int val = atoi(temp_ustromt_st_obj_2.quantity) + atoi(temp_ustromt_st_obj.quantity);
                    itoa(val, temp_ustromt_quantity, 10);

                    strcpy(temp_ustromt_st_obj_2.quantity, temp_ustromt_quantity);

                    ustromt_io_obj_1.write((char*)&temp_ustromt_st_obj_2, sizeof(temp_ustromt_st_obj_2));
                }
                else
                {
                    ustromt_io_obj_1.write((char*)&temp_ustromt_st_obj_2, sizeof(temp_ustromt_st_obj_2));
                }
            }
            ustromt_io_obj_1.close();
            ustromt_io_obj_2.close();

            remove("stocks.txt");
            rename("temp_stocks.txt", "stocks.txt");
        }
        ustromt_io_obj.close();

        remove(temp_address_of_bill_stocks_Refund_page);
    }
    void generating_the_money_to_be_paid_back()
    {
        // Printing the column names
        cout<<"\nItems";
        cout<<setw(33)<<setfill(' ')<<"";
        cout<<"Quantity(refunded)";
        cout<<setw(8)<<setfill(' ')<<"";
        cout<<"Selling price(per unit)";
        cout<<setw(7)<<setfill(' ')<<"";
        cout<<"Amount(to be paid back)\n";

        // Printing the main data
        ip_obj.open(temp_address_of_bill_stocks_Refund_page, ios::in);

        float amount=0, subTamt=0;
        int subTsp=0, subTq=0;
        while(ip_obj.read((char*)&display_temp_bill_stock_obj, sizeof(display_temp_bill_stock_obj)))
        {
            cout<<setw(31)<<left<<display_temp_bill_stock_obj.name;
            cout<<setw(25)<<right<<display_temp_bill_stock_obj.quantity;
            cout<<setw(31)<<right<<display_temp_bill_stock_obj.selling_price;

            amount =  static_cast<float>(atoi(display_temp_bill_stock_obj.selling_price)) * static_cast<float>(atoi(display_temp_bill_stock_obj.quantity));
            subTamt += amount;
            subTsp += atoi(display_temp_bill_stock_obj.selling_price);
            subTq += atoi(display_temp_bill_stock_obj.quantity);

            cout<<setw(30)<<right<<fixed<<setprecision(2)<<amount<<endl;

            cout.fill(' '); // Restoring the default value of the fill character
        }
        ip_obj.close();

//        Printing the sub-total row (START)
        cout<<setw(117)<<setfill('-')<<""<<endl; //printing the sub-total row ceiling
        cout.fill(' '); // Restoring the default value of the fill character
        cout<<setw(31)<<left<<"Sub-total ->";
        cout<<setw(25)<<right<<subTq;
        cout<<setw(31)<<right<<subTsp;
        cout<<setw(30)<<right<<subTamt<<endl;
//        Printing the sub-total row (END)

    }
    void refund_option_main_task()
    {
        char romt_choice;
        char temp_id_romt[50]="";
        char temp_quantity_romt[50];

        // Forming the address of the stored-temp_bill_stocks file
        strcpy(address_of_bill_stocks_Refund_page, "bill_files/");
        strcat(address_of_bill_stocks_Refund_page, "Invoice_");
        strcat(address_of_bill_stocks_Refund_page, temp_bill_r_obj.invoice_num);
        strcat(address_of_bill_stocks_Refund_page, "_bill_stocks.txt");

        label_52:
        system("cls");
        displaying_the_bill_RP();

        label_50:
        cout<<"\n\nWhich product do you want to refund? (Write id or press enter to exit)\n"; cin.getline(temp_id_romt, sizeof(temp_id_romt));
        if(strcmp(temp_id_romt,"")==0) employee_homepage(); //if by mistake the user has chosen the option

        // Checking if ID exists in the bill or not
        int exists_in_r = 0;
        temp_r_object_inp_outp.open(address_of_bill_stocks_Refund_page, ios::in);
        while(temp_r_object_inp_outp.read((char*)&temp_bill_st_refu_obj, sizeof(temp_bill_st_refu_obj)))
        {
            if(strcmp(temp_bill_st_refu_obj.id, temp_id_romt)==0)
            {
                exists_in_r = 1;
                break;
            }
            else exists_in_r = 0;
        }
        temp_r_object_inp_outp.close();

        if(exists_in_r == 0)
        {
            cout<<"\nINVALID ID....Re-enter\n";
            goto label_50;
        }

        // if ID is available then check if requested QUANTITY is perfect or not?
        label_51:
        cout<<"\nEnter the quantity you want to refund: "; cin.getline(temp_quantity_romt, sizeof(temp_quantity_romt));

        if(atoi(temp_quantity_romt)<=0)
        {
            cout<<"\nINVAILD QUANTITY (quantity less than or equals to 0)\n";
            goto label_51;
        }
        if(invalid_quantiy_romt(temp_id_romt, temp_quantity_romt)==1) // this tells if requesting more than available
        {
            cout<<"\nINVALID QUANTITY (requesting more than available)\n";
            goto label_51;
        }

        // if both are perfect then proceed ahead

        updating_bill_stocks_romt(temp_id_romt, temp_quantity_romt);
        making_new_temp_bill_stocks_romt(temp_id_romt, temp_quantity_romt);

        cout<<"\nDo you want to refund more?(y/n)\n";
        romt_choice = getch();
        if(romt_choice=='y') goto label_52;

        generating_the_money_to_be_paid_back();
        updating_stocks_txt_refund_option_main_task();
    }
    void generating_temp_generated_invoices_file()
    {
        fstream temp_reGP_io_obj, temp_drfunc_io_obj_2;
        bill temp_drfunc_bill_obj;

        temp_drfunc_io_obj_2.open("bill_files/generated_invoices.txt", ios::in);
        temp_reGP_io_obj.open("bill_files/temp_generated_invoices.txt", ios::app);
        while(temp_drfunc_io_obj_2.read((char*)&temp_drfunc_bill_obj, sizeof(temp_drfunc_bill_obj)))
        {
            temp_reGP_io_obj.write((char*)&temp_drfunc_bill_obj, sizeof(temp_drfunc_bill_obj));
        }

        temp_reGP_io_obj.close();
        temp_drfunc_io_obj_2.close();
    }
    string date_ret_func()
    {
        fstream temp_reGP_io_obj;

        temp_reGP_io_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        temp_reGP_io_obj.read((char*)&temp_bill_ReGP_obj, sizeof(temp_bill_ReGP_obj));
        temp_reGP_io_obj.close();

        return charArrtoString(temp_bill_ReGP_obj.invoice_date);
    }
    int counting_the_number_of_dates()
    {
        fstream temp_ctnod_io_obj, temp_ctnod_io_obj_2;
        bill temp_ctnod_bill_obj, temp_ctnod_bill_obj_2;

        // writing into the temp_generated_invoices file
        temp_ctnod_io_obj_2.open("bill_files/generated_invoices.txt", ios::in);
        temp_ctnod_io_obj_2.read((char*)&temp_ctnod_bill_obj, sizeof(temp_ctnod_bill_obj));
        temp_ctnod_io_obj_2.close();

        temp_ctnod_io_obj.open("bill_files/Temp_generated_invoices.txt", ios::app);
        temp_ctnod_io_obj.write((char*)&temp_ctnod_bill_obj, sizeof(temp_ctnod_bill_obj));
        temp_ctnod_io_obj.close();

        // following code has the main logic
        temp_ctnod_io_obj_2.open("bill_files/generated_invoices.txt", ios::in);
        while(temp_ctnod_io_obj_2.read((char*)&temp_ctnod_bill_obj, sizeof(temp_ctnod_bill_obj)))
        {
            int not_exists = 1;

            temp_ctnod_io_obj.open("bill_files/Temp_generated_invoices.txt", ios::in);
            while(temp_ctnod_io_obj.read((char*)&temp_ctnod_bill_obj_2, sizeof(temp_ctnod_bill_obj_2)))
            {
                if(strcmp(temp_ctnod_bill_obj_2.invoice_date, temp_ctnod_bill_obj.invoice_date)==0)
                {
                    not_exists = 0;
                    break;
                }
            }
            temp_ctnod_io_obj.close();

            temp_ctnod_io_obj.open("bill_files/Temp_generated_invoices.txt", ios::app);
            if(not_exists == 1) temp_ctnod_io_obj.write((char*)&temp_ctnod_bill_obj, sizeof(temp_ctnod_bill_obj));
            temp_ctnod_io_obj.close();
        }
        temp_ctnod_io_obj_2.close();

        int cntr = 0;
        temp_ctnod_io_obj.open("bill_files/Temp_generated_invoices.txt", ios::in);
        while(temp_ctnod_io_obj.read((char*)&temp_ctnod_bill_obj_2, sizeof(temp_ctnod_bill_obj_2)))
        {
            cntr++;
        }
        temp_ctnod_io_obj.close();

        remove("bill_files/Temp_generated_invoices.txt");

        return cntr;
    }
    string extracting_the_invoiceNumber_piod(char* date)
    {
        fstream etin_p_ip_obj;
        bill etin_p_bill_obj;
        string temp_str_etin;

        etin_p_ip_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        while(etin_p_ip_obj.read((char*)&etin_p_bill_obj, sizeof(etin_p_bill_obj)))
        {
            if(strcmp(etin_p_bill_obj.invoice_date, date)==0) break;
        }
        etin_p_ip_obj.close();

        temp_str_etin = charArrtoString(etin_p_bill_obj.invoice_num);

        return temp_str_etin;
    }
    void print_the_total_amt_at_the_inv_num(string inv_num)
    {
        fstream ptdoftin_ip_obj;
        bill ptdoftin_bill_obj;
        char temp_char_arr_ptdoftin[100];

        // converting the string to character array
        int i=0;
        for(i; i<inv_num.length(); i++)
        {
            temp_char_arr_ptdoftin[i] = inv_num[i];
        }
        temp_char_arr_ptdoftin[i] = '\0';

        cout.fill(' ');
        ptdoftin_ip_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        while(ptdoftin_ip_obj.read((char*)&ptdoftin_bill_obj, sizeof(ptdoftin_bill_obj)))
        {
            if(strcmp(ptdoftin_bill_obj.invoice_num, temp_char_arr_ptdoftin)==0)
            {
                cout<<setw(15)<<right<<ptdoftin_bill_obj.total_amount<<"|";
                break;
            }
        }
        ptdoftin_ip_obj.close();

        total_amt_for_rev_gen_page = charArrtoString(ptdoftin_bill_obj.total_amount);
    }
    void print_GST_at_the_inv_num_PIOD(string inv_num)
    {
        fstream pGSTatin_ip_obj;
        total_gst temp_total_gst_object;
        char temp_char_arr_ptdoftin[100];
        char temp_char_arr_ptdoftin_2[100];

        // converting the string to character array
        int i=0;
        for(i; i<inv_num.length(); i++)
        {
            temp_char_arr_ptdoftin[i] = inv_num[i];
        }
        temp_char_arr_ptdoftin[i] = '\0';

        // converting the total_amt_for_rev_gen_page string to character array
        int j=0;
        for(j; j<total_amt_for_rev_gen_page.length(); j++)
        {
            temp_char_arr_ptdoftin_2[j] = total_amt_for_rev_gen_page[j];
        }
        temp_char_arr_ptdoftin_2[j] = '\0';

        cout.fill(' ');
        pGSTatin_ip_obj.open("bill_files/total_gst_of_all_invoices.txt", ios::in);
        while(pGSTatin_ip_obj.read((char*)&temp_total_gst_object, sizeof(temp_total_gst_object)))
        {
            if(strcmp(temp_total_gst_object.invoice_num, temp_char_arr_ptdoftin)==0)
            {
                cout<<setw(11)<<right<<temp_total_gst_object.total_GST<<"|";

                in_valueF_rev_gen_page = atof(temp_char_arr_ptdoftin_2) - atof(temp_total_gst_object.total_GST);
                cout<<setw(14)<<right<<fixed<<setprecision(2)<<in_valueF_rev_gen_page<<endl;
                total_val_earned_rev_gen_page += in_valueF_rev_gen_page;
                break;
            }
        }
        pGSTatin_ip_obj.close();

//        piod_io_obj_2.open("bill_files/total_gst_of_all_invoices.txt", ios::in);
//        while(piod_io_obj_2.read((char*)&temp_total_gst_object, sizeof(temp_total_gst_object)))
//        {
//            if(strcmp(temp_total_gst_object.invoice_num, piod_bill_obj.invoice_num)==0)
//            {
//                cout<<setw(11)<<right<<temp_total_gst_object.total_GST<<"|";
//                in_valueF = atof(piod_bill_obj.total_amount) - atof(temp_total_gst_object.total_GST);
//                cout<<setw(14)<<right<<fixed<<setprecision(2)<<in_valueF<<endl;
//                total_val_earned_rev_gen_page += in_valueF;
//            }
//        }
//        piod_io_obj_2.close();
    }
    void delete_data_of_the_inv_num_PIOD(string inv_num)
    {
        fstream daiotd_io_obj, daiotd_io_obj_2;
        bill daiotd_bill_obj;

        char temp_char_arr_ptdoftin[100];
        // converting the string to character array
        int i=0;
        for(i; i<inv_num.length(); i++)
        {
            temp_char_arr_ptdoftin[i] = inv_num[i];
        }
        temp_char_arr_ptdoftin[i] = '\0';

        daiotd_io_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        daiotd_io_obj_2.open("bill_files/temp_temp_generated_invoices.txt", ios::app);
        while(daiotd_io_obj.read((char*)&daiotd_bill_obj, sizeof(daiotd_bill_obj)))
        {
            if(strcmp(daiotd_bill_obj.invoice_num, temp_char_arr_ptdoftin)!=0)
            {
                daiotd_io_obj_2.write((char*)&daiotd_bill_obj, sizeof(daiotd_bill_obj));
            }
        }
        daiotd_io_obj_2.close();
        daiotd_io_obj.close();

        remove("bill_files/temp_generated_invoices.txt");
        rename("bill_files/temp_temp_generated_invoices.txt", "bill_files/temp_generated_invoices.txt");
    }
    void print_details_of_the_date(char* date)
    {
        fstream piod_io_obj, piod_io_obj_2;
        bill piod_bill_obj;
        total_gst temp_total_gst_object;
        int invoices_cntr=0;
        float in_valueF;

        // counting the number of invoices at that particular date
        piod_io_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        while(piod_io_obj.read((char*)&piod_bill_obj, sizeof(piod_bill_obj)))
        {
            if(strcmp(piod_bill_obj.invoice_date, date)==0)
            {
                invoices_cntr++;
            }
        }
        piod_io_obj.close();

        // running the loop from 1 to invoices_cntr
        cout.fill(' ');
        for(int i=1; i<=invoices_cntr; i++)
        {
            if(i==1) cout<<setw(14)<<left<<date<<"|";
            else cout<<setw(14)<<setfill(' ')<<""<<"|";

            string temp_str = extracting_the_invoiceNumber_piod(date);
            cout<<setw(10)<<right<<temp_str<<"|";
            print_the_total_amt_at_the_inv_num(temp_str);
            print_GST_at_the_inv_num_PIOD(temp_str);
            delete_data_of_the_inv_num_PIOD(temp_str);
        }
//        piod_io_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
//        while(piod_io_obj.read((char*)&piod_bill_obj, sizeof(piod_bill_obj)))
//        {
//            if(strcmp(piod_bill_obj.invoice_date, date)==0)
//            {
//                cout.fill(' ');
//                if(cntr==0)
//                {
//                    cntr++;
//                    cout<<setw(14)<<left<<date<<"|";
//                }
//                else cout<<setw(14)<<setfill(' ')<<""<<"|";
//
//                cout<<setw(10)<<right<<piod_bill_obj.invoice_num<<"|";
//
//                cout.fill(' ');
//
//                cout<<setw(15)<<right<<piod_bill_obj.total_amount<<"|";
//
//                piod_io_obj_2.open("bill_files/total_gst_of_all_invoices.txt", ios::in);
//                while(piod_io_obj_2.read((char*)&temp_total_gst_object, sizeof(temp_total_gst_object)))
//                {
//                    if(strcmp(temp_total_gst_object.invoice_num, piod_bill_obj.invoice_num)==0)
//                    {
//                        cout<<setw(11)<<right<<temp_total_gst_object.total_GST<<"|";
//                        in_valueF = atof(piod_bill_obj.total_amount) - atof(temp_total_gst_object.total_GST);
//                        cout<<setw(14)<<right<<fixed<<setprecision(2)<<in_valueF<<endl;
//                        total_val_earned_rev_gen_page += in_valueF;
//                    }
//                }
//                piod_io_obj_2.close();
//            }
//        }
//        piod_io_obj.close();

        // printing the record floor
        if(i_of_rev_gen != num_of_dates_in_rev_gen)
        {
            cout<<setw(14)<<setfill('-')<<""<<"+";
            cout<<setw(10)<<setfill('-')<<""<<"+";
            cout<<setw(15)<<setfill('-')<<""<<"+";
            cout<<setw(11)<<setfill('-')<<""<<"+";
            cout<<setw(14)<<setfill('-')<<""<<endl;
        }
    }
    void delete_all_instances_of_the_date(char* date)
    {
        fstream daiotd_io_obj, daiotd_io_obj_2;
        bill daiotd_bill_obj;

        daiotd_io_obj.open("bill_files/temp_generated_invoices.txt", ios::in);
        daiotd_io_obj_2.open("bill_files/temp_temp_generated_invoices.txt", ios::app);
        while(daiotd_io_obj.read((char*)&daiotd_bill_obj, sizeof(daiotd_bill_obj)))
        {
            if(strcmp(daiotd_bill_obj.invoice_date, date)!=0)
            {
                daiotd_io_obj_2.write((char*)&daiotd_bill_obj, sizeof(daiotd_bill_obj));
            }
        }
        daiotd_io_obj_2.close();
        daiotd_io_obj.close();

        remove("bill_files/temp_generated_invoices.txt");
        rename("bill_files/temp_temp_generated_invoices.txt", "bill_files/temp_generated_invoices.txt");
    }
    void printing_the_sub_total_in_rev_gen_page()
    {
        cout<<endl<<setw(41)<<setfill(' ')<<""; //printing spaces
        cout<<"+"<<setw(26)<<setfill('-')<<""<<"+"<<endl; //printing box-ceiling
        cout<<setw(41)<<setfill(' ')<<""; //printing spaces
        cout<<"|"<<"Sub total ->";
        cout.fill(' '); // restoring the fill character
        cout<<setw(14)<<right<<fixed<<setprecision(2)<<total_val_earned_rev_gen_page<<"|"<<endl;
        cout<<setw(41)<<setfill(' ')<<""; //printing spaces
        cout<<"+"<<setw(26)<<setfill('-')<<""<<"+"<<endl; //printing box-floor

        remove("bill_files/temp_generated_invoices.txt");
    }
public:
    ims()
    {
        total_val_earned_rev_gen_page = 0;
        admin_found = 0;
        emp_found = 0;
        admin_in_emp_found = 0;
    }
    void log_in_page()
    {
        char c;
        admin temp;
        emp e_temp;
        cout<<"\t\tINVENTORY MANAGEMENT SYSTEM\n";
        cout<<"\t\t\tLog-in page\n\n";

        cout<<"1. Administrator\t\t2. Employee\n\n";
        cout<<"Choose 1 or 2 ( or press any other key to exit): "; c=getch();

        if(c=='1')
        {
            cout<<"\n\nEnter admin username: "; cin.getline(temp.username, sizeof(temp.username));
            cout<<"Enter admin password: "; cin.getline(temp.password, sizeof(temp.password));

            ip_obj.open("admin_accounts.txt", ios::in);
            while(ip_obj.read((char*)&ad_obj, sizeof(ad_obj)))
            {
                if(strcmp(ad_obj.username, temp.username)==0 && strcmp(ad_obj.password, temp.password)==0)
                {
                    admin_found=1;
                    cout<<"\nADMIN FOUND! WELCOME\n";
                    break;
                }
                else admin_found=0;

            }
            if(admin_found==0) cout<<"\nINVALID admin username or password\n";

            ip_obj.close();
        }
        else if(c=='2')
        {
            if(autoidEMP()==101)
            {
                cout<<"\n\nNO EMPLOYEE ACCOUNT FOUND!\n";
                exit(0);
            }
            cout<<"\n\nEnter username: "; cin.getline(e_temp.username, sizeof(e_temp.username));
            cout<<"Enter password: "; cin.getline(e_temp.password, sizeof(e_temp.password));

            //check in employee accounts file
            empF_ip_obj.open("employee_accounts.txt", ios::in);
            while(empF_ip_obj.read((char*)&emp_obj, sizeof(emp_obj)))
            {
                if(strcmp(emp_obj.username, e_temp.username)==0 && strcmp(emp_obj.password, e_temp.password)==0)
                {
                    emp_found=1;
                    cout<<"\nEMPLOYEE FOUND! WELCOME\n";
                    break;
                }
                else emp_found=0;

            }
            empF_ip_obj.close();

            if(emp_found == 1) return;
            else
            {
                //check in admin accounts file
                admin_in_emp_io_object.open("admin_accounts.txt", ios::in);
                while(admin_in_emp_io_object.read((char*)&ad_obj, sizeof(ad_obj)))
                {
                    if(strcmp(ad_obj.username, e_temp.username)==0 && strcmp(ad_obj.password, e_temp.password)==0)
                    {
                        admin_in_emp_found = 1;
                        cout<<"\nADMIN FOUND! WELCOME\n";
                        break;
                    }
                    else admin_in_emp_found=0;

                }
                admin_in_emp_io_object.close();

                if(emp_found==0 && admin_in_emp_found==0) cout<<"\nINVALID employee or admin username or password\n";
            }

        }
        else exit(0);
    }
    void admin_Homepage()
    {
        if(admin_found!=1) return;
        else
        {
            char c;
            system("cls");
            cout<<"\t\t\tINVENTORY MANAGEMENT SYSTEM\n";
            cout<<"\t\t\t\tAdmin Homepage\n\n";
            if(admin_found == 1) cout<<"\nUsername of the admin: "<<ad_obj.username<<endl<<endl;

            cout<<"\n1. Add stock\t\t2. Delete stock\t\t\t3. Modify stock\n";
            cout<<"\n4. Show stocks\t\t5. Create employee account\t6. Delete employee account\n";
            cout<<"\n7. Revenue generated\t8. Recycle bin for stocks\n";
            cout<<"\n\nEnter your choice (or press any other key to exit): "; c=getch();

            if(c=='1')
            {
                label:
                system("cls");

                char d;
                int n;
                cout<<"\t\tADD STOCK PAGE\n";
                cout<<"\nHow many stocks do you want to add? ";
                cin>>n; fflush(stdin);

                for(int i=1; i<=n; i++)
                {
                    cout<<"\nStock number "<<i<<" --> \n";
                    getdata();
                    cout<<endl;

                    storedata();
                }

                cout<<"Do you want to continue adding stocks? (y/n) ";
                d=getch();
                if(d=='y')
                {
                    goto label;
                }
                else if(d=='n')
                {
                    admin_Homepage();
                }
                else exit(0);
            }
            else if(c=='2')
            {
                label_2:
                system("cls");
                cout<<"\t\t\t\t\t\t\t  DELETE STOCK PAGE\n\n\n";

                if(no_data_available()==1)
                {
                    cout<<"\nNO DATA AVAILABLE\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    if(getch()=='y') admin_Homepage();
                    else if(getch()=='n') exit(0);
                    else exit(0);
                }

                char temp_id[20]="";
                char dc;
                char d;
                int delete_stock_found=0;

                showData();

                cout<<"Enter ID of the stock you want to remove (or press enter to exit): ";cin.getline(temp_id, sizeof(temp_id));
                if(strcmp(temp_id,"")==0) admin_Homepage(); //if by mistake the user has chosen the option

                // following code is for user confirmation purpose
                ip_obj.open("stocks.txt", ios::in);
                while(ip_obj.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                {
                    if(strcmp(temp_id, stock_obj_ip.id)==0)
                    {
                        delete_stock_found=1;
                        break;
                    }
                }
                ip_obj.close();

                // if the above code evaluates delete_stock_found as 1 or any other integer then....
                if(delete_stock_found==1)
                {
                    cout<<"\nID of the stock: "<<stock_obj_ip.id;
                    cout<<"\nName of the stock: "<<stock_obj_ip.name<<endl;

                    cout<<"\nPROCEED WITH THE DELETION OF THE STOCK? (y/n)\n"; dc=getch();

                    if(dc=='y')
                    {
                        ip_obj.open("stocks.txt", ios::in);
                        op_obj.open("stocks_temp.txt", ios::app);
                        io_obj_recycle.open("stock_recycle_bin.txt", ios::app);

                        while(ip_obj.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                        {
                            if(strcmp(stock_obj_ip.id, temp_id)!=0) // if record id != user_given id then write record into the temp file
                            {
                                op_obj.write((char*)&stock_obj_ip, sizeof(stock_obj_ip));
                            }
                            else // Entering stock into the recycle bin
                            {
                                io_obj_recycle.write((char*)&stock_obj_ip, sizeof(stock_obj_ip));
                            }
                        }
                        io_obj_recycle.close();
                        ip_obj.close();
                        op_obj.close();

                        // Check if the file has been successfully removed
                        int status = remove("stocks.txt");
                        if (status != 0) {
                            perror("Error deleting file");
                        }
                        else {
                            cout << "\nstock successfully deleted\n" << endl;
                        }
                        rename("stocks_temp.txt","stocks.txt");
                    }
                    else if(dc=='n')
                    {
                        cout<<"\nDELETION CANCELLED\n\nDo you want to go back to the homepage? (y/n)\n";
                        if(getch()=='y') admin_Homepage();
                        else if(getch()=='n') exit(0);
                        else exit(0);
                    }
                    else exit(0);
                }
                else
                {
                    cout<<"\nSTOCK NOT FOUND\n";
                }

                cout<<"\nDo you want to continue deleting? (y/n) ";
                d=getch();
                if(d=='y')
                {
                    goto label_2;
                }
                else if(d=='n')
                {
                    admin_Homepage();
                }
                else exit(0);
            }
            else if(c=='3')
            {
                label_3:
                system("cls");

                cout<<"\t\t\t\t\t\t\t  MODIFY STOCK PAGE\n\n\n";

                if(no_data_available()==1)
                {
                    cout<<"\nNO DATA AVAILABLE\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    if(getch()=='y') admin_Homepage();
                    else if(getch()=='n') exit(0);
                    else exit(0);
                }

                char d;
                char temp_id[20]="";
                int id_not_found=1;

                showData();

                cout<<"\nWhich stock do you want to modify? (give id or press enter to exit): ";
                cin.getline(temp_id, sizeof(temp_id));
                if(strcmp(temp_id,"")==0) admin_Homepage(); //if by mistake the user has chosen the option

                ip_obj.open("stocks.txt", ios::in);
                while(ip_obj.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                {
                    if(strcmp(temp_id, stock_obj_ip.id)==0)
                    {
                        id_not_found=0;
                        break;
                    }
                    else id_not_found=1;
                }
                ip_obj.close();

                // if ID not found is false THEN ONLY proceed
                if(id_not_found != 1)
                {
                    // proceeding further

                    stock temp_stock_ip_obj;
                    char fc;

                    cout<<"\nID of the stock: "<<stock_obj_ip.id;
                    cout<<"\nName of the stock: "<<stock_obj_ip.name<<endl;

                    cout<<"\nWhich field(s) do you want to modify? -->\n";
                    cout<<"\n1. Name of the product\t\t2. Quantity\t\t3. Cost price\n";
                    cout<<"\n4. Selling price\t\t5. GST rate applicable\n\n";
                    label_5:
                    cout<<"\nEnter your field of choice: "; fc = getch(); cout<<endl;

                    if(fc=='1')
                    {
                        char temp_name[50];
                        cout<<"\nEnter the new name: ";
                        cin.getline(temp_name, sizeof(temp_name));

                        // copying the changes into the object to be written in the file
                        strcpy(stock_obj_ip.name, temp_name);
                    }
                    else if(fc=='2')
                    {
                        char temp_quant[50];
                        cout<<"\nEnter the new quantity: ";
                        cin.getline(temp_quant, sizeof(temp_quant));

                        // copying the changes into the object to be written in the file
                        strcpy(stock_obj_ip.quantity, temp_quant);
                    }
                    else if(fc=='3')
                    {
                        char temp_cp[50];
                        cout<<"\nEnter the new cost price: ";
                        cin.getline(temp_cp, sizeof(temp_cp));

                        // copying the changes into the object to be written in the file
                        strcpy(stock_obj_ip.cost_price, temp_cp);
                    }
                    else if(fc=='4')
                    {
                        char temp_sp[50];
                        cout<<"\nEnter the new selling price: ";
                        cin.getline(temp_sp, sizeof(temp_sp));

                        // copying the changes into the object to be written in the file
                        strcpy(stock_obj_ip.selling_price, temp_sp);
                    }
                    else if(fc=='5')
                    {
                        char temp_gst[50];
                        cout<<"\nEnter the new GST rate applicable: ";
                        cin.getline(temp_gst, sizeof(temp_gst));

                        // copying the changes into the object to be written in the file
                        strcpy(stock_obj_ip.gst, temp_gst);
                    }
                    else
                    {
                        cout<<"\nFIELD NON-EXISTENT\n";
                        cout<<"\nDo you want to modify any other stock? (y/n) ";
                        if(getch()=='y')
                        {
                            goto label_3;
                        }
                        else if(getch()=='n')
                        {
                            admin_Homepage();
                        }
                        else exit(0);
                    }

                    // now writing the changes into the file
                    ip_obj.open("stocks.txt", ios::in);
                    op_obj.open("TEMPstocks.txt", ios::app);
                    while(ip_obj.read((char*)&temp_stock_ip_obj, sizeof(temp_stock_ip_obj)))
                    {
                        if(strcmp(temp_stock_ip_obj.id, temp_id)==0)
                        {
                            op_obj.write((char*)&stock_obj_ip, sizeof(stock_obj_ip));
                        }
                        else
                        {
                            op_obj.write((char*)&temp_stock_ip_obj, sizeof(temp_stock_ip_obj));
                        }
                    }
                    op_obj.close();
                    ip_obj.close();

                    remove("stocks.txt");
                    rename("TEMPstocks.txt","stocks.txt");

                    cout<<"\nDo you want to modify the same stock? (y/n)\n";
                    if(getch()=='y') goto label_5;
                }
                else
                {
                    cout<<"\nID NOT FOUND\n";
                }

                cout<<"\nDo you want to continue modifying any other stock? (y/n) ";
                d=getch();
                if(d=='y')
                {
                    goto label_3;
                }
                else if(d=='n')
                {
                    admin_Homepage();
                }
                else exit(0);
            }
            else if(c=='4')
            {
                system("cls");

                char d;
                cout<<"\t\t\t\t\t\t\t  SHOW STOCK PAGE\n\n";
                if(no_data_available()==1)
                {
                    cout<<"\nNO DATA AVAILABLE\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    if(getch()=='y') admin_Homepage();
                    else if(getch()=='n') exit(0);
                    else exit(0);
                }
                showData();

                cout<<"Do you want to continue? (y/n)\n";
                cout<<"y == back to the homepage\nn == complete exit from the program\n";
                d=getch();
                if(d=='y')
                {
                    admin_Homepage();
                }
                else if(d=='n')
                {
                    exit(0);
                }
                else exit(0);
            }
            else if(c=='5')
            {
                label_100:
                system("cls");
                char d_cr_emp_ACcS_UsCh;
                cout<<"\t\t\tCREATE EMPLOYEE ACCOUNT PAGE\n\n";

                readEmployeeAccs();
                cout<<"\nEnter new data -->";
                createEmployeeAcc();

                cout<<"\n\nDo you want to create more employee accounts? (y/n) ";
                d_cr_emp_ACcS_UsCh=getch();
                if(d_cr_emp_ACcS_UsCh=='y')
                {
                    goto label_100;
                }
                else if(d_cr_emp_ACcS_UsCh=='n')
                {
                    admin_Homepage();
                }
                else exit(0);
            }
            else if(c=='6')
            {
                label_200:
                system("cls");
                fstream temporary_ip_object_for_DEC;
                int employee_account_found_for_deletion=0;

                // below code is to check if emp_accs file exists
                char d_DEC_for_user_CHOiCE;
                char temp_id[30]="";
                FILE *fptr = fopen("employee_accounts.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO EMPLOYEE ACCOUNT EXISTS\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    d_DEC_for_user_CHOiCE=getch();
                    if(d_DEC_for_user_CHOiCE=='y')
                    {
                        fclose(fptr);
                        admin_Homepage();
                    }
                    else if(d_DEC_for_user_CHOiCE=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                system("cls");
                cout<<"\t\t\tDELETE EMPLOYEE ACCOUNT PAGE\n\n";

                readEmployeeAccs();

                cout<<"\n\nEnter ID of the employee you want to remove (or press enter to exit): ";cin.getline(temp_id, sizeof(temp_id));
                if(strcmp(temp_id,"")==0) admin_Homepage(); //if by mistake the user has chosen the option

                //following code is for user confirmation purpose
                ip_obj.open("employee_accounts.txt", ios::in);
                while(ip_obj.read((char*)&emp_obj, sizeof(emp_obj)))
                {
                    if(strcmp(temp_id, emp_obj.id)==0)
                    {
                        employee_account_found_for_deletion=1;
                        break;
                    }
                }
                ip_obj.close();

                //if the above code evaluates employee_account_found_for_deletion as 1 or any other integer then....
                if(employee_account_found_for_deletion==1)
                {
                    cout<<"\nUsername of the employee: "<<emp_obj.username;
                    cout<<"\nPassword of the employee: "<<emp_obj.password<<endl;

                    cout<<"\nPROCEED WITH THE DELETION OF THE ACCOUNT? (y/n)\n"; d_DEC_for_user_CHOiCE=getch();

                    if(d_DEC_for_user_CHOiCE=='y')
                    {
                        ip_obj.open("employee_accounts.txt", ios::in);
                        op_obj.open("employee_accounts_temp.txt", ios::app);
                        while(ip_obj.read((char*)&emp_obj, sizeof(emp_obj)))
                        {
                            if(strcmp(emp_obj.id, temp_id)!=0) // if record id != user_given id then write record into the temp file
                            {
                                op_obj.write((char*)&emp_obj, sizeof(emp_obj));
                            }
                        }
                        ip_obj.close();
                        op_obj.close();

                        // Check if the file has been successfully removed
                        int status = remove("employee_accounts.txt");
                        if (status != 0) {
                            perror("Error deleting file");
                        }
                        else {
                            cout << "\nEmployee account successfully deleted\n" << endl;
                        }
                        rename("employee_accounts_temp.txt","employee_accounts.txt");
                    }
                    else if(d_DEC_for_user_CHOiCE=='n')
                    {
                        cout<<"\nDELETION CANCELLED\n\nDo you want to go back to the homepage? (y/n)\n";
                        if(getch()=='y') admin_Homepage();
                        else if(getch()=='n') exit(0);
                        else exit(0);
                    }
                    else exit(0);
                }
                else
                {
                    cout<<"\nEMPLOYEE NOT FOUND\n";
                }

                // Deleting the employee accounts file if it is empty
                fstream temp_IP_obj_for_emp_acc_del_fstream_obj;
                temp_IP_obj_for_emp_acc_del_fstream_obj.open("employee_accounts.txt", ios::in);
                temp_IP_obj_for_emp_acc_del_fstream_obj.seekg(0, ios::end);
                if(temp_IP_obj_for_emp_acc_del_fstream_obj.tellg()==0)
                {
                    temp_IP_obj_for_emp_acc_del_fstream_obj.close();
                    remove("employee_accounts.txt");
                }
                temp_IP_obj_for_emp_acc_del_fstream_obj.close();


                cout<<"\n\nDo you want to continue with the deletion page? (y/n)\n";
                if(getch()=='y') goto label_200;
                else admin_Homepage();
            }
            else if(c=='7')
            {
                system("cls");
                if(strcmp(ad_obj.username,"nsr")!=0 && strcmp(ad_obj.password, "nsr")!=0)
                {
                    cout<<"\nINVALID USERNAME OR PASSWORD\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    cout<<"y == back to the homepage\nn == complete exit from the program\n";
                    if(getch()=='y')
                    {
                        admin_Homepage();
                    }
                    else if(getch()=='n')
                    {
                        exit(0);
                    }
                    else exit(0);
                }

                // below code is to check if generated_invoices exists or not
                char r_choice_2;
                FILE *fptr = fopen("bill_files/generated_invoices.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO BILL EVER GENERATED\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    r_choice_2=getch();
                    if(r_choice_2=='y')
                    {
                        fclose(fptr);
                        admin_Homepage();
                    }
                    else if(r_choice_2=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }
                }
                fclose(fptr);

                cout<<"\t\t\tREVENUE GENERATED PAGE\n\n";

                // printing the column names
                cout<<setw(5)<<setfill(' ')<<""<<"DATE"<<setw(5)<<setfill(' ')<<""<<"|";
                cout<<setw(1)<<setfill(' ')<<""<<"INVOICES"<<setw(1)<<setfill(' ')<<""<<"|";
                cout<<setw(1)<<setfill(' ')<<""<<"AMOUNT GAINED"<<setw(1)<<setfill(' ')<<""<<"|";
                cout<<setw(4)<<setfill(' ')<<""<<"GST"<<setw(4)<<setfill(' ')<<""<<"|";
                cout<<setw(1)<<setfill(' ')<<""<<"AMOUNT LEFT"<<endl;

                // printing the column-name-row floor
                cout<<setw(14)<<setfill('-')<<""<<"+";
                cout<<setw(10)<<setfill('-')<<""<<"+";
                cout<<setw(15)<<setfill('-')<<""<<"+";
                cout<<setw(11)<<setfill('-')<<""<<"+";
                cout<<setw(14)<<setfill('-')<<""<<endl;

                // printing the main data

                num_of_dates_in_rev_gen = counting_the_number_of_dates();
                generating_temp_generated_invoices_file();
                char returned_date_char_arr[60];

                for(i_of_rev_gen=1;  i_of_rev_gen<=num_of_dates_in_rev_gen;  i_of_rev_gen++)
                {
                    strcpy(returned_date_char_arr, "");

                    string returned_date = date_ret_func();
//                  converting string to char array
                    int m;
                    for(m=0; m<returned_date.length(); m++)
                    {
                        returned_date_char_arr[m] = returned_date[m];
                    }
                    returned_date_char_arr[m] = '\0';

                    print_details_of_the_date(returned_date_char_arr);
//                    delete_all_instances_of_the_date(returned_date_char_arr);
                }

                printing_the_sub_total_in_rev_gen_page();

                cout<<"\nDo you want to go back to the homepage?(y/n)\n";
                r_choice_2 = getch();
                if(r_choice_2 == 'y')
                {
                    total_val_earned_rev_gen_page = 0;
                    admin_Homepage();
                }
                else exit(0);
            }
            else if(c=='8')
            {
                label_4:
                system("cls");

                stock temp_stock_obj_ip;
                stock temp_stock_obj_ip_2;
                char temp_id[20]="";
                char d, I_r_A_choice, I_r_A_choice_2;
                int ID_not_found_RBAdHp=0;

                cout<<"\t\t\t\t\t\t\t\tRECYCLE BIN\t\t\n";

                // checking if file is empty
                ip_obj.open("stock_recycle_bin.txt", ios::in | ios::app);
                ip_obj.seekg(0, ios::end);
                if(ip_obj.tellg()==0)
                {
                    cout<<"\nRECYCLE BIN IS EMPTY\n";
                    ip_obj.close();

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    if(getch()=='y') admin_Homepage();
                    else if(getch()=='n') exit(0);
                    else exit(0);
                }
                ip_obj.close();

                // if not then (show the data in the file)
                cout<<"\nDELETED STOCKS --> \n";
                show_data_recycle_bin_ADHP();

                cout<<"\n\nHow do you want to recover? (or press 5 to exit the page)\n\n";
                cout<<"1. Individually\t\t2. Recover all\t\t3. Delete stock permanently\t\t4. Clear recycle bin\n";
                label_80:
                I_r_A_choice = getch();
                if(I_r_A_choice=='1')
                {
                    // Now which data do you want to recover?
                    cout<<"\n\nWhich stock do you want to recover (give id or press enter to exit)?  "; cin.getline(temp_id, sizeof(temp_id));
                    if(strcmp(temp_id,"")==0) admin_Homepage(); //if by mistake the user has chosen the option

                    // checking if requested ID exists or not and storing the data into an object(temp_stock_obj_ip)
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    while(ip_obj.read((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip)))
                    {
                        if(strcmp(temp_stock_obj_ip.id, temp_id)==0)
                        {
                            ID_not_found_RBAdHp=1;
                            break;
                        }
                        else ID_not_found_RBAdHp=0;
                    }
                    ip_obj.close();

                    if(ID_not_found_RBAdHp == 0)
                    {
                        cout<<"\nID NOT FOUND....Re-enter\n";
                        Sleep(1100);
                        goto label_4;
                    }

                    // if ID is found then continue ahead....
                    ip_obj.open("stock_recycle_bin.txt", ios::in);

                    while(ip_obj.read((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip)))
                    {
                        if(strcmp(temp_id, temp_stock_obj_ip.id)==0)
                        {
                            // changing the id of the stock
                            itoa(autoid(),temp_stock_obj_ip.id, 10);

                            // append in the stocks.txt file
                            op_obj.open("stocks.txt", ios::app);
                            op_obj.write((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip));
                            op_obj.close();
                        }
                    }
                    ip_obj.close();

                    // deleting the stock from the recycle bin file
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    op_obj.open("TEMPstock_recycle_bin.txt", ios::app);
                    while(ip_obj.read((char*)&temp_stock_obj_ip_2, sizeof(temp_stock_obj_ip_2)))
                    {
                        if(strcmp(temp_stock_obj_ip_2.id, temp_id)!=0)
                        {
                            op_obj.write((char*)&temp_stock_obj_ip_2, sizeof(temp_stock_obj_ip_2));
                        }
                    }
                    ip_obj.close();
                    op_obj.close();

                    remove("stock_recycle_bin.txt");
                    rename("TEMPstock_recycle_bin.txt", "stock_recycle_bin.txt");

                    cout<<"\nStock has been recovered successfully\n";;

                    // removing the recycle bin file if it is empty
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    ip_obj.seekg(0, ios::end);
                    if(ip_obj.tellg()==0)
                    {
                        ip_obj.close();
                        remove("stock_recycle_bin.txt");

                        cout<<"\nRECYCLE BIN IS EMPTY\n\nDo you want to go back to the homepage? (y/n)\n";
                        I_r_A_choice_2 = getch();
                        if(I_r_A_choice_2=='y') admin_Homepage();
                        else if(I_r_A_choice_2=='n') exit(0);
                        else exit(0);
                    }
                    ip_obj.close();

                    cout<<"\nDo you want to continue recycling? (y/n) ";
                    d=getch();
                    if(d=='y')
                    {
                        goto label_4;
                    }
                    else if(d=='n')
                    {
                        admin_Homepage();
                    }
                    else exit(0);
                }
                else if(I_r_A_choice=='2')
                {
                    // Recover all below
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    while(ip_obj.read((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip)))
                    {
                        // changing the id of the stock
                        itoa(autoid(),temp_stock_obj_ip.id, 10);

                        // append in the stocks.txt file
                        op_obj.open("stocks.txt", ios::app);
                        op_obj.write((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip));
                        op_obj.close();
                    }
                    ip_obj.close();

                    // deleting the recycle bin file
                    int status = remove("stock_recycle_bin.txt");
                    // Check if the file has been successfully removed
                    if (status != 0) {
                        perror("Error deleting file");
                    }
                    else {
                        cout << "" << endl;
                    }

                    cout<<"\nStocks recovered successfully\n";
                    cout<<"\nRECYCLE BIN IS EMPTY NOW\n\nDo you want to go back to the homepage? (y/n)\n";
                    I_r_A_choice_2 = getch();
                    if(I_r_A_choice_2=='y') admin_Homepage();
                    else if(I_r_A_choice_2=='n') exit(0);
                    else exit(0);

                }
                else if(I_r_A_choice=='3')
                {
                    // Now which data do you want to recover?
                    cout<<"\n\nWhich stock do you want to delete (give id or press enter to exit)?  "; cin.getline(temp_id, sizeof(temp_id));
                    if(strcmp(temp_id,"")==0) admin_Homepage(); //if by mistake the user has chosen the option

                    // checking if requested ID exists or not and storing the data into an object(temp_stock_obj_ip)
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    while(ip_obj.read((char*)&temp_stock_obj_ip, sizeof(temp_stock_obj_ip)))
                    {
                        if(strcmp(temp_stock_obj_ip.id, temp_id)==0)
                        {
                            ID_not_found_RBAdHp=1;
                            break;
                        }
                        else ID_not_found_RBAdHp=0;
                    }
                    ip_obj.close();

                    if(ID_not_found_RBAdHp == 0)
                    {
                        cout<<"\nID NOT FOUND\n";
                        Sleep(1100);
                        goto label_4;
                    }

                    // if ID is found then delete the stock from the recycle bin file
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    op_obj.open("TEMPstock_recycle_bin.txt", ios::app);
                    while(ip_obj.read((char*)&temp_stock_obj_ip_2, sizeof(temp_stock_obj_ip_2)))
                    {
                        if(strcmp(temp_stock_obj_ip_2.id, temp_id)!=0)
                        {
                            op_obj.write((char*)&temp_stock_obj_ip_2, sizeof(temp_stock_obj_ip_2));
                        }
                    }
                    ip_obj.close();
                    op_obj.close();

                    remove("stock_recycle_bin.txt");
                    rename("TEMPstock_recycle_bin.txt", "stock_recycle_bin.txt");

                    cout<<"\nStock has been deleted permanently\n";

                    // removing the recycle bin file if it is empty
                    ip_obj.open("stock_recycle_bin.txt", ios::in);
                    ip_obj.seekg(0, ios::end);
                    if(ip_obj.tellg()==0)
                    {
                        ip_obj.close();
                        remove("stock_recycle_bin.txt");

                        cout<<"\nRECYCLE BIN IS EMPTY\n\nDo you want to go back to the homepage? (y/n)\n";
                        I_r_A_choice_2 = getch();
                        if(I_r_A_choice_2=='y') admin_Homepage();
                        else if(I_r_A_choice_2=='n') exit(0);
                        else exit(0);
                    }
                    ip_obj.close();

                    cout<<"\nDo you want to continue with the recycle bin page? (y/n) ";
                    d=getch();
                    if(d=='y')
                    {
                        goto label_4;
                    }
                    else if(d=='n')
                    {
                        admin_Homepage();
                    }
                    else exit(0);
                }
                else if(I_r_A_choice=='4')
                {
                    char choice_for_clear_recy_BIN;

                    cout<<"\nAre you sure?(y/n)\n"; choice_for_clear_recy_BIN = getch();

                    if(choice_for_clear_recy_BIN  == 'y')
                    {
                        // deleting the recycle bin file
                        int status = remove("stock_recycle_bin.txt");
                        // Check if the file has been successfully removed
                        if (status != 0) {
                            perror("Error deleting file");
                        }

                        cout<<"\nRECYCLE BIN IS EMPTY NOW\n\nDo you want to go back to the homepage? (y/n)\n";
                        I_r_A_choice_2 = getch();
                        if(I_r_A_choice_2=='y') admin_Homepage();
                        else if(I_r_A_choice_2=='n') exit(0);
                        else exit(0);
                    }
                    else goto label_4;
                }
                else if(I_r_A_choice=='5') admin_Homepage();
                else
                {
                    cout<<"\nWrong input... Re-enter\n";
                    goto label_80;
                }
            }
            else exit(0);
        }
    }
    void employee_homepage()
    {
        if(emp_found!=1 && admin_in_emp_found!=1) return;
        else
        {
            char c;
            fstream temp_io_obj_1, temp_io_obj_2;
            system("cls");

            cout<<"\t\t\tINVENTORY MANAGEMENT SYSTEM\n";
            cout<<setw(29)<<setfill(' ')<<""<<"Employee Homepage\n\n";

            if(admin_in_emp_found == 1) cout<<"\nUsername of the admin: "<<ad_obj.username<<endl<<endl;
            else if(emp_found == 1) cout<<"\nUsername of the employee: "<<emp_obj.username<<endl<<endl;

            cout<<"\n1. New bill\t\t2. Modify bill\t\t3. Show bill\n\n4. Generate bill\t5. Refund\n";
            cout<<"\n\nEnter your choice (or press any other key to exit): "; c=getch();

            if(c=='1')
            {
                system("cls");

                // below code is to check if a bill is already in process
                char d;
                char temp_id[30];
                char temp_quantity[30];
                FILE *fptr = fopen("bill_files/temp_bill_stocks.txt","r");
                if(fptr != NULL)
                {
                    cout<<"\nPREVIOUS BILL IN PROCESS\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    d=getch();
                    if(d=='y')
                    {
                        fclose(fptr);
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                if(no_data_available()==1)
                {
                    cout<<"\nINVENTORY IS EMPTY\n";

                    cout<<"\nDo you want to continue? (y/n)\n";
                    cout<<"y == back to the homepage\nn == complete exit from the program\n";
                    d=getch();
                    if(d=='y')
                    {
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        exit(0);
                    }
                    else exit(0);
                }

                // if inventory is non-void then....
                cout<<"\t\t\t\tNEW BILL PAGE\n\n";

                cout<<"\nEnter the name of the recipient: "; cin.getline(bill_obj_op.name_of_the_recipient, sizeof(bill_obj_op.name_of_the_recipient));

                if(admin_in_emp_found==1)
                {
                    strcpy(bill_obj_op.employee_name, ad_obj.username);
                }
                else strcpy(bill_obj_op.employee_name, emp_obj.username);

                itoa(auto_invoice_num(), bill_obj_op.invoice_num, 10);
                strcpy(bill_obj_op.invoice_date, __DATE__);


                label_6:
                system("cls");
                cout<<"\t\t\t\t\t\tNEW BILL PAGE\n\n";
                cout<<"\nName of the recipient: "<<bill_obj_op.name_of_the_recipient<<endl<<endl;
                showData_employee_homepage();
                // starting the main billing process....
                int valid_id=0;
                cout<<"\n\nEnter the ID of the product: "; cin.getline(temp_id, sizeof(temp_id));

                // following code checks if ID is available or not....
                temp_io_obj_1.open("stocks.txt",ios::in);
                while(temp_io_obj_1.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                {
                    if(strcmp(stock_obj_ip.id, temp_id)==0)
                    {
                        valid_id=1;
                        break;
                    }
                }
                temp_io_obj_1.close();
                if(valid_id!=1)
                {
                    cout<<"\nINVALID ID! Re-enter....\n";
                    Sleep(700);
                    goto label_6;
                }


                // if ID is available then only proceed ahead....
                label_7:
                cout<<"\nEnter quantity: "; cin.getline(temp_quantity, sizeof(temp_quantity));

                // CODE START --> perfect quantity requested or not?
                if(atoi(temp_quantity)<=0)
                {
                    cout<<"\nINVAILD QUANTITY (quantity less than or equals to 0)\n";
                    goto label_7;
                }
                if(invalid_quantiy(temp_id, temp_quantity)==1) // this tells if requesting more than available
                {
                    cout<<"\nINVALID QUANTITY (requesting more than available)\n";
                    goto label_7;
                }
                // finding the occurrence of the stock in the temp_stocks_file
                if(occurs_in_temp_stocks(temp_id) == 0)
                {
                    write_into_temp_stocks(temp_id, temp_quantity);
                }
                else if(occurs_in_temp_stocks(temp_id) == 1) update_stock_in_temp_stocks(temp_id,temp_quantity);

                if(temp_stocks_quantity_more_than_available(temp_id)==1)
                {
                    cout<<"\nINVALID QUANTITY (aggregating up to quantity more than available quantity)\n";
                    SOLUTION_temp_stocks_quantity_more_than_available(temp_id);
                }

                // printing the data of the temp_bill_stocks file to check if everything is okay or not?
                show_temp_bill_stocks();

                // CODE END --> perfect quantity requested or not?

                cout<<"\n\nWant to make more entries? (y/n) ";
                if(getch()=='y') goto label_6;
                else
                {
                    employee_homepage();
                }
            }
            else if(c=='2')
            {
                system("cls");

                // below code is to check if a bill exists or not
                char d, main_c;
                FILE *fptr = fopen("bill_files/temp_bill_stocks.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO BILL EXISTS TO MODIFY\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    d=getch();
                    if(d=='y')
                    {
                        fclose(fptr);
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                cout<<"\t\t\t\tMODIFY BILL PAGE\n";
                if(no_data_available()==1)
                {
                    cout<<"\nINVENTORY IS EMPTY\n";

                    cout<<"\nDo you want to continue? (y/n)\n";
                    cout<<"y == back to the homepage\nn == complete exit from the program\n";
                    d=getch();
                    if(d=='y')
                    {
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        exit(0);
                    }
                    else exit(0);
                }

                cout<<"\n1. Add item\t\t2. Delete item\t\t3. Modify quantity\n";
                main_c = getch();

                if(main_c=='1')
                {
                    // Add item
                    char temp_id[30]="";
                    char temp_quantity[30];

                    label_8:
                    system("cls");
                    cout<<"\t\t\t\tMODIFY BILL PAGE -- Add item section\n";
                    cout<<"\nName of the recipient: "<<bill_obj_op.name_of_the_recipient<<endl<<endl;
                    showData_employee_homepage();
                    cout<<endl;
                    show_temp_bill_stocks();


                    int valid_id=0;
                    cout<<"\n\nEnter the ID of the product (or press enter to exit): "; cin.getline(temp_id, sizeof(temp_id));
                    if(strcmp(temp_id,"")==0) employee_homepage(); //if by mistake the user has chosen the option

                    // following code checks if ID is available or not....
                    temp_io_obj_1.open("stocks.txt",ios::in);
                    while(temp_io_obj_1.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                    {
                        if(strcmp(stock_obj_ip.id, temp_id)==0)
                        {
                            valid_id=1;
                            break;
                        }
                    }
                    temp_io_obj_1.close();
                    if(valid_id!=1)
                    {
                        cout<<"\nINVALID ID! Re-enter....\n";
                        Sleep(700);
                        goto label_8;
                    }


                    // if ID is available then only proceed ahead....
                    label_9:
                    cout<<"\nEnter quantity: "; cin.getline(temp_quantity, sizeof(temp_quantity));

                    // CODE START --> perfect quantity requested or not?
                    if(atoi(temp_quantity)<=0)
                    {
                        cout<<"\nINVAILD QUANTITY (quantity less than or equals to 0)\n";
                        goto label_9;
                    }
                    if(invalid_quantiy(temp_id, temp_quantity)==1) // this tells if requesting more than available
                    {
                        cout<<"\nINVALID QUANTITY (requesting more than available)\n";
                        goto label_9;
                    }
                    // finding the occurrence of the stock in the temp_stocks_file
                    if(occurs_in_temp_stocks(temp_id) == 0)
                    {
                        write_into_temp_stocks(temp_id, temp_quantity);
                    }
                    else if(occurs_in_temp_stocks(temp_id) == 1)
                    {
                        update_stock_in_temp_stocks(temp_id,temp_quantity);
                    }

                    if(temp_stocks_quantity_more_than_available(temp_id)==1)
                    {
                        cout<<"\nINVALID QUANTITY (aggregating up to quantity more than available quantity)\n";
                        SOLUTION_temp_stocks_quantity_more_than_available(temp_id);
                    }

                    // CODE END --> perfect quantity requested or not?

                    cout<<"\n\nWant to add more products in the bill? (y/n) ";
                    if(getch()=='y') goto label_8;
                    else
                    {
                        employee_homepage();
                    }

                }
                else if(main_c=='2')
                {
                    // Delete item
                    char temp_id[30]="";
                    char temp_quantity[30];

                    label_20:
                    // following code checks if the temp_bill_stocks is empty or not
                    fstream temp_ip_obj;
                    temp_ip_obj.open("bill_files/temp_bill_stocks.txt", ios::in);
                    temp_ip_obj.seekg(0, ios::end);
                    if(temp_ip_obj.tellg()==0)
                    {
                        temp_ip_obj.close();

                        cout<<"\n\nFILE IS EMPTY\n\n";
                        remove("bill_files/temp_bill_stocks.txt");
                        Sleep(1100);
                        employee_homepage();
                    }
                    temp_ip_obj.close();

                    // if it is not empty then move ahead
                    system("cls");
                    cout<<"\t\t\t\tMODIFY BILL PAGE -- Delete item section\n";
                    cout<<"\nName of the recipient: "<<bill_obj_op.name_of_the_recipient<<endl<<endl;
                    show_temp_bill_stocks();
                    cout<<endl;

                    int valid_id=0;
                    cout<<"\n\nEnter the ID of the product (or press enter to exit): "; cin.getline(temp_id, sizeof(temp_id));
                    if(strcmp(temp_id,"")==0) employee_homepage(); //if by mistake the user has chosen the option

                    // following code checks if ID is available(in the bill) or not....
                    temp_io_obj_1.open("bill_files/temp_bill_stocks.txt",ios::in);
                    while(temp_io_obj_1.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                    {
                        if(strcmp(stock_obj_ip.id, temp_id)==0)
                        {
                            valid_id=1;
                            break;
                        }
                    }
                    temp_io_obj_1.close();
                    if(valid_id!=1)
                    {
                        cout<<"\nINVALID ID! Re-enter....\n";
                        Sleep(700);
                        goto label_20;
                    }

                    // following code does the main job
                    ip_obj.open("bill_files/temp_bill_stocks.txt",ios::in);
                    op_obj.open("bill_files/temp_temp_bill_stocks.txt", ios::app);
                    while(ip_obj.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                    {
                        if(strcmp(stock_obj_ip.id, temp_id)!=0)
                        {
                            op_obj.write((char*)&stock_obj_ip, sizeof(stock_obj_ip));
                        }
                    }
                    op_obj.close();
                    ip_obj.close();

                    remove("bill_files/temp_bill_stocks.txt");
                    rename("bill_files/temp_temp_bill_stocks.txt", "bill_files/temp_bill_stocks.txt");


                    cout<<"\n\nWant to delete more items? (y/n) ";
                    if(getch()=='y') goto label_20;
                    else
                    {
                        employee_homepage();
                    }
                }
                else if(main_c=='3')
                {
                    // Modify quantity

                    char temp_id[30]="";
                    char temp_quantity[30];

                    label_13:
                    system("cls");
                    cout<<"\t\t\t\tMODIFY BILL PAGE -- Modify quantity section\n";
                    cout<<"\nName of the recipient: "<<bill_obj_op.name_of_the_recipient<<endl<<endl;
                    showData_employee_homepage();
                    cout<<endl;
                    show_temp_bill_stocks();


                    int valid_id=0;
                    cout<<"\n\nEnter the ID of the product (or press enter to exit): "; cin.getline(temp_id, sizeof(temp_id));
                    if(strcmp(temp_id,"")==0) employee_homepage(); //if by mistake the user has chosen the option

                    // following code checks if ID is available(in the bill) or not....
                    temp_io_obj_1.open("bill_files/temp_bill_stocks.txt",ios::in);
                    while(temp_io_obj_1.read((char*)&stock_obj_ip, sizeof(stock_obj_ip)))
                    {
                        if(strcmp(stock_obj_ip.id, temp_id)==0)
                        {
                            valid_id=1;
                            break;
                        }
                    }
                    temp_io_obj_1.close();
                    if(valid_id!=1)
                    {
                        cout<<"\nINVALID ID! (Not available in the bill) Re-enter....\n";
                        Sleep(1100);
                        goto label_13;
                    }

                    // if ID is available then only proceed ahead....
                    label_14:
                    cout<<"\nEnter new quantity: "; cin.getline(temp_quantity, sizeof(temp_quantity));

                    // CODE START --> perfect quantity requested or not?
                    if(atoi(temp_quantity)<=0)
                    {
                        cout<<"\nINVAILD QUANTITY (quantity less than or equals to 0)\n";
                        goto label_14;
                    }
                    if(invalid_quantiy(temp_id, temp_quantity)==1) // this tells if requesting more than available
                    {
                        cout<<"\nINVALID QUANTITY (requesting more than available)\n";
                        goto label_14;
                    }
                    // CODE END --> perfect quantity requested or not?

                    // If quantity is perfect then proceed ahead with the modifications....
                    modify_the_quantity_in_the_bill(temp_id, temp_quantity);

                    cout<<"\n\nWant to modify more quantities? (y/n) ";
                    if(getch()=='y') goto label_13;
                    else
                    {
                        employee_homepage();
                    }
                }
                else employee_homepage();
            }
            else if(c=='3')
            {
                //show bill page
                system("cls");

                // below code is to check if a bill exists or not
                char d, main_c;
                FILE *fptr = fopen("bill_files/temp_bill_stocks.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO BILL EXISTS\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    d=getch();
                    if(d=='y')
                    {
                        fclose(fptr);
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                cout<<"\t\tSHOW BILL PAGE\n\n";
                cout<<"Name of the recipient: "<<bill_obj_op.name_of_the_recipient<<endl<<endl;

                show_temp_bill_stocks_tabular_for_option_3();

                cout<<"\n\n\nDo you want to go back to the homepage? (y/n)\n";
                d=getch();
                if(d=='y')
                {
                    employee_homepage();
                }
                else if(d=='n')
                {
                    exit(0);
                }
                else exit(0);
            }
            else if(c=='4')
            {
                system("cls");

                // below code is to check if a bill exists or not
                char d, main_c2, re_character_ip;
                FILE *fptr = fopen("bill_files/temp_bill_stocks.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO BILL EXISTS TO GENERATE\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    d=getch();
                    if(d=='y')
                    {
                        fclose(fptr);
                        employee_homepage();
                    }
                    else if(d=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                cout<<"\t\t\t\tBILL GENERATION PAGE\n";
                cout<<"\nDo you want to continue? (y/n)\n";
                main_c2 = getch();

                if(main_c2 == 'y')
                {
                    displaying_the_bill_BGP();

                    bill_generator();

                    // making a copy of temp_bill_stocks file (START)
                    fstream temp_input_object_0, temp_input_object_printer;
                    stock temporary_object;

                    char address[100];
                    temp_input_object_0.open("bill_files/temp_bill_stocks.txt", ios::in);
                    strcpy(address, "bill_files/");
                    strcat(address, "Invoice_");
                    strcat(address, bill_obj_op.invoice_num);
                    strcat(address,"_bill_stocks");
                    strcat(address,".txt");
                    temp_input_object_printer.open(address, ios::app);

                    while(temp_input_object_0.read((char*)&temporary_object, sizeof(temporary_object)))
                    {
                        temp_input_object_printer.write((char*)&temporary_object, sizeof(temporary_object));
                    }
                    temp_input_object_printer.close();
                    temp_input_object_0.close();
                    // (DONE) making a copy of temp_bill_stocks file

                    int st_cntr = count_the_num_of_items_in_bill();

                    for(int i=1; i<=st_cntr; i++)
                    {
                        stocks_updater_after_bill_has_been_generated_R_D_U();
                    }

                    // if temp_bill_stocks is empty then delete it
                    fstream temp_input_object;
                    temp_input_object.open("bill_files/temp_bill_stocks.txt", ios::in);
                    temp_input_object.seekg(0, ios::end);
                    if(temp_input_object.tellg()==0)
                    {
                        temp_input_object.close();
                        remove("bill_files/temp_bill_stocks.txt");
                    }
                    temp_input_object.close();


                    cout<<"\n\nDo you want to go back to the homepage?(y/n)\n";
                    re_character_ip=getch();
                    if(re_character_ip=='y')
                    {
                        employee_homepage();
                    }
                    else if(re_character_ip=='n')
                    {
                        exit(0);
                    }
                    else
                    {
                        exit(0);
                    }
                }
                else if(main_c2 == 'n')
                {
                    employee_homepage();
                }
                else
                {
                    employee_homepage();
                }
            }
            else if(c=='5')
            {
                system("cls");
                char r_choice;

                if( strcmp(ad_obj.username,"nsr")!=0 && strcmp(ad_obj.password, "nsr")!=0 )
                {
                    cout<<"\nINVALID USERNAME OR PASSWORD\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    cout<<"y == back to the homepage\nn == complete exit from the program\n";
                    r_choice=getch();
                    if(r_choice=='y')
                    {
                        employee_homepage();
                    }
                    else if(r_choice=='n')
                    {
                        exit(0);
                    }
                    else exit(0);
                }

                // below code is to check if generated_invoices exists or not
                char r_choice_2;
                FILE *fptr = fopen("bill_files/generated_invoices.txt","r");
                if(fptr == NULL)
                {
                    cout<<"\nNO BILL EVER GENERATED\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    r_choice_2=getch();
                    if(r_choice_2=='y')
                    {
                        fclose(fptr);
                        employee_homepage();
                    }
                    else if(r_choice_2=='n')
                    {
                        fclose(fptr);
                        exit(0);
                    }
                    else
                    {
                        fclose(fptr);
                        exit(0);
                    }

                }
                fclose(fptr);

                // if exists THEN continue ahead
                fstream temp_refund_io_obj;
                char temp_invoice_num[70];
                char dates_ahead[7][70];
                int IN_not_found=0;

                cout<<"\t\t\t\tREFUND PAGE\n";
                label_40:
                cout<<"\nEnter invoice number: "; cin.getline(temp_invoice_num, sizeof(temp_invoice_num));

                // checking if invoice number exists or not and storing the data into an object(temp_bill_r_obj)
                temp_refund_io_obj.open("bill_files/generated_invoices.txt", ios::in);
                while(temp_refund_io_obj.read((char*)&temp_bill_r_obj, sizeof(temp_bill_r_obj)))
                {
                    if(strcmp(temp_bill_r_obj.invoice_num, temp_invoice_num)==0)
                    {
                        IN_not_found=1;
                        break;
                    }
                    else IN_not_found=0;
                }
                temp_refund_io_obj.close();

                if(IN_not_found == 0)
                {
                    cout<<"\nINVOICE NUMBER NOT FOUND....Re-enter\n";
                    goto label_40;
                }

                // FOLLOWING CODE CREATES THE 7 DATES AFTER TODAY
                // Below logic is not perfect because it does not include time, it is based only on date
                // eg. (purchase date & time) Jun 17 2024; 01:16 PM  -> (7 days later) Jun 24 2024 {the products will be refundable for the whole day, which is invalid}

                char month_of_purchase[50];
                char date_of_purchase[50];
                char year_of_purchase[50];
                string complete_date_of_purchase_STR = "";
                char COPY_complete_date_of_purchase[100];

                strcpy(COPY_complete_date_of_purchase, temp_bill_r_obj.invoice_date);
                complete_date_of_purchase_STR = charArrtoString(COPY_complete_date_of_purchase);

                string x = complete_date_of_purchase_STR.substr(0,3); // month
                string y = complete_date_of_purchase_STR.substr(4,2); // date
                string z = complete_date_of_purchase_STR.substr(7,4); // year

                // converting string to char array (MONTH)
                int m,n,o;
                for(m=0; m<x.length(); m++)
                {
                    month_of_purchase[m] = x[m];
                }
                month_of_purchase[m] = '\0';

                // converting string to char array (DATE)
                for(n=0; n<y.length(); n++)
                {
                    date_of_purchase[n] = y[n];
                }
                date_of_purchase[n] = '\0';

                // converting string to char array (YEAR)
                for(o=0; o<z.length(); o++)
                {
                    year_of_purchase[o] = z[o];
                }
                year_of_purchase[o] = '\0';

                // the date has been divided into MONTH, DATE and YEAR. Uncomment below couts to see that
//                cout<<month_of_purchase<<endl;
//                cout<<date_of_purchase<<endl;
//                cout<<year_of_purchase<<endl;


                // NOW INSTALLING THE DATES INTO THE dates_ahead ARRAY
                char COPY_month_of_purchase[50], COPY_year_of_purchase[50];
                strcpy(COPY_month_of_purchase, month_of_purchase);
                strcpy(COPY_year_of_purchase, year_of_purchase);

                if(is_thirty(month_of_purchase)==1) // the months with 30 days
                {
                    if(atoi(date_of_purchase)<=24 && atoi(date_of_purchase)>=10)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70];

                        for(int p=0; p<7; p++)
                        {
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);
                            strcat(temp_date_char_arr, " ");
                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                    else if(atoi(date_of_purchase)<=24 && atoi(date_of_purchase)<10)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70];

                        for(int p=0; p<7; p++)
                        {
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);

                            if(temp_date_int>=1 && temp_date_int<=9)
                            {
                                strcat(temp_date_char_arr, "  ");
                            }
                            else strcat(temp_date_char_arr, " ");

                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                    else if(atoi(date_of_purchase)>24 && atoi(date_of_purchase)<=30)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70], next_month[50];

                        for(int p=0; p<7; p++)
                        {
                            if(temp_date_int == 31)
                            {
                                temp_date_int = 1;
                                string next_month_str = next_month_func(month_of_purchase);

                                // converting string to char array (NEXT MONTH)
                                int q;
                                for(q=0; q<next_month_str.length(); q++)
                                {
                                    next_month[q] = next_month_str[q];
                                }
                                next_month[q] = '\0';

                                strcpy(month_of_purchase, next_month);
                            }
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);

                            if(temp_date_int>=1 && temp_date_int<=9)
                            {
                                strcat(temp_date_char_arr, "  ");
                            }
                            else strcat(temp_date_char_arr, " ");

                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                }
                else if(is_thirty_one(month_of_purchase)==1) // the months with 31 days
                {
                    if(atoi(date_of_purchase)<=25 && atoi(date_of_purchase)>=10)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70];

                        for(int p=0; p<7; p++)
                        {
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);
                            strcat(temp_date_char_arr, " ");
                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                    else if(atoi(date_of_purchase)<=25 && atoi(date_of_purchase)<10)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70];

                        for(int p=0; p<7; p++)
                        {
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);

                            if(temp_date_int>=1 && temp_date_int<=9)
                            {
                                strcat(temp_date_char_arr, "  ");
                            }
                            else strcat(temp_date_char_arr, " ");

                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                    else if(atoi(date_of_purchase)>25 && atoi(date_of_purchase)<=31)
                    {
                        int temp_date_int = atoi(date_of_purchase);
                        char temp_date_char_arr[70], temp_date_char_arr_2[70], next_month[50], next_year[50];

                        for(int p=0; p<7; p++)
                        {
                            if(temp_date_int == 32)
                            {
                                temp_date_int = 1;
                                string next_month_str = next_month_func(month_of_purchase);

                                if(strcmp(month_of_purchase, "Dec")==0)
                                {
                                    itoa((atoi(year_of_purchase)+1), next_year, 10);
                                    strcpy(year_of_purchase, next_year);
                                }

                                // converting string to char array (NEXT MONTH)
                                int q;
                                for(q=0; q<next_month_str.length(); q++)
                                {
                                    next_month[q] = next_month_str[q];
                                }
                                next_month[q] = '\0';

                                strcpy(month_of_purchase, next_month);
                            }
                            strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                            strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                            strcpy(temp_date_char_arr, month_of_purchase);

                            if(temp_date_int>=1 && temp_date_int<=9)
                            {
                                strcat(temp_date_char_arr, "  ");
                            }
                            else strcat(temp_date_char_arr, " ");

                            itoa(temp_date_int, temp_date_char_arr_2, 10);
                            strcat(temp_date_char_arr, temp_date_char_arr_2);
                            strcat(temp_date_char_arr, " ");
                            strcat(temp_date_char_arr, year_of_purchase);

                            strcpy(dates_ahead[p], temp_date_char_arr);

                            temp_date_int++;
                        }
                    }
                }
                else if(strcmp(month_of_purchase, "Feb")==0) // if the month is February
                {
                    if(is_leap(year_of_purchase)==1)
                    {
                        if(atoi(date_of_purchase)<=23 && atoi(date_of_purchase)>=10)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70];

                            for(int p=0; p<7; p++)
                            {
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);
                                strcat(temp_date_char_arr, " ");
                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                        else if(atoi(date_of_purchase)<=23 && atoi(date_of_purchase)<10)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70];

                            for(int p=0; p<7; p++)
                            {
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);

                                if(temp_date_int>=1 && temp_date_int<=9)
                                {
                                    strcat(temp_date_char_arr, "  ");
                                }
                                else strcat(temp_date_char_arr, " ");

                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                        else if(atoi(date_of_purchase)>23 && atoi(date_of_purchase)<=29)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70], next_month[50];

                            for(int p=0; p<7; p++)
                            {
                                if(temp_date_int == 30)
                                {
                                    temp_date_int = 1;
                                    string next_month_str = next_month_func(month_of_purchase);

                                    // converting string to char array (NEXT MONTH)
                                    int q;
                                    for(q=0; q<next_month_str.length(); q++)
                                    {
                                        next_month[q] = next_month_str[q];
                                    }
                                    next_month[q] = '\0';

                                    strcpy(month_of_purchase, next_month);
                                }
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);

                                if(temp_date_int>=1 && temp_date_int<=9)
                                {
                                    strcat(temp_date_char_arr, "  ");
                                }
                                else strcat(temp_date_char_arr, " ");

                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                    }
                    else
                    {
                        if(atoi(date_of_purchase)<=22 && atoi(date_of_purchase)>=10)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70];

                            for(int p=0; p<7; p++)
                            {
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);
                                strcat(temp_date_char_arr, " ");
                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                        else if(atoi(date_of_purchase)<=22 && atoi(date_of_purchase)<10)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70];

                            for(int p=0; p<7; p++)
                            {
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);

                                if(temp_date_int>=1 && temp_date_int<=9)
                                {
                                    strcat(temp_date_char_arr, "  ");
                                }
                                else strcat(temp_date_char_arr, " ");

                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                        else if(atoi(date_of_purchase)>22 && atoi(date_of_purchase)<=28)
                        {
                            int temp_date_int = atoi(date_of_purchase);
                            char temp_date_char_arr[70], temp_date_char_arr_2[70], next_month[50];

                            for(int p=0; p<7; p++)
                            {
                                if(temp_date_int == 29)
                                {
                                    temp_date_int = 1;
                                    string next_month_str = next_month_func(month_of_purchase);

                                    // converting string to char array (NEXT MONTH)
                                    int q;
                                    for(q=0; q<next_month_str.length(); q++)
                                    {
                                        next_month[q] = next_month_str[q];
                                    }
                                    next_month[q] = '\0';

                                    strcpy(month_of_purchase, next_month);
                                }
                                strcpy(temp_date_char_arr, "");  // initializing the char arr with an empty str
                                strcpy(temp_date_char_arr_2, "");  // initializing the char arr with an empty str

                                strcpy(temp_date_char_arr, month_of_purchase);

                                if(temp_date_int>=1 && temp_date_int<=9)
                                {
                                    strcat(temp_date_char_arr, "  ");
                                }
                                else strcat(temp_date_char_arr, " ");

                                itoa(temp_date_int, temp_date_char_arr_2, 10);
                                strcat(temp_date_char_arr, temp_date_char_arr_2);
                                strcat(temp_date_char_arr, " ");
                                strcat(temp_date_char_arr, year_of_purchase);

                                strcpy(dates_ahead[p], temp_date_char_arr);

                                temp_date_int++;
                            }
                        }
                    }
                }

                strcpy(month_of_purchase, COPY_month_of_purchase); // Restoring the respective value after it has been changed above
                strcpy(year_of_purchase, COPY_year_of_purchase); // Restoring the respective value after it has been changed above

                // Now checking if the current system date is in the refundable range
                int refundable=0;
                char cur_sys_date[50];
                char r_choice_4;
                strcpy(cur_sys_date, __DATE__);

                for(int f=0; f<7; f++)
                {
                    if(strcmp(dates_ahead[f], cur_sys_date)==0)
                    {
                        cout<<"\nTHE PRODUCTS ARE REFUNDABLE\n";
                        refundable = 1;
                        break;
                    }
                    else refundable=0;
                }

                // Doing the main job if the products are refundable
                if(refundable == 1)
                {
                    Sleep(1100);
                    refund_option_main_task();

                    cout<<"\nDo you want to go back to the homepage?(y/n)\n";
                    if(getch()=='y') employee_homepage();
                    else exit(0);
                }
                else
                {
                    cout<<"\nTHE PRODUCTS ARE NOT REFUNDABLE\n";

                    cout<<"\nDo you want to go back to the homepage? (y/n)\n";
                    r_choice_4=getch();
                    if(r_choice_4=='y')
                    {
                        employee_homepage();
                    }
                    else if(r_choice_4=='n')
                    {
                        exit(0);
                    }
                    else
                    {
                        exit(0);
                    }
                }
            }
            else
            {
                remove("bill_files/temp_bill_stocks.txt");
                exit(0);
            }
        }
    }
};
int main()
{
    ims obj;
    obj.log_in_page();
    obj.admin_Homepage();
    obj.employee_homepage();
}
