#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "main_classes.h"
using namespace std;

class admin_class
{
private:
    admin obj;
    fstream io_obj;
    int autoid()
    {
        // checking for empty file
        io_obj.open("admin_accounts.txt", ios::in | ios::app);
        io_obj.seekg(0, ios::end);
        if(io_obj.tellg()==0)
        {
            io_obj.close();
            return 101;
        }
        io_obj.close();

        // if not empty then...
        int id;
        io_obj.open("admin_accounts.txt", ios::in);
        while(io_obj.read((char*)&obj, sizeof(obj)));

        id = atoi(obj.id);
        io_obj.close();
        return id+1;
    }

public:
    void create_acc()
    {
        int retVal = autoid();

        if(retVal==101)cout<<"FIRST ADMIN ACCOUNT\n\n";
        itoa(retVal, obj.id, 10);
        cout<<"Enter username: "; cin.getline(obj.username, sizeof(obj.username));
        cout<<"Enter password: "; cin.getline(obj.password, sizeof(obj.password));

        io_obj.open("admin_accounts.txt", ios::app);
        io_obj.write((char*)&obj, sizeof(obj));
        io_obj.close();
    }
    void read()
    {
        cout<<"\nADMIN ACCOUNTS PRESENT IN THE FILE...\n";
        int i=0;
        io_obj.open("admin_accounts.txt", ios::in);
        while(io_obj.read((char*)&obj, sizeof(obj)))
        {
            cout<<"\nAdmin account number "<<i+1<<" --> "<<endl;
            cout<<"ID: "<<obj.id<<endl;
            cout<<"USERNAME: "<<obj.username<<endl;
            cout<<"PASSWORD: "<<obj.password<<endl<<endl;
            i++;
        }
        io_obj.close();
    }
};

int main()
{
    cout<<"\t\t\t\tADMIN ACCOUNTS CREATOR\n";
    admin_class obj;
    obj.create_acc();
    obj.read();
}
