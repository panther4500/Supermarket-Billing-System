#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>

using namespace std;

class product 
{
    protected:
        string product_name;
        float price, discount;
        int product_id, quantity;

    public:
        product()
        {
            product_name = "ABC";
            product_id = 0;
            price = 0;
            quantity = 0;
            discount = 0;
        }
        void getdata()
        {
            cout << "Enter name of Product: ";
            cin >> product_name;
            cout << endl
                << "Enter product id: ";
            cin >> product_id;
            cout << endl
                << "Enter price of product: ";
            cin >> price;
            cout << endl
                << "Enter quantity of product: ";
            cin >> quantity;
            cout << endl
                << "Enter Discount on product(%): ";
            cin >> discount;
        }
        void copy_data(int n)
        {
            product_name = product_name;
            product_id = product_id;
            price = price;
            quantity = n;
            discount = discount;
        }
        void putdata()
        {
            cout << endl
                << "Name: " << product_name << endl;
            cout << "ID: " << product_id << endl;
            cout << "Price: " << price << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Discount: " << discount << "%" << endl;
        }
        void put_tabular()
        {
            cout << "\n\t-------------------------------------------------------------------------------------------------------\n";
            cout << "\t|" << setw(17) << product_name << "|" << setw(17) << product_id << "|" << setw(17) << price << "|" << setw(17) << quantity << "|" << setw(17) << discount << "|";
            cout << "\n\t--------------------------------------------------------------------------------------------------------";
        }
        int getid()
        {
            return product_id;
        }
        int getquantity()
        {
            return quantity;
        }
        string getname()
        {
            return product_name;
        }
        float getprice()
        {
            return price;
        }
        int getdiscount()
        {
            return discount;
        }
} pr;

class customer : public product
{
private:
    int billid;

public:
    void copy_data(int id, int q, product p)
    {
        product_name = p.getname();
        product_id = p.getid();
        price = p.getprice();
        quantity = q;
        discount = p.getdiscount();
        billid = id;
    }
    int getbillid()
    {
        return billid;
    }
} ct;

int n; // Variable to store bill id
void customer_menu(); // Function to display customer menu
void password(); // Function for handeling admin password
void change_password(); // Function to cahnge admin password
void admin_menu(); // Funciton to display admin menu
void menu(int pointer); // Function to display main menu
void write_product(); // Function to write new product into database
void modify_product(); // Function to modify product into database
void delete_product(); // Function to delete product form database
void display_all(); // Function to display all product from database
void display_one(); // Function to display single product
void navigation(); // Function for navigation in main menu
void print_bill(); // Function to print bill after user has purchased items
void searchbill(); // Function to search bill with specific bill id
void select_product(); // Function to purchase product
void delete_product_bill(); // Function to delete product from the bill
void loading(); // Function for loading screen

int main()
{
    loading();
    navigation();
    return 0;
}

void customer_menu()
{
    string ch[] = {"Create New Bill", "Delete item from bill", "Search a bill", "Back to main menu"};
    int i = 0, option;
    while (true)
    {
        system("cls");
        system("COLOR 8f");
        cout << "*************" << endl;
        cout << "*        Customer Billing System      * " << endl;
        cout << "*************" << endl;
        for (i = 0; i < 4; i++)
        {
            cout << "\n"
                 << i + 1 << ")  " << ch[i];
        }
        cout << "\nEnter the Option you are interested in : ";
        cin >> option;
        switch (option)
        {
        case 1:
            select_product();
            break;
        case 2:
            delete_product_bill();
            break;
        case 3:
            searchbill();
            break;
        case 4:
            navigation();
        default:
            cout << "\nEnter Valid input!!!";
        }
    }
}
void password()
{
    bool confirm = true;
    int count = 0;
    char ch;
    ifstream fin;
    ofstream fout;
    string pass1, pass2;
    fin.open("password.txt", ios::in);
    if (!fin.is_open())
    {
        fout.open("password.txt", ios::trunc);
        while (confirm)
        {
            system("cls");
            system("COLOR 8f");
            cout << "\nCreate a new Password : ";
            cin >> pass1;
            cout << "\nConfirm Password : ";
            cin >> pass2;
            if (pass1 == pass2)
            {
                confirm = false;
                fout << pass1;
            }
            else
            {
                cout<<"\n\nPassword and Confirm Password are not same\n";
                Sleep(1500);
            }
            
        }
        fout.close();
        fin.close();
    }
    else
    {
        while (confirm)
        {
            pass1.clear();
            system("cls");
            system("COLOR 8f");
            cout << "\nEnter the Password : ";
            fin >> pass2;
            try
            {
            
                while (true)
                {
                    ch = getch();
                    if ((int)ch == 13)
                    {
                        break;
                    }
                    else if ((int)ch == 8)
                    {
                        if (pass1.size() == 0)
                        {
                            continue;
                        }
                        pass1.pop_back();
                        system("cls");
                        system("COLOR 8f");
                        cout << "\nEnter the Password : ";
                        for (int i = 0; i < pass1.size(); i++)
                        {
                            cout << "*";
                        }
                        Sleep(1000);
                        continue;
                    }
                    pass1.push_back(ch);
                    cout << "*";
                }
                if (pass1 == pass2)
                {
                    confirm = false;
                    cout << "\nCorrect Password :)";
                    Sleep(1500);
                    admin_menu();
                }
                else
                {
                    count++;
                    cout<<"\nThis is your "<<count<<" Attempt, now you have only "<<5-count<<" Attempt left\n";
                    if(count == 5)
                    {
                        cout<<"\nPlease Try again later\n";
                        confirm = false;
                        throw(404.404);
                    }
                    else
                    {
                        throw(2);
                    }
                }
                    
            }
            catch(int)
            {
                cout<<"\nWrong Password Entered\n";
                Sleep(1500);
            }
            catch(double)
            {
                cout<<"Returning to Main Menu";
                Sleep(1500);
                navigation();
            }
            fin.close();
        }
    }
}
void change_password()
{
    string pass1,pass2,newpass1,newpass2;
    int count=0;
    bool flag = true;
    while(flag)
    {   
        Sleep(150);        
        system("cls");
        system("COLOR 8f");
        cout<<"\nEnter your Current Password :";
        cin>>pass1;
        ifstream fin;
        fin.open("password.txt",ios::in);
        fin>>pass2;
        fin.close();
        try
        {
            if(pass1 == pass2)
            {
                flag = false;
                cout<<"\nCorrect Password\n";
                Sleep(1500);
                while(true)
                {
                    try
                    {
                        cout<<"\nEnter your new Password :";
                        cin>>newpass1;
                        cout<<"Confirm your new Password :";
                        cin>>newpass2;
                        if(newpass1 == newpass2)
                        {
                            ofstream fout;
                            fout.open("password.txt",ios::trunc);
                            fout<<newpass1;
                            cout<<"\nPassword changed successfully :)\n\n";
                            break;
                        }
                        else
                        {
                            throw(404);
                        }
                    }
                    catch(int)
                    {
                        Sleep(150);
                        system("cls");
                        system("COLOR 8f");                
                        cout<<"\nBoth Passwords are Not Same, Please Try Again\n";
                        Sleep(1500);
                    }
                    
                }
            }
            else
            {
                throw(404);
            }
        }
        catch(int)
        {
            count++;
            cout<<"\nWrong Password\n";
            cout<<"\nThis is your "<<count<<" Attempt, now you have only "<<5-count<<" Attempt left\n";
            Sleep(1500);
            if(count == 5)
            {
                cout<<"\nPlease Try again later\n";
                flag = false;
            }
        }
        
    }
    
    
}
void admin_menu()
{

    string ch[] = {"Add new product", "Modify a product", "Delete a product", "Display a product", "Display all products","Change the Password", "Exit"};
    int i = 0, option;
    while (true)
    {
        system("cls");
        system("COLOR 8f");
        cout << "*************" << endl;
        cout << "*   For Administrative purpose only   * " << endl;
        cout << "*************" << endl;
        for (i = 0; i < 7; i++)
        {
            cout << "\n"
                 << i + 1 << ")  " << ch[i];
        }
        cout << "\nEnter the Option you are interested in : ";
        cin >> option;
        switch (option)
        {
            case 1:
                write_product();
                break;
            case 2:
                modify_product();
                break;
            case 3:
                delete_product();
                break;
            case 4:
                display_one();
                break;
            case 5:
                display_all();
                break;
            case 6:
                change_password();
                break;
            case 7:
                navigation();
                break;
            default:
                cout << "\nEnter the correct value!!!";
            }
            cout << "\n";
            system("pause");
    }
}
void menu(int pointer)
{
    system("cls");
    system("COLOR 8f");
    cout <<"|___________________|" << endl;
    cout <<"|"<<setw(38)<<"SUPERMARKET BILLING SYSTEM"<<"           |" << endl;
    cout <<"|___________________|" << endl;
    string ch[] = {"Customer Menu", "Admin Menu", "Exit"};
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (i == pointer)
        {
            cout << "--->" << ch[i] << "\n";
        }
        else
        {
            cout << "     " << ch[i] << "\n";
        }
    }
    cout<<"\n\nUse 'w' and 's' to navigate up and down recpectively in the menu\n";
    cout<<"Press 'Enter' for entering any menu :)";
}
void write_product()
{
    ofstream fp;
    fp.open("Product.txt", ios::app);
    pr.getdata();
    fp.write((char *)&pr, sizeof(product));
    fp.close();
    cout << "\nThe product was inserted into database\n";
}
void modify_product()
{
    int id, found = 0;
    fstream fp;
    system("cls");
    system("COLOR 8f");
    display_all();
    cout << "\nPlease Enter The Product No. of The Product: ";
    cin >> id;
    fp.open("Product.txt", ios::in | ios::out);
    while (fp.read((char *)&pr, sizeof(product)) && found == 0)
    {
        if (pr.getid() == id)
        {
            pr.putdata();
            cout << endl
                 << "Please Enter The New Details of Product" << endl;
            pr.getdata();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&pr, sizeof(product));
            cout << endl
                 << "Product Details Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}
void delete_product()
{
    fstream fp;
    ofstream fp1;
    int id;
    bool avail = false;
    display_all();
    cout << "Enter the product no to delete: ";
    cin >> id;
    fp.open("Product.txt", ios::in | ios::out);
    fp1.open("Temp.txt", ios::out);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.getid() != id)
        {
            fp1.write((char *)&pr, sizeof(product));
        }
        else if (pr.getid() == id)
        {
            pr.putdata();
            avail = true;
        }
    }
    if (!avail)
    {
        cout << "\nEnter a Valid Product ID\n";
    }
    else
    {
        cout << "\nProduct Deleted!!!\n";
    }
    fp.close();
    fp1.close();
    remove("Product.txt");
    rename("Temp.txt", "Product.txt");
}
void display_all()
{
    system("cls");
    system("COLOR 8f");
    ifstream fp;
    fp.open("Product.txt", ios::in);
    cout << "*************" << endl;
    cout << "*       Displaying all products       *" << endl;
    cout << "*************" << endl;
    cout << "\n\t-----------------------------------------------------------------------------------------------------------\n";
    cout << "\t|" << setw(18) << "Name |" << setw(18) << "ID |" << setw(18) << "Price |" << setw(18) << "Quantity |" << setw(18) << "Discount |";
    cout << "\n\t-----------------------------------------------------------------------------------------------------------";

    while (fp.read((char *)&pr, sizeof(product)))
    {
        pr.put_tabular();
    }
    fp.close();
}
void display_one()
{
    int id, flag = 0;
    cout << "Enter the Product ID: ";
    cin >> id;
    ifstream fp;
    fp.open("Product.txt", ios::in);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.getid() == id)
        {
            system("cls");
            system("COLOR 8f");
            cout << "***" << endl;
            cout << "*       Displaying Single product     *" << endl;
            cout << "***" << endl;
            pr.putdata();
            flag = 1;
            break;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "The Record for Product ID: " << id << " Doesn't Exist";
    }
}
void navigation()
{
    int i = 0, pointer = 0;
    char ch;
    menu(0);
    while (true)
    {
        ch = getch();
        if (ch == 119)
        {
            pointer -= 1;
            if (pointer <= -1)
            {
                pointer = 2;
            }
            menu(pointer);
        }
        else if (ch == 115)
        {
            pointer += 1;
            if (pointer >= 3)
            {
                pointer = 0;
            }
            menu(pointer);
        }
        else if ((int)ch == 13)
        {
            system("cls");
            system("COLOR 8f");
            if (pointer == 0)
            {
                customer_menu();
                getch();
                pointer = 0;
                menu(pointer);
            }
            else if (pointer == 1)
            {
                password();
                getch();
                pointer = 0;
                menu(pointer);
            }
            else if (pointer == 2)
            {
                exit(0);
            }
        }
    }
}
void print_bill()
{
    system("COLOR 8f");
    bool cond = false;
    cout << "\nYour invoice generated is: \n";
    ifstream fp;
    float total_sum = 0;
    fp.open("Bill.txt", ios::in);
    while (fp.read((char *)&ct, sizeof(customer)) && !cond)
    {
        cond = true;
    }
    fp.seekg(ios::beg);
    if (!cond)
    {
        cout << "\nNothing to print\n";
        cout << "\n";
        system("pause");
    }
    else
    {
        cout << "\n\t--------------------------------------------------------------------------------------------------------\n";
        cout << "\t|" << setw(18) << "ID |" << setw(18) << "Name |" << setw(18) << "Price |" << setw(18) << "Discount |" << setw(18) << "Quantity |" << setw(18) << "Final Price |";
        cout << "\n\t----------------------------------------------------------------------------------------------------------";
        cout << "\n\t|" << setw(18) << " |" << setw(18) << " |" << setw(18) << " |" << setw(18) << "|" << setw(18) << "|" << setw(18) << "|" << endl;
        while (fp.read((char *)&ct, sizeof(customer)))
        {
            if (ct.getbillid() == n)
            {
                cout << "\n\t-------------------------------------------------------------------------------------------------------\n";
                cout << "\t|" << setw(17) << ct.getid() << "|" << setw(17) << ct.getname() << "|" << setw(17) << ct.getprice() << "|" << setw(17) << ct.getdiscount() << "|" << setw(17) << ct.getquantity() << "|" << setw(17) << ct.getprice() * (100 - ct.getdiscount()) / 100 << "|";
                cout << "\n\t--------------------------------------------------------------------------------------------------------";
                total_sum = total_sum + ((ct.getprice() * (100 - ct.getdiscount())) / 100) * ct.getquantity();
            }
        }
        cout << endl
             << setw(109) << "Total Price: " << total_sum;
        cout << "\n";
        system("pause");
    }
    fp.close();
}
void searchbill()
{
    ifstream fout;
    int b,found=0;
    float total_sum = 0;
    fout.open("Bill.txt", ios::in);
    cout << "Enter the Bill no.: ";
    cin >> b;
    cout << "\n\t--------------------------------------------------------------------------------------------------------\n";
    cout << "\t|" << setw(18) << "ID |" << setw(18) << "Name |" << setw(18) << "Price |" << setw(18) << "Discount |" << setw(18) << "Quantity |" << setw(18) << "Final Price |";
    cout << "\n\t----------------------------------------------------------------------------------------------------------";
    cout << "\n\t|" << setw(18) << " |" << setw(18) << " |" << setw(18) << " |" << setw(18) << "|" << setw(18) << "|" << setw(18) << "|" << endl;
    while (fout.read((char *)&ct, sizeof(customer)))
    {
        if (ct.getbillid() == b)
        {
            cout << "\n\t-------------------------------------------------------------------------------------------------------\n";
            cout << "\t|" << setw(17) << ct.getid() << "|" << setw(17) << ct.getname() << "|" << setw(17) << ct.getprice() << "|" << setw(17) << ct.getdiscount() << "|" << setw(17) << ct.getquantity() << "|" << setw(17) << ct.getprice() * (100 - ct.getdiscount()) / 100 << "|";
            cout << "\n\t--------------------------------------------------------------------------------------------------------";
            total_sum = total_sum + ((ct.getprice() * (100 - ct.getdiscount())) / 100) * ct.getquantity();
            found = 1;
        }
    }
    if (found != 1)
    {
        cout<<"Bill Not Found!!!"<<endl;
    }
    else
    {
        cout << endl
        << setw(109) << "Total Price: " << total_sum;
        cout << "\n";   
    }
    system("pause");
    fout.close();
}
void select_product()
{
    int id, flag = 0, quantity, t = 0, i;
    char ch;
    fstream f, f1;
    f.open("billid.txt", ios::in | ios::out | ios::binary);
    if (!f.is_open())
    {
        f1.open("billid.txt", ios::out | ios::binary);
        int a = 10001; // <--------Change first bill id here
        n = a;
        f1.write((char *)&a, sizeof(int));
        f1.close();
    }
    else
    {
        f.read((char *)&i, sizeof(int));
        i++;
        n = i;
        f.seekp(0, ios::beg);
        f.write((char *)&i, sizeof(int));
        f.close();
    }
    do
    {
        system("cls");
        system("COLOR 8f");
        display_all();
        flag = 0;
        t = 0;
        cout << "\nEnter the product id you want to purchase: ";
        cin >> id;
        fstream fp;
        fp.seekg(0, ios::beg);
        fp.open("Product.txt", ios::in | ios::out);
        while (fp.read((char *)&pr, sizeof(product)))
        {
            if (pr.getid() == id)
            {
                fstream fout;
                cout << "Enter the quantity of product: ";
                cin >> quantity;
                if (quantity <= pr.getquantity())
                {
                    int temp = pr.getquantity();
                    pr.copy_data(temp - quantity);
                    int pos = -1 * sizeof(pr);
                    fp.seekp(pos, ios::cur);
                    fp.write((char *)&pr, sizeof(product));
                    fout.open("Bill.txt", ios::app);
                    ct.copy_data(n, quantity, pr);
                    fout.write((char *)&ct, sizeof(customer));
                    fout.close();
                    cout << "Product was added to your invoice!!";
                }
                else
                {
                    cout << "Enter quantity less than or equal to: " << pr.getquantity();
                }
                cout << "\nDo you want to continue(Y/N)? : ";
                cin >> ch;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "Product not found!!!\n";
            Sleep(1000);
            cout << "Do you want to continue(Y/N)? : ";
            cin >> ch;
        }
        fp.close();
    } while (ch == 'y' || ch == 'Y');
    system("cls");
    cout << setw(56) << "Bill Id: " << n;
    print_bill();
}
void delete_product_bill()
{
    fstream fp;
    ofstream fp1;
    int id, bno,flag = 0;
    cout << "Enter Bill No: ";
    cin >> bno;
    cout << "Enter the product no. to delete: ";
    cin >> id;
    fp.open("Bill.txt", ios::in | ios::out);
    fp1.open("Temp.txt", ios::out);
    while (fp.read((char *)&ct, sizeof(customer)))
    {
        if (ct.getid() == id && ct.getbillid() == bno)
        {
            continue;
            flag = 1;
        }
        else
        {
            fp1.write((char *)&ct, sizeof(customer));
        }
    }
    fp.close();
    fp1.close();
    remove("Bill.txt");
    rename("Temp.txt", "Bill.txt");
    if(flag==1)
    {
        cout << "Product Deleted!!!";
    }
    else
    {
        cout<<"Product No.:"<<id<<" in Bill No.: "<<bno<<"Not Found!!!";
    }
    Sleep(2000);
}
void loading()
{
    system("cls");
    //system("COLOR 8f");
    int i = 0;
    system("COLOR 70");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << setw(50);
    cout << "Loading...\n";
    cout << setw(40);
    for (i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            cout << "|";
            Sleep(1000);
        }
        else
        {
            cout << "|";
            Sleep(150);
        }
    }
}
