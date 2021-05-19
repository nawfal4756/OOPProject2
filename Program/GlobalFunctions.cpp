#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <regex>
using namespace std;

#include "Classes.cpp"

// typedef struct
// {
//     char address[30];
//     char province[30];
//     char area[30];
//     char city[30];
//     char country[30];
// } Address;

// typedef struct
// {
//     int date;
//     int month;
//     int year;
// } Date;

// typedef struct
// {
//     int hours;
//     int minutes;
//     int seconds;
// } Time;

// typedef struct {
//     int invoiceID;
//     Date invoiceDate;
//     Time invoiceTime;
//     float amount;
//     float amountToBePaid;
// } CustomerData;

// typedef struct {
//     int id;
//     Date date;
//     float amount;
//     char name[30], description[30];
// } ExpenseStruct;

// typedef struct {
//     // 0 - Cow, 1 - Credit Card, 2 - Customer, 3 - Employee, 4 - Expense, 5 - Feed, 6 - Invoice, 7 - Parcel, 8 - Product, 9 - CowQuantity, 10 - ProductQuantity
//     Date fileD[11];
//     Time fileT[11];
// } FilesTime;

// typedef struct {
//     int id;
//     Date date;
//     Time time;
//     float amount;
// } IncomeStruct;

// typedef struct {
//     int productID;
//     char productName[30];
//     float quantity;
//     float unitPrice;
//     float price;
// } InvoiceList;

// typedef struct
// {
//     int quantity;
//     char name[30];
// } Items;

// typedef struct {
//     int id;
//     Date date;
//     Time time;
//     float quantity;
// } ProductionLog;

// typedef struct {
//     InvoiceList invoiceData;
//     Date date;
//     Time time;
// } ProductSoldList;

// time_t now = time(0);
// tm *localTimeNow = localtime(&now);

// string FileTimeLoc = "../Files/FilesData.txt";

bool contactNumberVerification(unsigned long int number);
int customerInterface();
bool dateVerification (const int day, const int month, const int year, const char type);
bool dobVerification (const int day, const int month, const int year, const char condition);
int employeeInterface();
bool emailAddressVerification(const std::string email);
int fileTimeUpdate(const int indicator);
int numberOfRecords(std::fstream& ptr, int classSize);
bool passwordVerification(const std::string pass);

bool contactNumberVerification(unsigned long int number)
{
    int temp;
    temp = number / 1000000000;

    if (temp == 3)
    {
        if (number >= 3000000000 && number <= 39999999999)
        {
            return true;
        }
    }

    return false;
}

int customerInterface() {
    int userOption, res, tempParcelID;
    Customer customerObj;
    Parcel parcelObj;

    while (1) {
        cout << "Enter 1 to Login" << endl;
        cout << "Enter 2 to Create New Account" << endl;
        cout << "Enter 3 to exit" << endl;
        cout << "Enter desired option: ";
        cin >> userOption;
        fflush(stdin);
        cout << endl << endl;

        if (userOption == 1) {        
            res = customerObj.login();
            if (res == 404) {
                cout << "File operation error!" << endl;
                cout << "Try again later." << endl;
                cout << "Press enter to continue...";
                getchar();
                return 2;
            }
            else if (res == 0) {
                cout << "Incorrect username or password!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
            else if (res == 2) {
                
            }
            else if (res == 1) {
                system("cls");
                while (1) {
                    res = customerNotification(customerObj.getID());
                    if (res == 404) {
                        cout << "File Error! Could not load notifications." << endl << endl;
                    }
                    cout << endl;
                    cout << "Enter 1 to place an order" << endl;
                    cout << "Enter 2 to pay an invoice" << endl;
                    cout << "Enter 3 to see parcel status" << endl;
                    cout << "Enter 4 to modify account details" << endl;
                    cout << "Enter 5 to go back" << endl;
                    cin >> userOption;
                    fflush(stdin);
                    cout << endl << endl;

                    if (userOption == 1) {
                        res = customerObj.generateInvoice();                        
                        if (res == 404) {
                            cout << "File operation error!" << endl;
                            cout << "Try again later." << endl;
                            cout << "Press enter to continue...";
                            getchar();                            
                        }
                        else if (res == 0) {

                        }
                        else if (res == 1) {
                            if (customerObj.customerType == 'R') {
                                res = customerObj.payInvoice();
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == -1) {
                                    cout << "No invoice found of this customer!" << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "Payment Information Confirmation Failure!" << endl;
                                    cout << "Payment Unsuccessful!" << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Payment Successful!" << endl;                                
                                    cout << "Press enter to continue...";
                                    getchar();
                                }                        
                            }                        
                        }
                    }
                    else if (userOption == 2) {
                        res = customerObj.payInvoice();
                        if (res == 404) {
                            cout << "File operation error!" << endl;
                            cout << "Try again later." << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == -1) {
                            cout << "No invoice found of this customer!" << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == 0) {
                            cout << "Payment Information Confirmation Failure!" << endl;
                            cout << "Payment Unsuccessful!" << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == 1) {
                            cout << "Payment Successful!" << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                    }
                    else if (userOption == 3) {
                        res = parcelObj.searchCustomerID(customerObj.getID());
                        if (res == 404) {
                            cout << "File operation error!" << endl;
                            cout << "Try again later." << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == 0) {
                            cout << "No parcel exists for you!" << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == 1) {
                            cout << "Enter parcel ID to see more details on it or enter -1 to go back: ";
                            cin >> tempParcelID;
                            fflush(stdin);
                            if (tempParcelID != -1) {
                                res = parcelObj.searchID(tempParcelID);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                while (res == 0) {
                                    cout << "Incorrect parcel ID entered" << endl;
                                    cout << "Enter parcel ID again to see more details on it: ";
                                    cin >> tempParcelID;
                                    fflush(stdin);
                                    res = parcelObj.searchID(tempParcelID);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                }
                                cout << endl << endl;                                
                                parcelObj.displayInfo();
                            }                            
                        }
                    }
                    else if (userOption == 4) {
                        customerObj.modifyInfo();
                        res = updateCustomerData(customerObj);
                        if (res == 404) {
                            cout << "File operation error!" << endl;
                            cout << "Try again later." << endl;
                            cout << "Press enter to continue...";
                            getchar();
                        }
                        else if (res == 1) {
                            cout << "Account updated successfully!" << endl;                            
                            cout << "Press enter to continue...";
                            getchar();
                        }
                    }
                    else if (userOption == 5) {
                        return 2;
                    }
                    else {
                        cout << "Incorrect option entered!" << endl;
                        cout << "Press enter to continue...";
                        getchar();
                    }
                    system("cls");
                }            
            }
        }
        else if (userOption == 2) {
            customerObj.inputInfo();
            res = customerObj.add();
            if (res == 404) {
                cout << "File operation error!" << endl;
                cout << "Try again later." << endl;
                cout << "Press enter to continue...";
                getchar();
            }
            else if (res == 1) {
                cout << "Customer Added Successfully!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
        }
        else if (userOption == 3) {
            return 2;
        }
        else {
            cout << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }
    
}

bool dateVerification(const int day, const int month, const int year, const char type)
{
    int response = 0;

    if (day == 0)
    {
        if (type == 'I')
        {
            if (year == localTimeNow->tm_year + 1900)
            {
                if (month >= 1 && month <= 12)
                {
                    if (month <= localTimeNow->tm_mon + 1)
                    {
                        response = 1;
                    }
                }
            }

            else if (year < localTimeNow->tm_year)
            {
                if (month >= 1 && month <= 12)
                {
                    response = 1;
                }
            }

            else
            {
                return false;
            }

            if (response == 1)
            {
                return true;
            }

            return false;
        }

        else if (type == 'E')
        {
            if (year == localTimeNow->tm_year + 1900)
            {
                if (month >= 1 && month <= 12)
                {
                    if (month > localTimeNow->tm_mon + 1)
                    {
                        response = 1;
                    }
                }
            }

            else if (year > localTimeNow->tm_year && year < 2031)
            {
                if (month >= 1 && month <= 12)
                {
                    response = 1;
                }
            }

            else
            {
                return false;
            }

            if (response == 1)
            {
                return true;
            }

            return false;
        }
    }

    else if (day > 0)
    {
        if (type == 'X')
        {
            if (year == localTimeNow->tm_year + 1900)
            {
                if (month >= 1 && month <= 12)
                {
                    if (month < localTimeNow->tm_mon + 1)
                    {
                        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                        {
                            if (day > 0 && day <= 31)
                            {
                                response = 1;
                            }
                        }
                        else if (month == 4 || month == 6 || month == 9 || month == 11)
                        {
                            if (day > 0 && day <= 30)
                            {
                                response = 1;
                            }
                        }
                        else if (month == 2)
                        {
                            if (day > 0 && day <= 29)
                            {
                                response = 1;
                            }
                        }                        
                    }

                    else if(month == localTimeNow->tm_mon + 1)
                    {
                        if(day <= localTimeNow->tm_mday)
                        {
                            response = 1;
                        }
                    }

                    else 
                    {
                        return false;
                    }

                    if(response == 1)
                    {
                        return true;
                    }
                }
            }

            else if (year < localTimeNow->tm_year)
            {
                if (month >= 1 && month <= 12)
                {
                    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                        {
                            if (day > 0 && day <= 31)
                            {
                                response = 1;
                            }
                        }
                        else if (month == 4 || month == 6 || month == 9 || month == 11)
                        {
                            if (day > 0 && day <= 30)
                            {
                                response = 1;
                            }
                        }
                        else if (month == 2)
                        {
                            if (day > 0 && day <= 29)
                            {
                                response = 1;
                            }
                        }
                }
            }

            else
            {
                return false;
            }

            if (response == 1)
            {
                return true;
            }

            return false;
        }

        else
        {
            return false;
        }
    }

    return false;
}

bool dobVerification (const int day, const int month, const int year, const char condition) {
    int response = 0;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day > 0 && day <= 31) {
            response = 1;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 0 && day <= 30) {
            response = 1;
        }
    }
    else if (month == 2) {
        if (day > 0 && day <= 29) {
            response = 1;
        }
    }
    
    if (condition == 'P') {
        if (year <= localTimeNow->tm_year + 1882) {
            if (response == 1) {
                return true;
            }
        }
        else {
            return false;
        }
    }
    else if (condition == 'C') {
        if (year <= localTimeNow->tm_year + 1895) {
            if (response == 1) {
                return true;
            }
        }
        else {
            return false;
        }
    }
    

    return false;
}

bool emailAddressVerification(const std::string email) {
    /*The \w matches any character in any case any number of times.
    Then the \.|_ matches if a dot or underscore is present 0 or 1 times.
    Then \w again match n characters.
    Then @ matches the @ in the email.
    Then we again check for n characters and a ‘.’ and a word after it, which must be present at least one or more times.*/
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

int employeeInterface() {
    Employee employeeObj, employeeObj2;
    Cow cowObj;
    Customer customerObj;
    Invoice invoiceObj;
    Parcel parcelObj;
    Product productObj;
    Expense expenseObj;
    AccountsReport accountsReportObj;
    CowReport* cowReportObj;
    CustomerReport customerReportObj;
    ProductReport productReportObj;
    int res, userOption, tempInt;
    string tempString;
    unsigned int long tempContact;
    bool resBool;

    while (1) {
        cout << "Enter 1 to login" << endl;
        cout << "Enter desired option: ";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1) {
            res = employeeObj.login();
            if (res == 2) {
                return 2;
            }
            else if (res == 404) {
                cout << "File operation error!" << endl;
                cout << "Try again later." << endl;
                cout << "Press enter to continue...";
                getchar();
                return 2;
            }
            else if (res == 0) {
                cout << "Incorrect username or password!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
            else if (res == 1) {
                system("cls");
                while (1) {
                    if (employeeObj.accessControl[5]) {
                        res = productNotification();
                        if (res == 404) {
                            cout << "File Error! Could not load notifications." << endl << endl;
                        }
                        cout << endl;
                    }                
                    if (employeeObj.accessControl[0]) {
                        cout << "Enter 1 to add a new admin" << endl;
                        cout << "Enter 2 to modify other employ details" << endl;
                        cout << "Enter 3 to see other employ details" << endl;
                    }
                    if (employeeObj.accessControl[1]) {
                        cout << "Enter 4 to add a cow" << endl;
                        cout << "Enter 5 to modify cow details" << endl;
                        cout << "Enter 6 to add milk produced" << endl;
                        cout << "Enter 7 to see cow information" << endl;
                    }
                    if (employeeObj.accessControl[2]) {
                        cout << "Enter 8 to add a new customer" << endl;
                        cout << "Enter 9 to modify customer details" << endl;
                        cout << "Enter 10 to see customer details" << endl;
                    }
                    if (employeeObj.accessControl[3]) {
                        cout << "Enter 11 to generate an invoice" << endl;
                        cout << "Enter 12 to display invoice information" << endl;
                    }
                    if (employeeObj.accessControl[4]) {
                        cout << "Enter 13 to generate a parcel" << endl;
                        cout << "Enter 14 to view parcel details" << endl;
                    }
                    if (employeeObj.accessControl[5]) {
                        cout << "Enter 15 to add a new product" << endl;
                        cout << "Enter 16 to modify product details" << endl;
                        cout << "Enter 17 to see product details" << endl;
                    }
                    if (employeeObj.accessControl[6]) {
                        cout << "Enter 18 to add a new expense" << endl;
                        cout << "Enter 19 to modify expense details" << endl;
                        cout << "Enter 20 to see expense details" << endl;
                    }
                    if (employeeObj.accessControl[7]) {
                        cout << "Enter 21 to generate Accounts Report" << endl;
                        cout << "Enter 22 to generate Cow Report" << endl;
                        cout << "Enter 23 to generate Customer Report" << endl;
                        cout << "Enter 24 to generate Product Report" << endl;
                    }
                    cout << "Enter 25 to modify you own details" << endl;
                    cout << "Enter 26 to go back" << endl;
                    cout << "Enter desired option: ";
                    cin >> userOption;
                    fflush(stdin);

                    if (userOption == 1) {
                        if (employeeObj.accessControl[0]) {
                            employeeObj2.inputInfo();
                            res = employeeObj2.add();
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Employee Added Successfully!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 2) {
                        if (employeeObj.accessControl[0]) {
                            cout << "Enter 1 to serach employee by ID" << endl;
                            cout << "Enter 2 to serach employee by username" << endl;
                            cout << "Enter 3 to serach employee by email address" << endl;
                            cout << "Enter 4 to serach employee by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter employee ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = employeeObj2.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = employeeObj2.modifyInfo();
                                    if (resBool) {
                                        res = updateEmployeeData(employeeObj2);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Employee Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Employee Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter employee username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = employeeObj2.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = employeeObj2.modifyInfo();
                                    if (resBool) {
                                        res = updateEmployeeData(employeeObj2);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Employee Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Employee Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter employee email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = employeeObj2.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = employeeObj2.modifyInfo();
                                    if (resBool) {
                                        res = updateEmployeeData(employeeObj2);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Employee Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Employee Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter employee contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = employeeObj2.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = employeeObj2.modifyInfo();
                                    if (resBool) {
                                        res = updateEmployeeData(employeeObj2);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Employee Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Employee Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }                    
                    }
                    else if (userOption == 3) {
                        if (employeeObj.accessControl[0]) {
                            cout << "Enter 1 to serach employee by ID" << endl;
                            cout << "Enter 2 to serach employee by username" << endl;
                            cout << "Enter 3 to serach employee by email address" << endl;
                            cout << "Enter 4 to serach employee by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter employee ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = employeeObj2.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    employeeObj2.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter employee username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = employeeObj2.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    employeeObj2.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter employee email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = employeeObj2.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    employeeObj2.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter employee contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = employeeObj2.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No employee found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    employeeObj2.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 4) {
                        if (employeeObj.accessControl[1]) {
                            cowObj.inputInfo();
                            res = cowObj.add();
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Cow Added Successfully!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }                    
                    }
                    else if (userOption == 5) {
                        if (employeeObj.accessControl[1]) {
                            cout << "Enter cow ID or -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                res = cowObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No Cow found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = cowObj.modifyInfo();
                                    if (resBool) {
                                        res = updateCowData(cowObj);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Cow Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Cow Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 6) {
                        if (employeeObj.accessControl[1]) {
                            cout << "Enter cow ID or -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                res = cowObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No Cow found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = cowObj.updateProductionLog();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Record Added Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }                    
                    }
                    else if (userOption == 7) {
                        if (employeeObj.accessControl[1]) {
                            cout << "Enter cow ID or -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                res = cowObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No Cow found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    cowObj.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        } 
                    }
                    else if (userOption == 8) {
                        if (employeeObj.accessControl[2]) {
                            customerObj.inputInfo();
                            res = customerObj.add();
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Employee Added Successfully!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 9) {
                        if (employeeObj.accessControl[2]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = customerObj.modifyInfo();
                                    if (resBool) {
                                        res = updateCustomerData(customerObj);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Customer Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Customer Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = customerObj.modifyInfo();
                                    if (resBool) {
                                        res = updateCustomerData(customerObj);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Customer Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Customer Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = customerObj.modifyInfo();
                                    if (resBool) {
                                        res = updateCustomerData(customerObj);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Customer Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Customer Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    resBool = customerObj.modifyInfo();
                                    if (resBool) {
                                        res = updateCustomerData(customerObj);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Customer Information Not Updated!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Customer Information Updated Successfully!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }                                
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 10) {
                        if (employeeObj.accessControl[2]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    customerObj.displayInfo();
                                    cout << endl <<"Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    customerObj.displayInfo();
                                    cout << endl <<"Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    customerObj.displayInfo();
                                    cout << endl <<"Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    customerObj.displayInfo();
                                    cout << endl <<"Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 11) {
                        if (employeeObj.accessControl[3]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = customerObj.generateInvoice();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Invoice not generated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Invoice Generated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = customerObj.generateInvoice();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Invoice not generated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Invoice Generated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = customerObj.generateInvoice();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Invoice not generated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Invoice Generated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = customerObj.generateInvoice();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Invoice not generated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Invoice Generated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 5) {

                            }                        
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 12) {
                        if (employeeObj.accessControl[3]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = invoiceObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter invoice ID to generate parcel: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = invoiceObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No invoice found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            invoiceObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << endl << endl;
                                        invoiceObj.displayInfo();
                                        cout << endl << "Press enter to continue...";
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << endl << endl;
                                        invoiceObj.displayInfo();
                                        cout << endl << "Press enter to continue...";
                                        getchar();
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter invoice ID to generate parcel: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = invoiceObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No invoice found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            invoiceObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 13) {
                        if (employeeObj.accessControl[4]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = invoiceObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter invoice ID to generate parcel: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = invoiceObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No invoice found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            res = invoiceObj.generateParcel();
                                            if (res == 404) {
                                                cout << "File operation error!" << endl;                                    
                                                cout << "Try again later." << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                            else if (res == 1) {
                                                cout << "Parcel Successfully Created!" << endl;
                                                cout << "Press enter to continue..." << endl;
                                                getchar();
                                            }
                                        }
                                    }
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = invoiceObj.generateParcel();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Parcel Successfully Created!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = invoiceObj.generateParcel();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Parcel Successfully Created!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << "Enter invoice ID to generate parcel: ";
                                    cin >> tempInt;
                                    fflush(stdin);
                                    res = invoiceObj.searchID(tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No invoice found with this ID!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = invoiceObj.generateParcel();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Parcel Successfully Created!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 14) {
                        if (employeeObj.accessControl[4]) {
                            cout << "Enter 1 to serach customer by ID" << endl;
                            cout << "Enter 2 to serach customer by username" << endl;
                            cout << "Enter 3 to serach customer by email address" << endl;
                            cout << "Enter 4 to serach customer by contact number" << endl;
                            cout << "Enter 5 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter customer ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = customerObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = parcelObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No parcel found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter parcel ID to display parcel information: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = parcelObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No parcel found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            parcelObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter customer username: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchUsername(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this username!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = parcelObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No parcel found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter parcel ID to display parcel information: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = parcelObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No parcel found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            parcelObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 3) {
                                cout << "Enter customer email address: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = customerObj.searchEmail(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this email address!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = parcelObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No parcel found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter parcel ID to display parcel information: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = parcelObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No parcel found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            parcelObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 4) {
                                cout << "Enter customer contact number: ";
                                cin >> tempContact;
                                fflush(stdin);
                                res = customerObj.searchConatctNumber(tempContact);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No customer found with this contact number!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = parcelObj.searchCustomerID(customerObj.getID());
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;                                    
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No parcel found for this customer!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Enter parcel ID to display parcel information: ";
                                        cin >> tempInt;
                                        fflush(stdin);
                                        res = parcelObj.searchID(tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;                                    
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No parcel found with this ID!" << endl;
                                            cout << "Press enter to continue..." << endl;
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << endl << endl;
                                            parcelObj.displayInfo();
                                            cout << endl << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                            else if (userOption == 5) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 15) {
                        if (employeeObj.accessControl[5]) {
                            productObj.inputInfo();
                            res = productObj.add();
                            if (res == 404) {
                                cout << "File Error!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Product Added!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                        else {
                        cout << "You do not have access to perform this task!" << endl;
                        cout << "Press enter to continue..." << endl;
                        getchar(); 
                        }
                    }
                    else if (userOption == 16) {
                        if (employeeObj.accessControl[5]) {
                            cout << "Enter product ID: ";
                            cin >> tempInt;
                            fflush(stdin);
                            res = productObj.searchID(tempInt);
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 0) {
                                cout << "No product found with this ID!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                            else if (res == 1) {
                                resBool = productObj.modifyInfo();
                                if (resBool) {
                                    res = updateProductData(productObj);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Product Information Not Updated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Product Information Updated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 17) {
                        if (employeeObj.accessControl[5]) {
                            cout << "Enter 1 to search by product ID" << endl;
                            cout << "Enter 2 to search by product name" << endl;
                            cout << "Enter 3 to go back" << endl;
                            cout << "Enter desired option: ";
                            cin >> userOption;
                            fflush(stdin);

                            if (userOption == 1) {
                                cout << "Enter product ID: ";
                                cin >> tempInt;
                                fflush(stdin);
                                res = productObj.searchID(tempInt);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No product found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    productObj.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 2) {
                                cout << "Enter product name: ";
                                getline(cin, tempString);
                                fflush(stdin);
                                res = productObj.searchName(tempString);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 0) {
                                    cout << "No product found with this ID!" << endl;
                                    cout << "Press enter to continue..." << endl;
                                    getchar();
                                }
                                else if (res == 1) {
                                    cout << endl << endl;
                                    productObj.displayInfo();
                                    cout << endl << "Press enter to continue...";
                                    getchar();
                                }
                            }
                            else if (userOption == 3) {

                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar(); 
                        }
                    }
                    else if (userOption == 18) {
                        if (employeeObj.accessControl[6]) {
                            expenseObj.inputInfo();
                            res = expenseObj.add();
                            if (res == 404) {
                                cout << "File Error!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Expense Added!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 19) {
                        if (employeeObj.accessControl[6]) {
                            cout << "Enter expense ID: ";
                            cin >> tempInt;
                            fflush(stdin);
                            res = expenseObj.searchID(tempInt);
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 0) {
                                cout << "No expense found with this ID!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                            else if (res == 1) {
                                resBool = expenseObj.modifyInfo();
                                if (resBool) {
                                    res = updateExpenseData(expenseObj);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Expense Information Not Updated!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Expense Information Updated Successfully!" << endl;
                                        cout << "Press enter to continue..." << endl;
                                        getchar();
                                    }
                                }                                
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 20) {
                        if (employeeObj.accessControl[6]) {
                            cout << "Enter expense ID: ";
                            cin >> tempInt;
                            fflush(stdin);
                            res = expenseObj.searchID(tempInt);
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 0) {
                                cout << "No expense found with this ID!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                            else if (res == 1) {
                                cout << endl << endl;
                                expenseObj.displayInfo();
                                cout << endl << "Press enter to continue...";
                                getchar();
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 21) {
                        if (employeeObj.accessControl[7]) {
                            res = accountsReportObj.read();
                            if (res == 404) {
                                res = gatherAccountsData(accountsReportObj);
                                if (res == 404) {
                                    cout << "File operation error!" << endl;
                                    cout << "Try again later." << endl;
                                    cout << "Press enter to continue...";
                                    getchar();
                                }
                                else if (res == 1) {
                                    res = accountsReportObj.printReport();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Report printed successfully!" << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                }
                            }
                            else if (res == 1) {
                                if (accountsReportObj.verifyUpdatedDateTime()) {
                                    res = accountsReportObj.printReport();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        cout << "Report printed successfully!" << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                }
                                else {
                                    res = gatherAccountsData(accountsReportObj);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = accountsReportObj.printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 22) {
                        if (employeeObj.accessControl[7]) {
                            cout << "Enter cow ID to generate report or -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                cowReportObj = new CowReport(tempInt);
                                res = cowReportObj->read();
                                if (res == 404) {
                                    res = cowReportObj->gatherData();
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No Cow with this ID found!" << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = cowReportObj->printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                                else if (res == 1) {
                                    if (cowReportObj->verifyUpdatedDateTime()) {
                                        res = cowReportObj->printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                    else {
                                        res = cowReportObj->gatherData();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No Cow with this ID found!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            res = cowReportObj->printReport();
                                            if (res == 404) {
                                                cout << "File operation error!" << endl;
                                                cout << "Try again later." << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                            else if (res == 1) {
                                                cout << "Report printed successfully!" << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                        }
                                    }
                                }
                                delete cowReportObj;
                            }                        
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 23) {
                        if (employeeObj.accessControl[7]) {
                            cout << "Enter customer ID to generate report or neter -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                res = customerReportObj.read();
                                if (res == 404) {
                                    res = gatherCustomerData(customerReportObj, tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No Customer with this ID found!" << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = customerReportObj.printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                                else if (res == 1) {
                                    if (customerReportObj.verifyUpdatedDateTime()) {
                                        res = customerReportObj.printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                    else {
                                        res = gatherCustomerData(customerReportObj, tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No Customer with this ID found!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            res = customerReportObj.printReport();
                                            if (res == 404) {
                                                cout << "File operation error!" << endl;
                                                cout << "Try again later." << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                            else if (res == 1) {
                                                cout << "Report printed successfully!" << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                        }
                                    }
                                }
                            }                        
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 24) {
                        if (employeeObj.accessControl[7]) {
                            cout << "Enter product ID to generate report or neter -1 to go back: ";
                            cin >> tempInt;
                            fflush(stdin);
                            if (tempInt != -1) {
                                res = productReportObj.read();
                                if (res == 404) {
                                    res = gatherProductData(productReportObj, tempInt);
                                    if (res == 404) {
                                        cout << "File operation error!" << endl;
                                        cout << "Try again later." << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 0) {
                                        cout << "No Product with this ID found!" << endl;
                                        cout << "Press enter to continue...";
                                        getchar();
                                    }
                                    else if (res == 1) {
                                        res = productReportObj.printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                }
                                else if (res == 1) {
                                    if (productReportObj.verifyUpdatedDateTime()) {
                                        res = productReportObj.printReport();
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            cout << "Report printed successfully!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                    }
                                    else {
                                        res = gatherProductData(productReportObj, tempInt);
                                        if (res == 404) {
                                            cout << "File operation error!" << endl;
                                            cout << "Try again later." << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 0) {
                                            cout << "No Product with this ID found!" << endl;
                                            cout << "Press enter to continue...";
                                            getchar();
                                        }
                                        else if (res == 1) {
                                            res = productReportObj.printReport();
                                            if (res == 404) {
                                                cout << "File operation error!" << endl;
                                                cout << "Try again later." << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                            else if (res == 1) {
                                                cout << "Report printed successfully!" << endl;
                                                cout << "Press enter to continue...";
                                                getchar();
                                            }
                                        }
                                    }
                                }
                            }                        
                        }
                        else {
                            cout << "You do not have access to perform this task!" << endl;
                            cout << "Press enter to continue..." << endl;
                            getchar();
                        }
                    }
                    else if (userOption == 25) {
                        resBool = employeeObj.modifyInfo();
                        if (resBool) {
                            res = updateEmployeeData(employeeObj);
                            if (res == 404) {
                                cout << "File operation error!" << endl;
                                cout << "Employee Information Not Updated!" << endl;
                                cout << "Try again later." << endl;
                                cout << "Press enter to continue...";
                                getchar();
                            }
                            else if (res == 1) {
                                cout << "Employee Information Updated Successfully!" << endl;
                                cout << "Press enter to continue..." << endl;
                                getchar();
                            }
                        }
                    }
                    else if (userOption == 26) {
                        return 2;
                    }                    
                    else {
                        cout << "Incorrect option entered!" << endl;
                        cout << "Press enter to continue...";
                        getchar();
                    }
                    system("cls");
                }
            }
        }
        else if (userOption == 707581692) {
            cout << "Enter master password: ";
            getline(cin, tempString);
            fflush(stdin);

            if (tempString == "FOFF@0396") {
                employeeObj.inputInfo();
                res = employeeObj.add();
                if (res == 404) {
                    cout << "File Error!" << endl;
                    cout << "Press enter to continue..." << endl;
                    getchar();
                }
                else if (res == 1) {
                    cout << "Employee Added!" << endl;
                    cout << "Press enter to continue..." << endl;
                    getchar();
                }
            }
        }
        system("cls");
    }
}

int fileTimeUpdate(const int indicator) {
    fstream file;
    FilesTime data;
    int counter;
    
    file.open(FileTimeLoc, ios::binary | ios::in);

    if (file) {
        file.read((char*)&data, sizeof(FilesTime));
        file.close();
    }
    else if (!file) {
        for (counter = 0; counter < 11; counter++) {
            data.fileD[counter].date = 0;
            data.fileD[counter].month = 0;
            data.fileD[counter].year = 0;
            data.fileT[counter].hours = 0;
            data.fileT[counter].minutes = 0;
            data.fileT[counter].seconds = 0;
        }
    }

    file.open(FileTimeLoc, ios::binary | ios::out | ios::trunc);

    if (!file) {
        return 404;
    }

    data.fileD[indicator].date = localTimeNow->tm_mday;
    data.fileD[indicator].month = localTimeNow->tm_mon + 1;
    data.fileD[indicator].year = localTimeNow->tm_year + 1900;
    data.fileT[indicator].hours = localTimeNow->tm_hour;
    data.fileT[indicator].minutes = localTimeNow->tm_min;
    data.fileT[indicator].seconds = localTimeNow->tm_sec;
    
    file.write((char*)&data, sizeof(FilesTime));
    file.close();
    return 1;
}

int numberOfRecords(std::fstream& ptr, int classSize) {
    int size;

    ptr.seekg(0, std::ios::end);
    size = ptr.tellg();

    size = size / classSize;

    ptr.seekg(0, std::ios::beg);

    return size;
}

bool passwordVerification(const std::string pass)
{
    int x;
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;

    for (x = 0; x < pass.size(); x++)
    {
        if (islower(pass[x]))
            hasLower = true;
        if (isupper(pass[x]))
            hasUpper = true;
        if (isdigit(pass[x]))
            hasDigit = true;

        if (!islower(pass[x]))
        {
            if (!isupper(pass[x]))
            {
                if (!isdigit(pass[x]))
                {
                    specialChar = true;
                }
            }
        }
    }

    if (!hasDigit || !hasLower || !hasUpper || !specialChar || pass.size() < 8)
    {
        return false;
    }

    else
    {
        return true;
    }
}