// hi
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Customer;
int Find(vector<Customer> customers, string username);
void SaveInFile(vector<Customer> c);

class Person
{

    string Name;
    string LastName;
    string Password;
    string UserName;

public:
    Person() {}
    Person(string Name, string LastName, string Password, string UserName);

    void SetName(string Name);
    void SetLastName(string LastName);
    void SetUserName(string UserName);
    void SetPassword(string Password);
    string GetUserName();
    string GetName();
    string GetLastName();
    string GetPassword();
};
// constructor
Person::Person(string Name, string LastName, string Password, string UserName)
{
    SetName(Name);
    SetLastName(LastName);
    SetUserName(UserName);
    SetPassword(Password);
}

// Set person
void Person::SetName(string Name)
{
    this->Name = Name;
}
void Person::SetLastName(string LastName)
{
    this->LastName = LastName;
}
void Person::SetUserName(string UserName)
{
    this->UserName = UserName;
}
void Person::SetPassword(string Password)
{
    this->Password = Password;
}

// Get person
string Person::GetName()
{
    return Name;
}
string Person::GetLastName()
{
    return LastName;
}
string Person::GetUserName()
{
    return UserName;
}
string Person::GetPassword()
{
    return Password;
}

class Customer : public Person
{
    unsigned long long int mojoodi;

    bool blocked_customer;

public:
    Customer() { blocked_customer = 0; }
    Customer(string Name, string LastName, string Password, string UserName, long long int mojoodi);
    void Block() { blocked_customer = true; }
    void UnBlock() { blocked_customer = false; }
    bool IsBlocked() { return blocked_customer; };
    void Setmojoodi(unsigned long long int mojoodi);
    unsigned long long int Getmojoodi();
    void Varis(unsigned long long int mablagh);
    bool Bardasht(unsigned long long int mablagh);
    bool Enteghal(unsigned long long int mablagh, Customer c);
    void Menu(vector<Customer> customers);
    void print();
};
// conctructor costomer
Customer::Customer(string Name, string LastName, string Password, string UserName, long long int mojoodi) : Person(Name, LastName, Password, UserName)
{
    Setmojoodi(mojoodi);
    blocked_customer = false;
}

void Customer::Menu(vector<Customer> customers)
{
    if (!blocked_customer)
    {
        while (true)
        {
            cout << "1: varis\n";
            cout << "2: Bardasht\n";
            cout << "3: Enteghal\n";
            cout << "4: Mojoodi\n";
            cout << "5: exit\n";
            int n;
            cin >> n;
            long long int mablagh;

            if (n == 1)
            {
                cout << "mablagh: ";
                cin >> mablagh;
                Varis(mablagh);
                cout << "varis shod\n";
            }
            else if (n == 2)
            {
                cout << "mablagh: ";
                cin >> mablagh;
                bool b = Bardasht(mablagh);
                if (b)
                    cout << "bardasht shod\n";
                else
                    cout << "mojoodi kafi nist";
            }
            else if (n == 3)
            {
                cout << "username maghsad: ";
                string username;
                cin >> username;

                int index = Find(customers, username);
                if (index != -1)
                {
                    Enteghal(mablagh, customers[index]);
                }
                else
                {
                    cout << "username not exist!!!\n";
                }
            }
            else if (n == 4)
            {
                cout << "mojoodi: " << mojoodi << endl;
            }
            else if (n == 5)
            {
                break;
            }
        }
    }
    else
    {
        cout << "you are blocked!!!";
    }
}

// Set customer
void Customer::Setmojoodi(unsigned long long int mojoodi)
{
    this->mojoodi = mojoodi;
}

void Customer::Varis(unsigned long long int mablagh)
{
    mojoodi += mablagh;
}
bool Customer::Bardasht(unsigned long long int mablagh)
{
    if (mojoodi >= mablagh)
    {
        mojoodi -= mablagh;
        return true;
    }
    else
    {
        return false;
    }
}

bool Customer::Enteghal(unsigned long long int mablagh, Customer c)
{
    if (mojoodi >= mablagh)
    {
        mojoodi -= mablagh;
        c.mojoodi += mablagh;
        return true;
    }
    else
    {
        return false;
    }
}
unsigned long long int Customer::Getmojoodi()
{
    return mojoodi;
}

void Customer::print()
{
    cout << "name: " << GetName() << "lastname;: " << GetLastName() << "mojoodi: " << mojoodi;
}

// پیدا کرد نام کاربری ممشتری
int Find(vector<Customer> customers, string username)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].GetUserName() == username)
        {
            return i;
        }
    }

    return -1;
}

class Employee : public Person
{

public:
    Employee(string Name, string LastName, string Password, string UserName) : Person(Name, LastName, Password, UserName) {}
    void Menu(vector<Customer> &customers);
};

void Employee::Menu(vector<Customer>& customers)
{
    while (true)
    {
        cout << "1: block customer\n";
        cout << "2: unblock customer\n";
        cout << "3: print all customer\n";
        cout << "4: exit\n";
        int n;
        cin >> n;

        if (n == 1)
        {
            cout << "username: ";
            string username;
            cin >> username;
            int index = Find(customers, username);
            if (index != -1)
            {
                customers[index].Block();
                

                cout << "blocked!\n";
            }
            else
            {
                cout << "username not exist!!!";
            }
        }
        else if (n == 2)
        {
            cout << "username: ";
            string username;
            cin >> username;
            int index = Find(customers, username);
            if (index != -1)
            {
                customers[index].UnBlock();

                cout << "unblocked!\n";
            }
            else
            {
                cout << "username not exist!!!";
            }
        }
        else if (n == 3)
        {
            for (int i = 0; i < customers.size(); i++)
            {
                customers[i].print();
            }
        }
        else if (n == 4)
        {
            break;
        }
    }
}


class Bank
{
    vector<Customer> customers;
    vector<Employee> employees;
    unsigned long long int LastUsername;

public:
    Bank()
    {
        LastUsername = 0;
    }
    Customer AddCustomer(string name, string lastname, string password, string username, unsigned long long mojoodi);
    void AddEmployee(string name, string lastname, string password, string username);
    friend void restore(Bank &bank);
    void Menu();
    void InputCustomer();
    void InputEmployee();
};

void Bank::Menu()
{

    string name, lastname, password;
    string username;

    while (true)
    {
        cout << endl
             << "Please select your operation:\n";
        cout << "1: signup\n";
        cout << "2: login\n";
        cout << "3: exit\n";
        int n;
        cin >> n;
        if (n == 1)
        {
            cout << "name: ";
            cin >> name;
            cout << "lastname: ";
            cin >> lastname;
            cout << "password: ";
            cin >> password;
            cout << "username: ";
            cin >> username;

            Customer c = AddCustomer(name, lastname, password, username, 0);
            cout << "username: " << c.GetUserName();
            c.Menu(customers);
        }
        else if (n == 2)
        {
            bool found=0;
            cout << "username: ";
            cin >> username;
            cout << "password: ";
            cin >> password;
            for (int i = 0; i < customers.size(); i++)
            {
                if (password == customers[i].GetPassword() && username == customers[i].GetUserName())
                {
                    found=1;

                        customers[i].Menu(customers);
                }
            }

            for (int i = 0; i < employees.size(); i++)
            {
                if (password == employees[i].GetPassword() && username == employees[i].GetUserName())
                {
                    found=1;
                    employees[i].Menu(customers);
                }
            }
            if(!found)
            cout << "username or password not found!!!\n";
        }
        else if (n == 3)
        {
            SaveInFile(customers);
            break;
        }
            SaveInFile(customers);
    }
}

//inpute
void Bank::InputCustomer()
{

    string name, lastname, password;
    string username;
    unsigned long long mojoodi;

    cout << "name: ";
    cin >> name;
    cout << "lastname: ";
    cin >> lastname;
    cout << "password: ";
    cin >> password;
    cout << "mojoodi: ";
    cin >> mojoodi;
    cout << "username: ";
    cin >> username;

    Customer c = AddCustomer(name, lastname, password, username, mojoodi);
}
void Bank::InputEmployee()
{

    string name, lastname, password;
    string username;

    cout << "name: ";
    cin >> name;
    cout << "lastname: ";
    cin >> lastname;
    cout << "password: ";
    cin >> password;
    cout << "username: ";
    cin >> username;

    AddEmployee(name, lastname, password, username);
}


Customer Bank::AddCustomer(string name, string lastname, string password, string username, unsigned long long mojoodi)
{

    Customer c(name, lastname, password, username, mojoodi);
    customers.push_back(c);
    SaveInFile(customers);
    return c;
}
void Bank::AddEmployee(string name, string lastname, string password, string username)
{
    Employee e(name, lastname, password, username);
    employees.push_back(e);
}

fstream file;
const string path = "E:\\data.txt";

void SaveInFile(vector<Customer> customers)
{

    ofstream file("E:\\data.txt");
    if (!file)
        cout << "file not open";
    for (int i = 0; i < customers.size(); i++)

        file << customers[i].GetName() << "\t" << customers[i].GetLastName() << "\t" << customers[i].GetUserName() << "\t" << customers[i].GetPassword() << "\t" << customers[i].Getmojoodi() << "\t" << customers[i].IsBlocked() << "\n";

    file.close();
}

void restore(Bank &bank)
{

    ifstream file("E:\\data.txt");
    if(!file.is_open()) cout<<"errrr";
    string line;
    int counter = 0;
    while (file)
    {
        int step = 0;
        getline(file, line);
        string item = "";
        Customer c;
        if (line != "")
            bank.customers.push_back(c);
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != '\t')
                item += line[i];

            else if (i != 0 && line[i] == '\t' && line[i - 1] != '\t')
            {
                switch (step)
                {
                case 0:
                    bank.customers[counter].SetName(item);
                    break;

                case 1:
                    bank.customers[counter].SetLastName(item);
                    break;
                case 2:
                    bank.customers[counter].SetUserName(item);
                    break;

                case 3:
                    bank.customers[counter].SetPassword(item);
                    break;

                case 4:
                    bank.customers[counter].Setmojoodi(stoi(item));
                    break;

                case 5:

                    break;
                }
                step++;
                item = "";
            }
        }
        if (item == "1")
            bank.customers[counter].Block();
        counter++;
    }
}

int main()
{

    Bank bank;
    restore(bank);

    int n;
    cout << "number customer: ";
    cin >> n;

    for (int i = 0; i < n; i++)
        bank.InputCustomer();

    cout << "number employee: ";
    cin >> n;

    for (int i = 0; i < n; i++)
        bank.InputEmployee();

    bank.Menu();
}
