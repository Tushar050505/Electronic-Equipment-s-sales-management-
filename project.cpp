#include <iostream>
#include <fstream>
using namespace std;
bool checkName(const char Name[])
{
    for (int i = 0; Name[i] != '\0'; ++i)
    {
        if (!((Name[i] >= 'A' && Name[i] <= 'Z') || (Name[i] >= 'a' && Name[i] <= 'Z')))
        {
            return false;
        }
    }
    return true;
}
bool checkDate(const char date[])
{
    for (int i = 0; i < 10; ++i)
    {
        if (date[i] == '\0')
            return false;
    }
    if (date[10] != '\0')
        return false; // Ensure no extra characters

    // Check the format DD-MM-YYYY
    if (date[2] != '-' || date[5] != '-')
    {
        return false;
    }

    // Extract day, month, and year
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    // Validate year, month, day
    if (year <= 2022)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (leap ? 29 : 28))
            return false;
    }
    return true;
}
bool isValidID(const char idd[])
{
    int digitCount = 0;
    bool hasSpecialChar = false;

    const char specialChars[] = "!@#$%^&*()-_=+";
    for (int i = 0; idd[i] != '\0'; ++i)
    {
        if (idd[i] >= '0' && idd[i] <= '9')
        {
            digitCount++;
        }
        else
        {
            for (int j = 0; specialChars[j] != '\0'; ++j)
            {
                if (idd[i] == specialChars[j])
                {
                    hasSpecialChar = true;
                    break;
                }
            }
        }
    }
    return (digitCount >= 2 && hasSpecialChar);
}

class Electrical_equipments
{
    char modal_id[10];
    char product_name[20];
    char company_name[20];
    char product_modal[15];
    int modal_price;
    char selling_date[15];
    char insurance_startingdate[13];
    char insurance_expiredate[13];
public:
    void getdata()
    {
        bool validid = false;
        while (!validid)
        {
            cout << "Enter modal id" << endl;
            cin >> modal_id;
            if (isValidID(modal_id))
            {
                validid = true;
            }
            else
            {
                cout << "Invalid id. Please enter again..." << endl;
            }
        }

        cout << endl
             << "Enter product name: ";
        cin >> product_name;

        cout << "Enter company name" << endl;
        cin >> company_name;

        cout << "Enter product modal" << endl;
        cin >> product_modal;

        cout << "Enter modal price" << endl;
        cin >> modal_price;
        bool validDate = false;
        while (!validDate)
        {
            cout << "Enter selling date(DD-MM-YYYY)" << endl;
            cin >> selling_date;
            if (checkDate(selling_date))
            {
                validDate = true;
            }
            else
            {
                cout << "Invalid date. Please enter again..." << endl;
            }
        }

        bool validDates = false;
        while (!validDates)
        {
            cout << "Enter insurance startingdate(DD-MM-YYYY)" << endl;
            cin >> insurance_startingdate;
            if (checkDate(insurance_startingdate))
            {
                validDates = true;
            }
            else
            {
                cout << "Invalid date. Please enter again..." << endl;
            }
        }

        bool validDatee = false;
        while (!validDatee)
        {
            cout << "Enter insurance expiredate(DD-MM-YYYY)" << endl;
            cin >> insurance_expiredate;
            if (checkDate(insurance_expiredate))
            {
                validDatee = true;
            }
            else
            {
                cout << "Invalid date. Please enter again..." << endl;
            }
        }
    }
    void disp()
    {
        cout << "product name=" << product_name << endl;
        cout << "company name=" << company_name << endl;
        cout << "product modal=" << product_modal << endl;
        cout << "modal id=" << modal_id << endl;
        cout << "modal price=" << modal_price << endl;
        cout << "selling date=" << selling_date << endl;
        cout << "insurance startingdate=" << insurance_startingdate << endl;
        cout << "insurance expiredate=" << insurance_expiredate << endl;
    }
    const char *getidno()
    {
        return modal_id;
    }
    const char *getdate()
    {
        return selling_date;
    }
};

void get_data()
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::app | ios::in | ios::out);

    if (!file)
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    a.getdata();
    file.write((char *)&a, sizeof(a));
    file.close();
}
bool startswith(const char *id1, const char *id2)
{
    int i = 0;
    while (id2[i] != '\0')
    {
        if (id1[i] != id2[i])
            return false;
        i++;
    }
    return id1[i] == '\0';
}
bool contains(const char *line, const char *word)
{
    while (*word)
    {
        if (*line != *word)
        {
            return false;
        }
        ++line;
        ++word;
    }
    return true;
}
void search_id(const char *n)
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::app | ios::in | ios::out);
    bool found = false;
    while (file.read((char *)&a, sizeof(a)))
    {

        if (contains(a.getidno(), n))
        {
            a.disp();
            found = true;
            break;
        }
    }
    file.close();
}
bool contains_date(const char *line, const char *word)
{
    const char *p = line;
    while (*p)
    {
        const char *q = p;
        const char *r = word;
        while (*r && *q == *r)
        {
            ++q;
            ++r;
        }
        if (!*r)
        {
            return true;
        }
        ++p;
    }
    return false;
}
void search_date(const char *n)
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::app | ios::in | ios::out);
    bool found = false;
    while (file.read((char *)&a, sizeof(a)))
    {
        if (contains_date(a.getdate(), n))
        {
            a.disp();
            found = true;
            break;
        }
    }
    file.close();
}
void delete_record(const char *n)
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::app | ios::in | ios::out);

    fstream outFile("temp.txt", ios::out | ios::binary);
    bool found = false;
    while (file.read((char *)&a, sizeof(a)))
    {

        if (!(startswith(a.getidno(), n)))
        {
            outFile.write((char *)&a, sizeof(a));
        }
    }
    file.close();
    outFile.close();
    remove("batra.txt");
    rename("temp.txt", "batra.txt");
}
void modify_record(const char *n)
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::app | ios::in | ios::out);

    fstream outFile("temp.txt", ios::out | ios::binary);

    while (file.read((char *)&a, sizeof(a)))
    {
        if (!contains(a.getidno(), n))
        {
            outFile.write((char *)&a, sizeof(a));
        }
        else
        {
            cout << "\nEnter the new details:" << endl;
            a.getdata();
            outFile.write((char *)&a, sizeof(a));
        }
    }
    file.close();
    outFile.close();
    remove("batra.txt");
    rename("temp.txt", "batra.txt");
}
void display()
{
    Electrical_equipments a;
    fstream file("batra.txt", ios::binary | ios::in);
    while (file.read((char *)&a, sizeof(a)))
    {
        a.disp();
    }
}

int main()
{
    Electrical_equipments a;
    int choice;
    cout << "\t\t\t* * * * * * * * * * * * * *" << endl;
    cout << "\t\t\t*   ELECTRICAL EQUIPMENTS *" << endl;
    cout << "\t\t\t*          SALES          *" << endl;
    cout << "\t\t\t*    MANAGEMENT SYSTEM    *" << endl;
    cout << "\t\t\t* * * * * * * * * * * * * *" << endl;

    do
    {
        cout << "Enter 1 for add sales records " << endl;
        cout << "Enter 2 for search sales records" << endl;
        cout << "Enter 3 for delete slaes records" << endl;
        cout << "Enter 4 for modify sales records" << endl;
        cout << "Enter 5 for display sales record" << endl;
        cout << "Enter 6 for exit " << endl;
        cout << endl
             << "Enter your choice =";
        cin >> choice;
        switch (choice)
        {
        case 1:
            get_data();
            break;
        case 2:
            int v;
            do
            {
                cout << "Enter 1 for search by id(must have 1 special character and 2 numbers)" << endl;
                cout << "Enter 2 for search by date" << endl;
                cout << "Enter 3 for exit" << endl;
                cout << endl
                     << "Enter your choice =";
                cin >> v;
                switch (v)
                {
                case 1:
                    char id[10];
                    cout << endl
                         << "Enter id (must have 1 special character and 2 numbers):";
                    cin >> id;
                    if (isValidID(id))
                    {
                        search_id(id);
                    }
                    else
                    {
                        cout << endl
                             << "Wrong Id !!";
                    }
                    break;

                case 2:
                    char n[11];
                    cout << endl
                         << "Enter date (DD-MM-YYYY):";
                    cin >> n;
                    if (checkDate(n))
                    {
                        search_date(n);
                    }
                    else
                    {
                        cout << endl
                             << "Wrong date !!";
                    }
                    break;
                case 3:
                    break;
                default:
                    cout << endl
                         << "Wrong choice !!";
                    break;
                }
            } while (v != 3);
            break;
        case 3:
            char iddt[10];
            cout << endl
                 << "Enter the id to delete =";
            cin >> iddt;
            if (checkDate(iddt))
            {
                delete_record(iddt);
            }
            break;
        case 4:
            char tv[10];
            cout << endl
                 << "Enter the id to modify =";
            cin >> tv;
            if (isValidID(tv))
            {
                modify_record(tv);
            }
            break;
        case 5:
            display();
            break;
        default:
            cout << endl
                 << "wrong choice ";
        }
    } while (choice != 5);
    return 0;
}