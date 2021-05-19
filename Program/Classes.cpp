#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <regex>
using namespace std;

// #include "GlobalFunctions.cpp"

typedef struct
{
    char address[30];
    char province[30];
    char area[30];
    char city[30];
    char country[30];
} Address;

typedef struct
{
    int date;
    int month;
    int year;
} Date;

typedef struct
{
    int hours;
    int minutes;
    int seconds;
} Time;

typedef struct {
    int invoiceID;
    Date invoiceDate;
    Time invoiceTime;
    float amount;
    float amountToBePaid;
} CustomerData;

typedef struct {
    int id;
    Date date;
    float amount;
    char name[30], description[30];
} ExpenseStruct;

typedef struct {
    // 0 - Cow, 1 - Credit Card, 2 - Customer, 3 - Employee, 4 - Expense, 5 - Feed, 6 - Invoice, 7 - Parcel, 8 - Product, 9 - CowQuantity, 10 - ProductQuantity
    Date fileD[11];
    Time fileT[11];
} FilesTime;

typedef struct {
    int id;
    Date date;
    Time time;
    float amount;
} IncomeStruct;

typedef struct {
    int productID;
    char productName[30];
    float quantity;
    float unitPrice;
    float price;
} InvoiceList;

typedef struct
{
    int quantity;
    char name[30];
} Items;

typedef struct {
    int id;
    Date date;
    Time time;
    float quantity;
} ProductionLog;

typedef struct {
    InvoiceList invoiceData;
    Date date;
    Time time;
} ProductSoldList;

bool operator== (const Time time1, const Time time2) {
    if (time1.hours == time2.hours) {
        if (time1.minutes == time2.minutes) {
            if (time1.seconds == time2.seconds) {
                return true;
            }
        }
    }

    return false;
}

bool operator== (const Date date1, const Date date2) {
    if (date1.date == date2.date) {
        if (date1.month == date2.month) {
            if (date1.year == date2.year) {
                return true;
            }
        }
    }

    return false;
}

time_t now = time(0);
tm *localTimeNow = localtime(&now);

string AccountsReportLoc = "../Files/AccountsReportData.txt";
string AccountsReportFileLoc = "../Files/Accounts Report.txt";
string CowFileLoc = "../Files/CowData.txt";
string CowQuantityFileLoc = "../Files/CowQuantityData.txt";
string CowReportLoc = "../Files/CowReportData.txt";
string CowReportFileLoc = "../Files/Cow Report.txt";
string CreditCardFileLoc = "../Files/CreditCardData.txt";
string CustomerFileLoc = "../Files/CustomerData.txt";
string CustomerReportLoc = "../Files/CustomerReportData.txt";
string CustomerReportFileLoc = "../Files/Customer Report.txt";
string EmployeeFileLoc = "../Files/EmployeeData.txt";
string ExpenseFileLoc = "../Files/ExpenseData.txt";
string FeedFileLoc = "../Files/FeedData.txt";
string InvoiceFileLoc = "../Files/InvoiceData.txt";
string ParcelFileLoc = "../Files/ParcelData.txt";
string ProductFileLoc = "../Files/ProductData.txt";
string ProductQuantityFileLoc = "../Files/ProductQuantityData.txt";
string ProductReportLoc = "../Files/ProductReportData.txt";
string ProductReportFileLoc = "../Files/Product Report.txt";
string FileTimeLoc = "../Files/FilesData.txt";

class Report {
    protected:
        Date lastUpdatedDate;
        Time lastUpdatedTime;

    public:
        Report();
        ~Report();
        virtual bool verifyUpdatedDateTime() = 0;
        virtual int printReport() = 0;
        virtual int add() = 0;
        virtual int read() = 0;
};

class AccountsReport : protected Report {
    private:
        IncomeStruct incomeLog[150];
        ExpenseStruct expenseLog[150];
        float profit;

    public:
        AccountsReport();
        ~AccountsReport();
        bool verifyUpdatedDateTime();
        int printReport();
        int add();
        int read();
        friend int gatherAccountsData(AccountsReport &obj);
};

class CowReport : protected Report {
    private:
        ProductionLog productionData[150];
        int cowID;

    public:
        CowReport();
        CowReport(const int cowID);
        ~CowReport();
        bool verifyUpdatedDateTime();
        int printReport();
        int add();
        int read();
        int gatherData();
};

class CustomerReport : protected Report {
    private:
        CustomerData data[150];
        float totalPayable;

    public:
        CustomerReport();
        ~CustomerReport();
        bool verifyUpdatedDateTime();
        int printReport();
        int add();
        int read();
        friend int gatherCustomerData(CustomerReport &obj, const int customerID);
};

class ProductReport : protected Report {
    private:
        ProductionLog productionData[150];
        ProductSoldList invoiceData[150];
        float quantityAvailable;
        float quantitySold;
    
    public:
        ProductReport();
        ~ProductReport();
        bool verifyUpdatedDateTime();
        int printReport();
        int add();
        int read();
        friend int gatherProductData(ProductReport &obj, const int productID);
};

class Ui {
    public:
        Ui();
        virtual ~Ui();
        virtual void inputInfo() = 0;
        virtual void displayInfo() = 0;
        virtual bool modifyInfo() = 0;
        virtual int add() = 0;        
        virtual int searchID(const int id) = 0;
};

class Id : public Ui {
    protected:
        int id;

    public:
        Id();        
        ~Id();
        void assignID();        
        void displayInfo();
};

class LivingThing : public Id {
    protected:        
        char gender;
        Date dateOfBirth;

    public:
        LivingThing();                    
        ~LivingThing();
        void inputInfo(const char check);
        void displayInfo();       
};

class Cow : protected LivingThing {
    private:
        float weight;
        char breed[30];
        float averageMilkProduction;
        char status;        
       
    public:
        Cow();
        ~Cow();
        int getID();                
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int feedCow();
        int updateProductionLog();
        friend int updateCowData(const Cow &obj);
        friend bool verifyCowID(const int id);
};

class Person : public LivingThing {
    private:
        char password[30];

    protected:
        char name[30];
        char emailAddress[30];
        Address completeAddress;
        unsigned long int contactNumber;
        char username[30];

    public:
        Person();
        ~Person();
        int getID();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();        
        bool verifyPassword(const string password);    
        virtual int searchUsername(const string username) = 0;
        virtual int searchEmail(const string email) = 0;
        virtual int searchConatctNumber(const unsigned long int contactNumber) = 0;
        virtual int login() = 0;
};

class Customer : protected Person {
    private:
        char customerType;
        float totalPayable;
    
    public:
        Customer();
        ~Customer();
        int getID();
        float getTotalPayable();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int searchUsername(const string username);
        int searchEmail(const string email);
        int searchConatctNumber(const unsigned long int contactNumber);
        int login();
        int payInvoice();
        int generateInvoice();
        void updatePayable(const float amount);
        friend bool checkCustomerEmail(const string email);
        friend bool checkCustomerUsername(const string username);
        friend bool checkCustomerContactNumber(const unsigned long int contactNumber);
        friend int customerInterface();
        friend int updateCustomerData(const Customer &obj);
        friend bool verifyCustomerID(const int id);
};

class Employee : protected Person {
    private:
        // 0 - Admin, 1 - Cow, 2 - Customer, 3 - Invoice, 4 - Parcel, 5 - Product, 6 - Expense, 7 - Report
        bool accessControl[8];
        float salary;
        char designation[30];

    public:
        Employee();
        ~Employee();
        int getID();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int searchUsername(const string customerUsername);
        int searchEmail(const string customerEmail);
        int searchConatctNumber(const unsigned long int customerContactNumber);
        int login();
        friend bool checkEmployeeEmail(const string email);
        friend bool checkEmployeeUsername(const string username);
        friend bool checkEmployeeContactNumber(const unsigned long int contactNumber);
        friend int employeeInterface();
        friend int updateEmployeeData(const Employee &obj);
        friend bool verifyEmployeeID(const int id);
};

class CreditCard : protected Id
{
    unsigned long int cardNumber;
    Date dateOfIssue;
    Date expiryDate;
    char cardHolderName[30];
    int cvc;

    public:
    CreditCard();
    ~CreditCard();
    int getID();
    void inputInfo();
    void displayInfo();
    bool modifyInfo();
    int add();
    int searchID(const int id);
    int searchCardNumber(const unsigned long int cardNumber);
    bool verifyCard(const Date expiry, const int cvc);
    int customerInputInfo();
    friend bool verifyCreditCardID(const int id);
};

class Expense : protected Id {
    private:
        char name[30];
        char description[30];
        Date expenseDate;
        float subAmount;
        float tax;
        float totalAmount;

    public:
        Expense();
        ~Expense();
        int getID();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        void calculation();
        friend int gatherAccountsData(AccountsReport &obj);
        friend int updateExpenseData(const Expense &obj);
        friend bool verifyExpenseID(const int id);
};

class Feed : protected Id {
    Date feedingDate;
    int cowID;
    float quantity;
    Time feedingTime;

    public:
        Feed();        
        Feed(const int id);
        Feed(const int id, const float quantity);
        ~Feed();
        int getID();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        friend int updateFeedData(const Feed &obj);
        friend bool verifyFeedID(const int id);
};

class Invoice : protected Id {
    private:
        int customerID;
        Date invoiceDate;
        Time invoiceTime;
        InvoiceList productsList[10];
        float subTotal;
        float tax;
        float total;
        float amountPaid;
        float amountToBePaid;

    public:
        Invoice();
        Invoice(const int id);
        ~Invoice();
        int getID();
        float getAmountToBePaid();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int searchCustomerID(const int id);
        int calculations();
        int generateParcel();
        void displayInvoice();
        void displayProductList();
        void payUpdate(const float amount);
        friend float purchaseItems(const int customerID);
        friend int gatherCustomerData(CustomerReport &obj, const int customerID);
        friend int gatherProductData(ProductReport &obj, const int productID);
        friend int gatherAccountsData(AccountsReport &obj);
        friend int updateInvoiceData(const Invoice &obj);
        friend bool verifyInvoiceID(const int id);
};

class Parcel : protected Id
{
    int invoiceID;
    int customerID;
    int status;

    public:
        Parcel();
        Parcel(const int invoiceId, const int customerId);
        ~Parcel();
        int getID();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int searchCustomerID(const int customerID);
        void displayParcel();
        friend int customerNotification(const int id);
        friend int updateParcelData(const Parcel &obj);
        friend bool verifyParcelID(const int id);
};

class Product : protected Id {
    private:
        char name[30];
        char description[50];
        float quantityAvailable;
        float quantitySold;
        float price;
        char status;

    public:
        Product();        
        ~Product();
        int getID();
        char getStatus();
        void inputInfo();
        void displayInfo();
        bool modifyInfo();
        int add();
        int searchID(const int id);
        int searchName(const string name);
        int addProduct(const float QuantityToBeAdded);
        void displayProduct();
        int displayProductList();
        int updateProductionLog(const float quantity);
        friend int productNotification();
        friend float purchaseItems(const int customerID);
        friend int gatherProductData(ProductReport &obj, const int productID);
        friend int updateProductData(const Product &obj);
        friend bool verifyProductID(const int id);
};

bool contactNumberVerification(unsigned long int number);
int customerInterface();
bool dateVerification (const int day, const int month, const int year, const char type);
bool dobVerification (const int day, const int month, const int year, const char condition);
int employeeInterface();
bool emailAddressVerification(const std::string email);
int fileTimeUpdate(const int indicator);
int numberOfRecords(std::fstream& ptr, int classSize);
bool passwordVerification(const std::string pass);

Report :: Report() {
    lastUpdatedDate.date = localTimeNow->tm_mday;
    lastUpdatedDate.month = localTimeNow->tm_mon + 1;
    lastUpdatedDate.year = localTimeNow->tm_year + 1900;
    lastUpdatedTime.hours = localTimeNow->tm_hour;
    lastUpdatedTime.minutes = localTimeNow->tm_min;
    lastUpdatedTime.seconds = localTimeNow->tm_sec;
}

Report :: ~Report() {
    
}

AccountsReport :: AccountsReport() {
    int counter;

    for (counter = 0; counter < 150; counter++) {
        incomeLog[counter].id = 0;
        expenseLog[counter].id = 0;
        fill_n(expenseLog[counter].name, 30, '\0');
        fill_n(expenseLog[counter].description, 30, '\0');
    }
        
    profit = 0.0;
}

AccountsReport :: ~AccountsReport() {
    
}

bool AccountsReport :: verifyUpdatedDateTime() {
    fstream file;
    FilesTime data;
    bool expense = false, invoice = false;

    file.open(FileTimeLoc, ios::binary | ios::in);

    if (!file) {
        return false;
    }

    file.read((char*)&data, sizeof(FilesTime));
    file.close();

    if (lastUpdatedTime == data.fileT[4]) {
        if (lastUpdatedDate == data.fileD[4]) {
            expense = true;
        }
    }

    if (lastUpdatedTime == data.fileT[6]) {
        if (lastUpdatedDate == data.fileD[6]) {
            invoice = true;
        }
    }

    if (expense == true && invoice == true) {
        return true;
    }
    else {
        return false;
    }
    
}

int AccountsReport :: printReport() {
    int counter;
    fstream AccountsReportFile;

    AccountsReportFile.open(AccountsReportFileLoc , ios::out | ios::trunc);

    if(!AccountsReportFile)
    {
        return 404;
    }

    AccountsReportFile << "Income details:";
    AccountsReportFile << "Income ID - Income Date - Income Time - Income Amount" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(incomeLog[counter].id != 0)
        {
            AccountsReportFile << incomeLog[counter].id << " - " << incomeLog[counter].date.date << "/" << incomeLog[counter].date.month << "/" << incomeLog[counter].date.year << " - " << incomeLog[counter].time.hours << ":" << incomeLog[counter].time.minutes << ":" << incomeLog[counter].time.seconds << " - " << incomeLog[counter].amount << endl;
        }
    }

    AccountsReportFile << "Expenses details: ";
    AccountsReportFile << "Expense ID - Expense Date - Expense Amount - Expense Name - Expense Description" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(expenseLog[counter].id != 0)
        {
            AccountsReportFile << expenseLog[counter].id << " - " << expenseLog[counter].date.date << "/" << expenseLog[counter].date.month << "/" << expenseLog[counter].date.year << " - " << expenseLog[counter].amount << " - " << expenseLog[counter].name << " - " << expenseLog[counter].description << endl;
        }
    }

    AccountsReportFile << "Profit: " << profit << endl;

    AccountsReportFile.close();

    return 1;
}

int AccountsReport :: add() {
    fstream file;

    file.open(AccountsReportLoc, ios::binary | ios::out | ios::trunc);
    
    if (!file) {
        return 404;
    }

    file.write((char*)this, sizeof(AccountsReport));
    file.close();
    return 1;
}

int AccountsReport :: read() {
    fstream file;

    file.open(AccountsReportLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    file.read((char*)this, sizeof(AccountsReport));
    file.close();
    return 1;
}

int gatherAccountsData(AccountsReport &obj) {
    fstream file;
    Invoice invoiceObj;
    Expense expenseObj;
    int fileSize, counter;
    float sum = 0;

    file.open(InvoiceFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(Invoice));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&invoiceObj, sizeof(Invoice));
        obj.incomeLog[counter].id = invoiceObj.id;
        obj.incomeLog[counter].date = invoiceObj.invoiceDate;
        obj.incomeLog[counter].time = invoiceObj.invoiceTime;
        obj.incomeLog[counter].amount = invoiceObj.total;
        sum += obj.incomeLog[counter].amount;
    }

    obj.profit += sum;
    file.close();

    file.open(ExpenseFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(Expense));

    sum = 0;
    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&expenseObj, sizeof(Expense));
        obj.expenseLog[counter].id = expenseObj.id;
        obj.expenseLog[counter].date = expenseObj.expenseDate;
        strcpy(obj.expenseLog[counter].name, expenseObj.name);
        strcpy(obj.expenseLog[counter].description, expenseObj.description);
        obj.expenseLog[counter].amount = expenseObj.totalAmount;
        sum += obj.expenseLog[counter].amount;
    }

    obj.profit -= sum;
    file.close();

    return 1;
}

CowReport :: CowReport() {
    int counter;

    for (counter = 0; counter < 150; counter++) {
        productionData[counter].id = 0;
    }

    this->cowID = 0;
}

CowReport :: CowReport(const int cowID) {
    int counter;

    for (counter = 0; counter < 150; counter++) {
        productionData[counter].id = 0;
    }
    
    this->cowID = cowID;
}

CowReport :: ~CowReport() {
    
}

bool CowReport :: verifyUpdatedDateTime() {
    fstream file;
    FilesTime data;
    bool cow = false, cowQuantity = false;

    file.open(FileTimeLoc, ios::binary | ios::in);

    if (!file) {
        return false;
    }

    file.read((char*)&data, sizeof(FilesTime));
    file.close();

    if (lastUpdatedTime == data.fileT[0]) {
        if (lastUpdatedDate == data.fileD[0]) {
            cow = true;
        }
    }

    if (lastUpdatedTime == data.fileT[9]) {
        if (lastUpdatedDate == data.fileD[9]) {
            cowQuantity = true;
        }
    }

    if (cow == true && cowQuantity == true) {
        return true;
    }
    else {
        return false;
    }
}

int CowReport :: printReport()
{
    int counter;
    fstream CowReportFile;

    CowReportFile.open(CowReportFileLoc , ios::out | ios::trunc);

    if(!CowReportFile)
    {
        return 404;
    }

    CowReportFile << "Cow ID - Production Date - Production Time - Quantity Produced" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(productionData[counter].id != 0)
        {
            CowReportFile << productionData[counter].id << " - " << productionData[counter].date.date << "/" << productionData[counter].date.month << "/" << productionData[counter].date.year << " - " << productionData[counter].time.hours << ":" << productionData[counter].time.minutes << ":" << productionData[counter].time.seconds << " - " << productionData[counter].quantity << endl;
        }
    }

    CowReportFile.close();

    return 1;
}

int CowReport :: add() {
    fstream file;

    file.open(CowReportLoc, ios::binary | ios::out | ios::trunc);
    
    if (!file) {
        return 404;
    }

    file.write((char*)this, sizeof(CowReport));
    file.close();
    return 1;
}

int CowReport :: read() {
    fstream file;

    file.open(CowReportLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    file.read((char*)this, sizeof(CowReport));
    file.close();
    return 1;
}

int CowReport :: gatherData() {
    fstream file;
    Cow cowObj;
    int res, fileSize, counter, recordCounter;
    ProductionLog tempData;
    
    res = cowObj.searchID(cowID);
    if (res != 1) {
        return res;
    }

    file.open(CowQuantityFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(ProductionLog));

    recordCounter = 0;
    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&tempData, sizeof(ProductionLog));

        if (cowID == tempData.id) {
            productionData[recordCounter] = tempData;
            recordCounter++;
        }
    }

    file.close();
    return 1;
}

CustomerReport :: CustomerReport() {
    int counter;

    for (counter = 0; counter < 150; counter++) {
        data[counter].invoiceID = 0;
        data[counter].invoiceDate.date = 0;
        data[counter].invoiceDate.month = 0;
        data[counter].invoiceDate.year = 0;
        data[counter].invoiceTime.hours = 0;
        data[counter].invoiceTime.minutes = 0;
        data[counter].invoiceTime.seconds = 0;        
        data[counter].amount = 0.0;
        data[counter].amountToBePaid = 0.0;
    }
    totalPayable = 0.0;
}

CustomerReport :: ~CustomerReport() 
{

}

bool CustomerReport :: verifyUpdatedDateTime() {
    fstream file;
    FilesTime data;
    bool customer = false, invoice = false;

    file.open(FileTimeLoc, ios::binary | ios::in);

    if (!file) {
        return false;
    }

    file.read((char*)&data, sizeof(FilesTime));
    file.close();

    if (lastUpdatedTime == data.fileT[2]) {
        if (lastUpdatedDate == data.fileD[2]) {
            customer = true;
        }
    }
    
    if (lastUpdatedTime == data.fileT[6]) {
        if (lastUpdatedDate == data.fileD[6]) {
            invoice = true;
        }
    }

    if (customer == true && invoice == true) {
        return true;
    }
    else {
        return false;
    }
}

int CustomerReport :: printReport() 
{
    int counter;
    fstream CustomerReportFile;

    CustomerReportFile.open(CustomerReportFileLoc , ios::out | ios::trunc);

    if(!CustomerReportFile)
    {
        return 404;
    }

    CustomerReportFile << "Invoice ID - Invoice Date - Invoice Time - Amount - AmountToBePaid" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(data[counter].invoiceID != 0)
        {
            CustomerReportFile << data[counter].invoiceID << " - " << data[counter].invoiceDate.date << "/" << data[counter].invoiceDate.month << "/" << data[counter].invoiceDate.year << " - " << data[counter].invoiceTime.hours << ":" << data[counter].invoiceTime.minutes << ":" << data[counter].invoiceTime.seconds << " - " << data[counter].amount << " - " << data[counter].amountToBePaid << endl;
        }
    }

    CustomerReportFile.close();

    return 1;
}

int CustomerReport :: add() {
    fstream file;

    file.open(CustomerReportLoc, ios::binary | ios::out | ios::trunc);
    
    if (!file) {
        return 404;
    }

    file.write((char*)this, sizeof(CustomerReport));
    file.close();
    return 1;
}

int CustomerReport :: read() {
    fstream file;

    file.open(CustomerReportLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    file.read((char*)this, sizeof(CustomerReport));
    file.close();
    return 1;
}

int gatherCustomerData(CustomerReport &obj, const int customerID) {
    int fileSize, counter, recordCounter, res;
    fstream file;    
    Invoice invoiceObj;
    Customer customerObj;

    res = customerObj.searchID(customerID);

    if (res != 1) {
        return res;
    }

    obj.totalPayable = customerObj.getTotalPayable();

    file.open(InvoiceFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(Invoice));

    recordCounter = 0;
    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&invoiceObj, sizeof(Invoice));

        if (invoiceObj.customerID == customerID) {
            obj.data[recordCounter].invoiceID = invoiceObj.id;
            obj.data[recordCounter].invoiceDate = invoiceObj.invoiceDate;
            obj.data[recordCounter].invoiceTime = invoiceObj.invoiceTime;
            obj.data[recordCounter].amount = invoiceObj.total;
            obj.data[recordCounter].amountToBePaid = invoiceObj.amountToBePaid;
            recordCounter++;
        }
    }

    file.close();
    return 1;
}

ProductReport :: ProductReport() {
    int counter;

    for (counter = 0; counter < 150; counter++) {
        productionData[counter].id = 0;
        invoiceData[counter].invoiceData.productID = 0;
        fill_n(invoiceData[counter].invoiceData.productName, 30, '\0');
    }
}

ProductReport :: ~ProductReport() {
    
}

bool ProductReport :: verifyUpdatedDateTime() {
    fstream file;
    FilesTime data;
    bool product = false, productQuantity = false, invoice = false;

    file.open(FileTimeLoc, ios::binary | ios::in);

    if (!file) {
        return false;
    }

    file.read((char*)&data, sizeof(FilesTime));
    file.close();

    if (lastUpdatedTime == data.fileT[8]) {
        if (lastUpdatedDate == data.fileD[8]) {
            product = true;
        }
    }

    if (lastUpdatedTime == data.fileT[10]) {
        if (lastUpdatedDate == data.fileD[10]) {
            productQuantity = true;
        }
    }

    if (lastUpdatedTime == data.fileT[6]) {
        if (lastUpdatedDate == data.fileD[6]) {
            invoice = true;
        }
    }

    if (product == true && productQuantity == true && invoice == true) {
        return true;
    }
    else {
        return false;
    }
    
}

int ProductReport :: printReport() {
    int counter;
    fstream ProductReportFile;

    ProductReportFile.open(ProductReportFileLoc , ios::out | ios::trunc);

    if(!ProductReportFile)
    {
        return 404;
    }

    ProductReportFile << "Product production" << endl;
    ProductReportFile << "Product ID - Production Date - Production Time - Produced Quantity" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(productionData[counter].id != 0)
        {
            ProductReportFile << productionData[counter].id << " - " << productionData[counter].date.date << "/" << productionData[counter].date.month << "/" << productionData[counter].date.year << " - " << productionData[counter].time.hours << ":" << productionData[counter].time.minutes << ":" << productionData[counter].time.seconds << " - " << productionData[counter].quantity << endl;
        }
    }

    ProductReportFile << "Product sells" << endl;
    ProductReportFile << "Product ID - Product Name - Product Quantity - Unit Price - Total Price - Sell Date - Sell Time" << endl;
    for(counter=0; counter<150; counter++)
    {
        if(invoiceData[counter].invoiceData.productID != 0)
        {
            ProductReportFile << invoiceData[counter].invoiceData.productID << "-" << invoiceData[counter].invoiceData.productName << "-" << invoiceData[counter].invoiceData.quantity << "-" << invoiceData[counter].invoiceData.unitPrice << "-" << invoiceData[counter].invoiceData.price << " - " << invoiceData[counter].date.date << "/" << invoiceData[counter].date.month << "/" << invoiceData[counter].date.year << " - " << invoiceData[counter].time.hours << ":" << invoiceData[counter].time.minutes << ":" << invoiceData[counter].time.seconds << endl;
        }
    }
    
    ProductReportFile << "Quantity Available: " << quantityAvailable << endl;
    ProductReportFile << "Quantity sold: " << quantitySold << endl;

    ProductReportFile.close();

    return 1;
}

int ProductReport :: add() {
    fstream file;

    file.open(ProductReportLoc, ios::binary | ios::out | ios::trunc);
    
    if (!file) {
        return 404;
    }

    file.write((char*)this, sizeof(ProductReport));
    file.close();
    return 1;
}

int ProductReport :: read() {
    fstream file;

    file.open(ProductReportLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    file.read((char*)this, sizeof(ProductReport));
    file.close();
    return 1;
}

int gatherProductData(ProductReport &obj, const int productID) {
    fstream file;
    int counter, counter2, recordCounter, fileSize, res;
    Invoice invoiceObj;
    Product productObj;
    ProductionLog tempData;

    res = productObj.searchID(productID);
    if (res != 1) {
        return res;
    }

    obj.quantityAvailable = productObj.quantityAvailable;
    obj.quantitySold = productObj.quantitySold;

    file.open(InvoiceFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(Invoice));

    recordCounter = 0;
    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&invoiceObj, sizeof(Invoice));

        for (counter2 = 0; counter2 < 10; counter2++) {
            if (invoiceObj.productsList[counter2].productID == productID) {
                obj.invoiceData[recordCounter].invoiceData = invoiceObj.productsList[counter2];
                obj.invoiceData[recordCounter].date = invoiceObj.invoiceDate;
                obj.invoiceData[recordCounter].time = invoiceObj.invoiceTime;
                recordCounter++;
            }
        }
    }

    file.close();

    file.open(ProductQuantityFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(ProductionLog));

    recordCounter = 0;
    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&tempData, sizeof(ProductionLog));

        if (tempData.id == productID) {
            obj.productionData[recordCounter] = tempData;
            recordCounter++;
        }
    }

    file.close();
    return 1;
}

Ui :: Ui() {

}

Ui :: ~Ui() {

}

Id :: Id() {
    id = 0;
}

Id :: ~Id() {
    
}

void Id :: assignID() {
    srand(time(0));

    id = rand() % 99999;
}

void Id :: displayInfo() {
    cout << "ID: " << id << endl;
}

LivingThing :: LivingThing() {
    dateOfBirth.date = 0;
    dateOfBirth.month = 0;
    dateOfBirth.year = 0;
    gender = 'u';
}

LivingThing :: ~LivingThing() {

}

void LivingThing :: inputInfo(const char check) {
    cout << "Enter gender (Male or Female): ";
    cin >> gender;
    fflush(stdin);
    while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
        cout << "Incorrect option entered!" << endl;
        cout << "Enter gender again (Male or Female): ";
        cin >> gender;
        fflush(stdin);
    }

    if (gender == 'm') {
        gender = 'M';
    }
    else if (gender == 'f') {
        gender = 'F';
    }

    cout << endl;

    cout << "Enter birth day: ";
    cin >> dateOfBirth.date;
    fflush(stdin);

    cout << "Enter birth month: ";
    cin >> dateOfBirth.month;
    fflush(stdin);

    cout << "Enter birth year: ";
    cin >> dateOfBirth.year;
    fflush(stdin);

    while (!dobVerification(dateOfBirth.date, dateOfBirth.month, dateOfBirth.year, check)) {
        cout << "Incorrect date entered!" << endl;

        cout << "Enter birth day: ";
        cin >> dateOfBirth.date;
        fflush(stdin);

        cout << "Enter birth month: ";
        cin >> dateOfBirth.month;
        fflush(stdin);

        cout << "Enter birth year: ";
        cin >> dateOfBirth.year;
        fflush(stdin);
    }

    cout << endl;
}

void LivingThing :: displayInfo() {
    string tempString;
            
    if (gender == 'M') {
        tempString = "Male";
    }
    else {
        tempString = "Female";
    }
    Id :: displayInfo();
    cout << "Gender: " << tempString << endl;
    cout << "Date of Birth: " << dateOfBirth.date << "/" << dateOfBirth.month << "/" << dateOfBirth.year << endl;
}

int updateCowData(const Cow &obj) {
    fstream file;
    Cow object;
    int location, res;

    res = fileTimeUpdate(0);
    if (res == 404) {
        return 404;
    }

    file.open(CowFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Cow));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(CowFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Cow);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Cow));

    file.close();

    return 1;
}

bool verifyCowID(const int id) {
    Cow object;
    fstream file;
    int fileSize, counter;

    file.open(CowFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Cow));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Cow));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Cow :: Cow() {
    weight = 0.0;
    fill_n(breed, 30, '\0');
    averageMilkProduction = 0.0;
    status = 'u';
}

Cow :: ~Cow() {

}

int Cow :: getID() {
    return id;
}

void Cow :: inputInfo() {
    do {
        assignID();
    } while (!verifyCowID(id));

    int response;
    string tempString;

    cout << "Enter cow weight: ";
    cin >> weight;
    fflush(stdin);
    while (weight <= 0) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter cow weight again: ";
        cin >> weight;
        fflush(stdin);
    }

    cout << endl;

    LivingThing :: inputInfo('C');

    cout << "Enter cow breed: ";
    getline(cin, tempString);            
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be empty!" << endl;
        cout << "Enter cow breed again: ";
        getline(cin, tempString);            
        fflush(stdin);
    }
    
    strcpy(breed, tempString.c_str());
    cout << endl;

    cout << "Enter cow status (Available, Sold, Death): ";
    cin >> status;
    fflush(stdin);
    while (status != 'A' && status != 'a' && status != 'S' && status != 's' && status != 'D' && status != 'd') {
        cout << "Incorrect option entered!" << endl;
        cout << "Enter cow status again (Available, Sold, Death): ";
        cin >> status;
        fflush(stdin);
    }

    if (status == 'a') {
        status = 'A';
    }
    else if (status == 's') {
        status = 'S';
    }
    else if (status == 'd') {
        status = 'D';
    }

    system("cls");
}

void Cow :: displayInfo() {    
    cout << "Cow Information:" << endl;
    cout << "ID: " << id << endl;
    cout << "Weight: " << weight << endl;
    LivingThing :: displayInfo();
    cout << "Breed: " << breed << endl;
    cout << "Status: " << status << endl;
}

bool Cow :: modifyInfo() {
    int userOption;
    bool update = false;

    while (1) {
        cout << "Enter 1 to update cow weight" << endl;
        cout << "Enter 2 to update cow status" << endl;
        cout << "Enter 3 to go back" << endl;
        cout << "Enter desired option: ";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1) {
            cout << "Enter cow weight: ";
            cin >> weight;
            fflush(stdin);
            while (weight <= 0) {
                cout << "Incorrect value entered!" << endl;
                cout << "Enter cow weight again: ";
                cin >> weight;
                fflush(stdin);
            }
            update = true;
        }
        else if (userOption == 2) {
            cout << "Enter cow status (Available, Sold, Death): ";
            cin >> status;
            fflush(stdin);
            while (status != 'A' && status != 'a' && status != 'S' && status != 's' && status != 'D' && status != 'd') {
                cout << "Incorrect option entered!" << endl;
                cout << "Enter cow status again (Available, Sold, Death): ";
                cin >> status;
                fflush(stdin);
            }

            if (status == 'a') {
                status = 'A';
            }
            else if (status == 's') {
                status = 'S';
            }
            else if (status == 'd') {
                status = 'D';
            }
            update = true;
        }
        else if (userOption == 3) {
            return update;
        }
        else {
            cout << endl << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }
}
        
int Cow :: add() {
    int res;
    fstream file; 

    res = fileTimeUpdate(0);
    if (res != 1) {
        return res;
    }

    file.open(CowFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(CowFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(CowFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Cow));
    file.close();
    return 1;
}

int Cow :: searchID(const int id) {
    fstream cowFile;
    int counter, fileSize;

    cowFile.open(CowFileLoc, ios::binary | ios::in);
    
    if (!cowFile) {
        return 404;
    }

    fileSize = numberOfRecords(cowFile, sizeof(Cow));

    for (counter = 0; counter < fileSize; counter++) {
        cowFile.read((char*)this, sizeof(Cow));

        if (this->id == id) {
            cowFile.close();
            return 1;
        }
    }

    cowFile.close();
    return 0;
}

int Cow :: feedCow() {
    char userOption;

    Feed feedObj(id);
    feedObj.inputInfo();
    feedObj.displayInfo();
    cout << "Is the info correct?" << endl;
    cout << "Yes or No: ";
    cin >> userOption;

    if (userOption == 'Y' || userOption == 'y') {
        feedObj.add();
        return 1;
    }
    else {
        return 2;
    }            
    
    return 0;
}

int Cow :: updateProductionLog() {
    fstream cowFile;    
    ProductionLog data;
    Product productObj;
    int res;

    res = fileTimeUpdate(9);
    if (res == 404) {
        return 404;
    }

    data.id = id;
    data.date.date = localTimeNow->tm_mday;
    data.date.month = localTimeNow->tm_mon + 1;
    data.date.year = localTimeNow->tm_year + 1900;
    data.time.hours = localTimeNow->tm_hour;
    data.time.minutes = localTimeNow->tm_min;
    data.time.seconds = localTimeNow->tm_sec;

    cout << "Enter quantity of milk produced by " << id << " : ";
    cin >> data.quantity;
    fflush(stdin);
    while (data.quantity <= 0) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter quantity of milk again produced by " << id << " : ";
        cin >> data.quantity;
        fflush(stdin);
    }

    res = productObj.searchName("Milk");
    if (res != 1) {
        return res;
    }

    productObj.addProduct(data.quantity);

    cowFile.open(CowQuantityFileLoc, ios::binary | ios::app);

    if (!cowFile) {
        cowFile.open(CowQuantityFileLoc, ios::binary | ios::trunc | ios::out);

        if (!cowFile) {
            return 404;
        }

        cowFile.close();
        cowFile.open(CowQuantityFileLoc, ios::binary | ios::app);

        if (!cowFile) {
            return 404;
        }
    }

    cowFile.seekg(0, ios::end);
    cowFile.write((char*)&data, sizeof(ProductionLog));
    cowFile.close();
    return 1;
}

Person :: Person() {
    int counter;

    for (counter = 0; counter < 30; counter++) {
        name[counter] = '\0';
        emailAddress[counter] = '\0';
        completeAddress.address[counter] = '\0';
        completeAddress.province[counter] = '\0';
        completeAddress.area[counter] = '\0';
        completeAddress.city[counter] = '\0';
        completeAddress.country[counter] = '\0';
        username[counter] = '\0';
        password[counter] = '\0';
    }
    contactNumber = 0;
    strcpy(completeAddress.country, "Pakistan");
}

Person :: ~Person() {}

int Person :: getID() {
    return id;
}

void Person :: inputInfo() {
    string tempString;

    cout << "Enter name: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Name field cannot be left empty!" << endl;
        cout << "Enter name again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(name, tempString.c_str());
    cout << endl;

    cout << "Enter email address: ";
    getline(cin, tempString);
    fflush(stdin);
    while (!emailAddressVerification(tempString)) {
        cout << "Email Address entered is not correct!" << endl;
        cout << "Enter email address again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(emailAddress, tempString.c_str());
    cout << endl;

    cout << "Complete Address Details" << endl;
    cout << "Enter basic address: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be left empty!" << endl;
        cout << "Enter basic address again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(completeAddress.address, tempString.c_str());

    cout << "Enter area: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be left empty!" << endl;
        cout << "Enter area again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(completeAddress.area, tempString.c_str());

    cout << "Enter city: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be left empty!" << endl;
        cout << "Enter city again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(completeAddress.city, tempString.c_str());

    cout << "Enter province: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be left empty!" << endl;
        cout << "Enter area again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(completeAddress.province, tempString.c_str());

    cout << "Country: Pakistan" << endl << endl;

    LivingThing :: inputInfo('P');

    cout << "Enter username: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Username field cannot be left empty!" << endl;
        cout << "Enter username again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(username, tempString.c_str());
    cout << endl;

    cout << "Enter password: ";
    getline(cin, tempString);
    fflush(stdin);
    while (!passwordVerification(tempString)) {
        cout << "Please revise the password!" << endl;
        cout << "Enter password again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(password, tempString.c_str()); 
    cout << endl;
}

void Person :: displayInfo() {
    cout << "Name: " << name << endl;
    cout << "Email Address: " << emailAddress << endl;
    cout << "Address: " << completeAddress.address << ", " << completeAddress.area << ", " << completeAddress.city << ", " << completeAddress.province << ", " << completeAddress.country << endl;
    cout << "Username: " << username << endl;
    LivingThing :: displayInfo();
}

bool Person :: modifyInfo() {
    int userOption, counter;
    string tempString;
    bool update = false;
    
    while (1) {        
        cout << "Enter 1 to update email address" << endl;
        cout << "Enter 2 to update address" << endl;
        cout << "Enter 3 to update username" << endl;
        cout << "Enter 4 to update passowrd" << endl;
        cout << "Enter 5 to go back" << endl;
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1) {
            cout << "Enter email address: ";
            getline(cin, tempString);
            fflush(stdin);
            while (!emailAddressVerification(tempString)) {
                cout << "Email Address entered is not correct!" << endl;
                cout << "Enter email address again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            for (counter = 0; counter < 30; counter++) {
                emailAddress[counter] = '\0';
            }
            strcpy(emailAddress, tempString.c_str());
            update = true;
        }
        else if (userOption == 2) {
            for (counter = 0; counter < 30; counter++) {                
                completeAddress.address[counter] = '\0';
                completeAddress.province[counter] = '\0';
                completeAddress.area[counter] = '\0';
                completeAddress.city[counter] = '\0';
                completeAddress.country[counter] = '\0';                
            }

            cout << "Complete Address Details" << endl;
            cout << "Enter basic address: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0) {
                cout << "Field cannot be left empty!" << endl;
                cout << "Enter basic address again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(completeAddress.address, tempString.c_str());

            cout << "Enter area: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0) {
                cout << "Field cannot be left empty!" << endl;
                cout << "Enter area again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(completeAddress.area, tempString.c_str());

            cout << "Enter city: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0) {
                cout << "Field cannot be left empty!" << endl;
                cout << "Enter city again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(completeAddress.city, tempString.c_str());

            cout << "Enter province: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0) {
                cout << "Field cannot be left empty!" << endl;
                cout << "Enter area again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(completeAddress.province, tempString.c_str());

            cout << "Country: Pakistan" << endl;
            update = true;
        }
        else if (userOption == 3) {
            cout << "Enter username: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0) {
                cout << "Username field cannot be left empty!" << endl;
                cout << "Enter username again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            for (counter = 0; counter < 30; counter++) {
                username[counter] = '\0';
            }

            strcpy(username, tempString.c_str());
            update = true;
        }
        else if (userOption == 4) {
            cout << "Enter old password: ";
            getline(cin, tempString);
            fflush(stdin);
            while (!verifyPassword(tempString)) {
                cout << "Incorrect password entered!";
                cout << "Enter old password again or enter 1 to go back: ";
                getline(cin, tempString);
                fflush(stdin);

                if (tempString == "1") {
                    return update;
                }
            }

            for (counter = 0; counter < 30; counter++) {
                password[counter] = '\0';
            }

            cout << "Enter password: ";
            getline(cin, tempString);
            fflush(stdin);
            while (!passwordVerification(tempString)) {
                cout << "Please revise the password!" << endl;
                cout << "Enter password again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(password, tempString.c_str());
            update = true;
        }
        else if (userOption == 5) {
            return update;
        }
        else {
            cout << endl << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }
}

bool Person :: verifyPassword(const string customerPasword) {
    char temp[30];
    fill_n(temp, 30, '\0');
    strcpy(temp, customerPasword.c_str());

    if (strcmp(temp, this->password) == 0) {
        return true;
    }
    else {
        return false;
    }
}

int updateInvoiceData(const Invoice &obj) {
    fstream file;
    Invoice object;
    int location, res;

    res = fileTimeUpdate(6);
    if (res == 404) {
        return 404;
    }

    file.open(InvoiceFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Invoice));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(InvoiceFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Invoice);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Invoice));

    file.close();

    return 1;
}

bool verifyInvoiceID(const int id) {
    Invoice object;
    fstream file;
    int fileSize, counter;

    file.open(InvoiceFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Invoice));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Invoice));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Invoice :: Invoice() {
    int counter;

    this->customerID = 0;
    invoiceDate.date = localTimeNow->tm_mday;
    invoiceDate.month = localTimeNow->tm_mon + 1;
    invoiceDate.year = localTimeNow->tm_year + 1900;
    invoiceTime.hours = localTimeNow->tm_mday;
    invoiceTime.minutes = localTimeNow->tm_min;
    invoiceTime.seconds = localTimeNow->tm_sec;

    for (counter = 0; counter < 10; counter++) {
        productsList[counter].productID = 0;
        fill_n(productsList[counter].productName, 30, '\0');
        productsList[counter].quantity = 0.0;
        productsList[counter].unitPrice = 0.0;
        productsList[counter].price = 0.0;
    }

    subTotal = 0.0;
    tax = 0.0;
    total = 0.0;
    amountPaid = 0.0;
    amountToBePaid = 0.0;
}

Invoice :: Invoice(const int id) {
    int counter;

    this->customerID = id;
    invoiceDate.date = localTimeNow->tm_mday;
    invoiceDate.month = localTimeNow->tm_mon + 1;
    invoiceDate.year = localTimeNow->tm_year + 1900;
    invoiceTime.hours = localTimeNow->tm_mday;
    invoiceTime.minutes = localTimeNow->tm_min;
    invoiceTime.seconds = localTimeNow->tm_sec;

    for (counter = 0; counter < 10; counter++) {
        productsList[counter].productID = 0;
        fill_n(productsList[counter].productName, 30, '\0');
        productsList[counter].quantity = 0.0;
        productsList[counter].unitPrice = 0.0;
        productsList[counter].price = 0.0;
    }

    subTotal = 0.0;
    tax = 0.0;
    total = 0.0;
    amountPaid = 0.0;
    amountToBePaid = 0.0;
}

Invoice :: ~Invoice() {

}

int Invoice :: getID() {
    return id;
}

float Invoice :: getAmountToBePaid() {
    return amountToBePaid;
}

void Invoice :: inputInfo() {
    
}

void Invoice :: displayInfo() {
    int counter;
    
    cout << "Parcel Information:" << endl;
    Id :: displayInfo();
    cout << "Customer ID: " << customerID << endl;
    cout << "Invoice Date: " << invoiceDate.date << "/" << invoiceDate.month << "/" << invoiceDate.year << endl;
    cout << "Invoice Time: " << invoiceTime.hours << ":" << invoiceTime.minutes << ":" << invoiceTime.seconds << endl;
    cout << "Products: " << endl;
    for (counter = 0; counter < 10; counter++) {
        if (productsList[counter].productID != 0) {
            cout << "Product ID: " << productsList[counter].productID << endl;
            cout << "Product Name: " << productsList[counter].productName << endl;
            cout << "Quantity: " << productsList[counter].quantity << endl;
            cout << "Unit Price: $" << fixed << setprecision(2) << productsList[counter].unitPrice << endl;
            cout << "Price: $" << fixed << setprecision(2) << productsList[counter].price << endl;
            cout << endl << endl;
        }
    }
    cout << "Sub Total: $" << fixed << setprecision(2) << subTotal << endl;
    cout << "Tax: $" << fixed << setprecision(2) << tax << endl;
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
    cout << "Amount Paid: $" << fixed << setprecision(2) << amountPaid << endl;
    cout << "Amount to be Paid: $" << fixed << setprecision(2) << amountToBePaid << endl;
}

bool Invoice :: modifyInfo() {
    return false;
}

int Invoice :: add() {
    int res;
    fstream file;

    do {
        assignID();
    } while (!verifyInvoiceID(id));    

    res = fileTimeUpdate(6);
    if (res != 1) {
        return res;
    }

    file.open(InvoiceFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(InvoiceFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(InvoiceFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Invoice));
    file.close();
    return 1;
}

int Invoice :: searchID(const int id) {
    fstream invoiceFile;
    int counter, fileSize;

    invoiceFile.open(InvoiceFileLoc, ios::binary | ios::in);
    
    if (!invoiceFile) {
        return 404;
    }

    fileSize = numberOfRecords(invoiceFile, sizeof(Invoice));

    for (counter = 0; counter < fileSize; counter++) {
        invoiceFile.read((char*)this, sizeof(Invoice));

        if (this->id == id) {
            invoiceFile.close();
            return 1;
        }
    }

    invoiceFile.close();
    return 0;
}

int Invoice :: searchCustomerID(const int id) {
    fstream invoiceFile;
    int counter, fileSize;
    bool found = false;

    invoiceFile.open(InvoiceFileLoc, ios::binary | ios::in);
    
    if (!invoiceFile) {
        return 404;
    }

    fileSize = numberOfRecords(invoiceFile, sizeof(Invoice));

    for (counter = 0; counter < fileSize; counter++) {
        invoiceFile.read((char*)this, sizeof(Invoice));

        if (this->customerID == id) {
            if (!found) {
                cout << "Invoices List:" << endl;
                found = true;
            }
            displayInvoice();
        }
    }

    invoiceFile.close();

    if (found) {
        return 1;
    }
    else {
        return 0;
    }
}

int Invoice :: calculations() {
    int counter;
    
    for (counter = 0; counter < 10; counter++) {
        if (productsList[counter].productID != 0) {
            subTotal += productsList[counter].price;
        }
    }

    tax = subTotal * 0.13;
    total = subTotal + total;
    return 1;
}

int Invoice :: generateParcel() {
    Parcel parcelObj(id, customerID);
    int res;

    parcelObj.inputInfo();
    res = parcelObj.add();
    return res;
}

void Invoice :: displayInvoice() {
    cout << "ID: " << id << " - Date: " << invoiceDate.date << "/" << invoiceDate.month << "/" << invoiceDate.year << " - Total: $" << fixed << setprecision(2) << total << " - Amount To Be Paid: $" << fixed << setprecision(2) << amountToBePaid << endl;
}

void Invoice :: displayProductList() {
    int counter;
    bool header = false;

    for (counter = 0; counter < 10; counter++) {
        if (productsList[counter].productID != 0) {
            if (!header) {
                cout << "Product List: " << endl;
            }
            cout << productsList[counter].productID << " - " << productsList[counter].productName << " - " << productsList[counter].quantity << " - " << productsList[counter].unitPrice << " - " << productsList[counter].price << endl;
        }
    }
}

void Invoice :: payUpdate(const float amount) {
    amountPaid += amount;
    amountToBePaid = total - amountPaid;
}

int updateCustomerData(const Customer &obj) {
    fstream file;
    Customer object;
    int location, res;

    res = fileTimeUpdate(2);
    if (res == 404) {
        return 404;
    }

    file.open(CustomerFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Customer));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(CustomerFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Customer);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Customer));

    file.close();

    return 1;
}

bool verifyCustomerID(const int id) {
    Customer object;
    fstream file;
    int fileSize, counter;

    file.open(CustomerFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Customer));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Customer :: Customer() {
    totalPayable = 0.0;
    customerType = 'u';
}

Customer :: ~Customer() {
    
}

int Customer :: getID() {
    return id;
}

float Customer :: getTotalPayable() {
    return totalPayable;
}

void Customer :: inputInfo() {

    do {
        assignID();
    } while (!verifyCustomerID(id));

    Person::inputInfo();
    cout << "Enter customer type" << endl;
    cout << "Press R for retail and B for business type of customer: ";
    cin >> customerType;
    fflush(stdin);
    while (customerType != 'R' && customerType != 'r' && customerType != 'B' && customerType != 'b')
    {
        cout << "Incorrect customer type!" << endl;
        cout << "Enter customer type" << endl;
        cout << "Press R for retail and B for business type of customer: ";
        cin >> customerType;
        fflush(stdin);
    }

    if (customerType == 'r') {
        customerType = 'R';
    }
    else if (customerType == 'b') {
        customerType = 'B';
    }
}

void Customer :: displayInfo() {
    string tempString;

    if (customerType == 'R') {
        tempString = "Retail";
    }
    else {
        tempString = "Business";
    }

    cout << "Customer Information:" << endl;
    Person :: displayInfo();
    cout << "Customer Type: " << tempString << endl;
    cout << "total Payable: $" << fixed << setprecision(2) << totalPayable << endl;
}

bool Customer :: modifyInfo() {
    bool response;

    response = Person :: modifyInfo();

    return response;
}

int Customer :: add() {
    fstream file;
    int res;

    res = fileTimeUpdate(2);
    if (res != 1) {
        return res;
    }

    file.open(CustomerFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(CustomerFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(CustomerFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Customer));
    file.close();
    return 1;
}

int Customer :: searchID(const int id) {
    fstream customerFile;
    int counter, fileSize;

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return 404;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)this, sizeof(Customer));

        if (this->id == id) {
            customerFile.close();
            return 1;
        }
    }

    customerFile.close();
    return 0;
}

int Customer :: searchUsername(const string username) {
    fstream customerFile;
    int counter, fileSize;
    char tempUsername[30];

    strcpy(tempUsername, username.c_str());

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return 404;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)this, sizeof(Customer));

        if (strcmp(this->username, tempUsername) == 0) {
            customerFile.close();
            return 1;
        }
    }

    customerFile.close();
    return 0;
}

int Customer :: searchEmail(const string email) {
    fstream customerFile;
    int counter, fileSize;
    char tempEmail[30];

    strcpy(tempEmail, email.c_str());

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return 404;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)this, sizeof(Customer));

        if (strcmp(this->emailAddress, tempEmail) == 0) {
            customerFile.close();
            return 1;
        }
    }

    customerFile.close();
    return 0;
}

int Customer :: searchConatctNumber(const unsigned long int contactNumber) {
    fstream customerFile;
    int counter, fileSize;    

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return 404;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)this, sizeof(Customer));

        if (this->contactNumber == contactNumber) {
            customerFile.close();
            return 1;
        }
    }

    customerFile.close();
    return 0;
}

int Customer :: login() {
    string tempString;
    int res;

    cout << "Enter username or enter -1 to go back: ";
    getline(cin, tempString);
    fflush(stdin);
    if (tempString == "-1") {
        return 2;
    }
    res = searchUsername(tempString);
    if (res != 1) {
        return res;
    }

    cout << "Enter password: ";
    getline(cin, tempString);
    fflush(stdin);
    if (verifyPassword(tempString)) {
        return 1;
    }
    else {
        return 0;
    }

}

int Customer :: payInvoice() {
    Invoice invoiceObj;
    CreditCard creditCardObj;
    int tempID, res;
    float amount;

    res = invoiceObj.searchCustomerID(id);
    if (res == 404) {
        return 404;
    }
    else if (res == 0) {
        return -1;
    }
    cout << "Enter Invoice ID of invoice you want to pay: ";
    cin >> tempID;
    fflush(stdin);
    res = invoiceObj.searchID(tempID);
    if (res == 404) {
        return 404;
    }
    while (res == 0) {
        cout << "Incorrect invoice number entered!" << endl;
        cout << "Enter Invoice ID of invoice you want to pay: ";
        cin >> tempID;
        fflush(stdin);
        res = invoiceObj.searchID(tempID);
        if (res == 404) {
            return 404;
        }
    }

    cout << "Enter the amount you want to pay: ";
    cin >> amount;
    fflush(stdin);
    while (amount <= 0 && amount > invoiceObj.getAmountToBePaid()) {
        cout << "Incorrect amount entered!" << endl;
        cout << "Enter the amount you want to pay: ";
        cin >> amount;
        fflush(stdin);
    }

    res = creditCardObj.customerInputInfo();
    if (res == 1) {        
        invoiceObj.payUpdate(amount);
        totalPayable -= amount;
    }
    else {
        return res;
    }

    updateInvoiceData(invoiceObj);
    updateCustomerData(*this);
    return res;
}

float purchaseItems(const int customerID) {
    Invoice invoiceObj(customerID);
    Product productObj;
    InvoiceList temp;
    int userOption, tempProductID, res, counter, counter2, selection;
    float tempQuantity;    
    
    while (1) {
        cout << "Enter 1 to add a product to cart" << endl;
        cout << "Enter 2 to delete a product from cart" << endl;
        cout << "Enter 3 to close cart" << endl;
        cin >> userOption;
        fflush(stdin);
        
        if (userOption == 1) {
            res = productObj.displayProductList();
            if (res == 404) {
                return -1;
            }
            else if (res == 0) {
                cout << "No product available to buy!" << endl;
                cout << "Press enter to continue...";
                getchar();
                return -2;
            }
            else if (res == 1) {
                cout << "Enter product ID to add to cart: ";
                cin >> tempProductID;
                fflush(stdin);
                res = productObj.searchID(tempProductID);
                if (res == 404) {
                    return -1;
                }
                while (res == 0) {
                    cout << "Incorrect product ID entered!" << endl;
                    cout << "Enter product ID to add to cart: ";
                    cin >> tempProductID;
                    fflush(stdin);
                    res = productObj.searchID(tempProductID);
                    if (res == 404) {
                        return -1;
                    }
                }

                cout << "Enter quantity you want to buy: ";
                cin >> tempQuantity;
                fflush(stdin);
                while (tempQuantity <= 0 && tempQuantity > productObj.quantityAvailable) {
                    cout << "Amount entered cannot be purchased!" << endl;
                    if (tempQuantity > productObj.quantityAvailable) {
                        cout << "Not enough quantity available!" << endl;
                    }
                    cout << "Enter quantity you want to buy: ";
                    cin >> tempQuantity;
                    fflush(stdin);
                }

                for (counter = 0; counter < 10; counter++) {
                    if (invoiceObj.productsList[counter].productID == 0) {
                        invoiceObj.productsList[counter].productID = productObj.id;
                        strcpy(invoiceObj.productsList[counter].productName, productObj.name);
                        invoiceObj.productsList[counter].quantity = tempQuantity;
                        invoiceObj.productsList[counter].unitPrice = productObj.price;
                        invoiceObj.productsList[counter].price = invoiceObj.productsList[counter].quantity * invoiceObj.productsList[counter].unitPrice;
                        counter = 11;
                    }
                }

                invoiceObj.calculations();
                productObj.quantityAvailable -= tempQuantity;
                productObj.quantitySold += tempQuantity;
                if (productObj.quantityAvailable <= 0) {
                    productObj.status = 'N';
                }            
                cout << "Item successfully added to cart!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
        }
        else if (userOption == 2) {
            for (counter = 0; counter < 10; counter++) {
                if (invoiceObj.productsList[counter].productID != 0) {
                    cout << counter + 1 << " - " << invoiceObj.productsList[counter].productName << " - " << invoiceObj.productsList[counter].quantity << " - $" << fixed << setprecision(2) << invoiceObj.productsList[counter].price << endl;
                }
            }
            cout << endl << "Enter serial number of product you want to delete from cart: ";
            cin >> selection;
            fflush(stdin);
            selection--;

            if (invoiceObj.productsList[selection].productID != 0) {
                productObj.searchID(invoiceObj.productsList[selection].productID);
                productObj.quantityAvailable += invoiceObj.productsList[selection].quantity;
                productObj.quantitySold -= invoiceObj.productsList[selection].quantity;

                invoiceObj.productsList[selection].productID = 0;
                fill_n(invoiceObj.productsList[selection].productName, 30, '\0');
                invoiceObj.productsList[selection].quantity = 0.0;
                invoiceObj.productsList[selection].unitPrice = 0.0;
                invoiceObj.productsList[selection].price = 0.0;

                cout << "Item successfully deleted from cart!" << endl;
                cout << "Press enter to continue...";
                getchar();                
            }
            else {
                cout << "No product available at current selection!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
        }
        else if (userOption == 3) {            
            for (counter = 0; counter < 10; counter++) {
                for (counter2 = 1; counter2 < 10; counter2++) {
                    if (invoiceObj.productsList[counter].productID == 0 && invoiceObj.productsList[counter2].productID != 0) {
                        temp = invoiceObj.productsList[counter];
                        invoiceObj.productsList[counter] = invoiceObj.productsList[counter2];
                        invoiceObj.productsList[counter2] = temp;
                    }
                }
            }            
            res = updateProductData(productObj);
            if (res == 404) {
                return -1;
            }
            res = invoiceObj.add();
            if (res == 404) {
                return -1;
            }
            return invoiceObj.total;        
        }
        else {
            cout << endl << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }

}

int Customer :: generateInvoice() {    
    float res;
    int res2;
    res = purchaseItems(id);
    if (res == -1) {
        return 404;
    }
    else if (res == -2) {
        return 0;
    }
    else {
        updatePayable(res);
        res2 = updateCustomerData(*this);
        if (res2 == 404) {
            return 404;
        }
        
        return 1;
    }    
}

void Customer :: updatePayable(const float amount) {
    totalPayable += amount;
}

bool checkCustomerEmail(const string email) {
    fstream customerFile;
    Customer obj;
    int counter, fileSize;
    char emailChar[30];

    strcpy(emailChar, email.c_str());

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return true;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)&obj, sizeof(Customer));

        if (strcmp(obj.emailAddress, emailChar) == 0) {
            customerFile.close();
            return false;
        }
    }

    customerFile.close();
    return true;
}

bool checkCustomerUsername(const string username) {
    fstream customerFile;
    Customer obj;
    int counter, fileSize;
    char usernameChar[30];

    strcpy(usernameChar, username.c_str());

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return true;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)&obj, sizeof(Customer));

        if (strcmp(obj.username, usernameChar) == 0) {
            customerFile.close();
            return false;
        }
    }

    customerFile.close();
    return true;
}

bool checkCustomerContactNumber(const unsigned long int contactNumber) {
    fstream customerFile;
    Customer obj;
    int counter, fileSize;

    customerFile.open(CustomerFileLoc, ios::binary | ios::in);

    if (!customerFile) {
        return true;
    }

    fileSize = numberOfRecords(customerFile, sizeof(Customer));

    for (counter = 0; counter < fileSize; counter++) {
        customerFile.read((char*)&obj, sizeof(Customer));

        if (obj.contactNumber == contactNumber) {
            customerFile.close();
            return false;
        }
    }

    customerFile.close();
    return true;
}

bool checkEmployeeContactNumber(const unsigned long int contactNumber) {
    fstream employeeFile;
    Employee obj;
    int counter, fileSize;

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return true;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)&obj, sizeof(Employee));

        if (obj.contactNumber == contactNumber) {
            employeeFile.close();
            return false;
        }
    }

    employeeFile.close();
    return true;
}

int updateEmployeeData(const Employee &obj) {
    fstream file;
    Employee object;
    int location, res;

    res = fileTimeUpdate(3);
    if (res == 404) {
        return 404;
    }

    file.open(EmployeeFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Employee));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(EmployeeFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Employee);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Employee));

    file.close();

    return 1;
}

bool verifyEmployeeID(const int id) {
    Employee object;
    fstream file;
    int fileSize, counter;

    file.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Employee));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Employee :: Employee() {
    fill_n(accessControl, 7, false);
    salary = 0.0;
    fill_n(designation, 30, '\0');
}

Employee :: ~Employee() {
    
}

int Employee :: getID() {
    return id;
}

void Employee :: inputInfo() {
    string tempString;
    char tempChar;
    int counter;

    do {
        assignID();
    } while (!verifyEmployeeID(id));

    Person :: inputInfo();

    cout << "Should the employee be given access to admin?" << endl;
    cout << "Note: If given access to admin all the access are given automatically!" << endl;
    cout << "Enter you option (Yes or No): ";
    cin >> tempChar;
    fflush(stdin);
    while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
        cout << "Incorrect option entered!" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
    }

    if (tempChar == 'N' || tempChar == 'n') {
        accessControl[0] = false;
        cout << endl;

        cout << "Should employee be given access to cow releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[1] = true;
        }
        else {
            accessControl[1] = false;
        }
        cout << endl;

        cout << "Should employee be given access to customer releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[2] = true;
        }
        else {
            accessControl[2] = false;
        }
        cout << endl;

        cout << "Should employee be given access to invoice releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[3] = true;
        }
        else {
            accessControl[3] = false;
        }
        cout << endl;

        cout << "Should employee be given access to parcel releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[4] = true;
        }
        else {
            accessControl[4] = false;
        }
        cout << endl;

        cout << "Should employee be given access to product releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[5] = true;
        }
        else {
            accessControl[5] = false;
        }
        cout << endl;

        cout << "Should employee be given access to expense releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[6] = true;
        }
        else {
            accessControl[6] = false;
        }
        cout << endl;

        cout << "Should employee be given access to report releated activities?" << endl;
        cout << "Enter you option again (Yes or No): ";
        cin >> tempChar;
        fflush(stdin);
        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
            cout << "Incorrect option entered!" << endl;
            cout << "Enter you option again (Yes or No): ";
            cin >> tempChar;
            fflush(stdin);
        }

        if (tempChar == 'Y' || tempChar == 'y') {
            accessControl[7] = true;
        }
        else {
            accessControl[7] = false;
        }
    }
    else if (tempChar == 'Y' || tempChar == 'y') {
        for (counter = 0; counter < 8; counter++) {
            accessControl[counter] = true;
        }
    }

    cout << endl;

    cout << "Enter employee salaray: ";
    cin >> salary;
    fflush(stdin);
    while (salary <= 0) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter employee salaray: ";
        cin >> salary;
        fflush(stdin);
    }

    cout << endl;

    cout << "Enter employee designation: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0) {
        cout << "Field cannot be left empty!" << endl;
        cout << "Enter employee designation again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(designation, tempString.c_str());
    cout << endl;
}

void Employee :: displayInfo() {
    cout << "Employee Information:" << endl;
    Person :: displayInfo();
    cout << "Access Control:" << endl;
    cout << "Admin: " << (accessControl[0]) ? "Yes" : "No";
    cout << endl << "Cow: " << (accessControl[1]) ? "Yes" : "No";
    cout << endl << "Customer: " << (accessControl[2]) ? "Yes" : "No";
    cout << endl << "Invoice: " << (accessControl[3]) ? "Yes" : "No";
    cout << endl << "Parcel: " << (accessControl[4]) ? "Yes" : "No";
    cout << endl << "Product: " << (accessControl[5]) ? "Yes" : "No";
    cout << endl << endl;
    cout << "Salary: $" << fixed << setprecision(2) << salary << endl;
    cout << "Designation: " << designation << endl;
}

bool Employee :: modifyInfo() {
    bool update = false;
    int userOption1, userOption2, counter;
    char tempChar;
    string tempString;

    while (1) {
        cout << "Enter 1 to get options related to name, Email Address, etc." << endl;
        cout << "Enter 2 to get options related to access, salary, designation" << endl;
        cout << "Enter 3 to go back" << endl;
        cout << "Enter desired option: ";
        cin >> userOption1;
        fflush(stdin);

        if (userOption1 == 1) {
            update = Person :: modifyInfo();
        }
        else if (userOption1 == 2) {
            if (accessControl[0]) {
                cout << "Enter 1 to modify access" << endl;
                cout << "Enter 2 to modify salary" << endl;
                cout << "Enter 3 to modify designation" << endl;
                cin >> userOption2;
                fflush(stdin);

                if (userOption2 == 1) {
                    cout << "Should the employee be given access to admin?" << endl;
                    cout << "Note: If given access to admin all the access are given automatically!" << endl;
                    cout << "Enter you option (Yes or No): ";
                    cin >> tempChar;
                    fflush(stdin);
                    while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                        cout << "Incorrect option entered!" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                    }

                    if (tempChar == 'N' || tempChar == 'n') {
                        accessControl[0] = false;
                        cout << endl;

                        cout << "Should employee be given access to cow releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[1] = true;
                        }
                        else {
                            accessControl[1] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to customer releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[2] = true;
                        }
                        else {
                            accessControl[2] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to invoice releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[3] = true;
                        }
                        else {
                            accessControl[3] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to parcel releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[4] = true;
                        }
                        else {
                            accessControl[4] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to product releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[5] = true;
                        }
                        else {
                            accessControl[5] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to expense releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[6] = true;
                        }
                        else {
                            accessControl[6] = false;
                        }
                        cout << endl;

                        cout << "Should employee be given access to report releated activities?" << endl;
                        cout << "Enter you option again (Yes or No): ";
                        cin >> tempChar;
                        fflush(stdin);
                        while (tempChar != 'Y' && tempChar != 'y' && tempChar != 'N' && tempChar != 'n') {
                            cout << "Incorrect option entered!" << endl;
                            cout << "Enter you option again (Yes or No): ";
                            cin >> tempChar;
                            fflush(stdin);
                        }

                        if (tempChar == 'Y' || tempChar == 'y') {
                            accessControl[7] = true;
                        }
                        else {
                            accessControl[7] = false;
                        }
                    }
                    else if (tempChar == 'Y' || tempChar == 'y') {
                        for (counter = 0; counter < 8; counter++) {
                            accessControl[counter] = true;
                        }
                    }

                    cout << endl << "Access Updated!" << endl;
                    cout << "Press enter to continue...";
                    getchar();
                    update = true;
                }
                else if (userOption2 == 2) {
                    cout << "Enter employee salaray: ";
                    cin >> salary;
                    fflush(stdin);
                    while (salary <= 0) {
                        cout << "Incorrect value entered!" << endl;
                        cout << "Enter employee salaray: ";
                        cin >> salary;
                        fflush(stdin);
                    }

                    cout << endl << "Salary Updated!" << endl;
                    cout << "Press enter to continue...";
                    getchar();
                    update = true;                
                }
                else if (userOption2 == 3) {
                    cout << "Enter employee designation: ";
                    getline(cin, tempString);
                    fflush(stdin);
                    while (tempString.length() <= 0) {
                        cout << "Field cannot be left empty!" << endl;
                        cout << "Enter employee designation again: ";
                        getline(cin, tempString);
                        fflush(stdin);
                    }

                    cout << endl << "Designation Updated!" << endl;
                    cout << "Press enter to continue...";
                    getchar();
                    update = true;

                    fill_n(designation, 30, '\0');
                    strcpy(designation, tempString.c_str());                
                }
                else {
                    cout << endl << "Incorrect option entered!" << endl;
                    cout << "Press enter to continue...";
                    getchar();
                }
            }
            else {
                cout << "You do not have access to perform this task!" << endl;
                cout << "Press enter to continue..." << endl;
                getchar();
            }
        }
        else if (userOption1 == 3) {
            return update;
        }
        else {
            cout << endl << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }

        system("cls");
    }
}

int Employee :: add() {
    fstream file;
    int res;

    res = fileTimeUpdate(3);
    if (res != 1) {
        return res;
    }

    file.open(EmployeeFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(EmployeeFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(EmployeeFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Employee));
    file.close();
    return 1;
}

int Employee :: searchID(const int id) {
    fstream employeeFile;
    int counter, fileSize;

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return 404;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)this, sizeof(Employee));

        if (this->id == id) {
            employeeFile.close();
            return 1;
        }
    }

    employeeFile.close();
    return 0;
}

int Employee :: searchUsername(const string username) {
    fstream employeeFile;
    int counter, fileSize;
    char tempUsername[30];

    fill_n(tempUsername, 30, '\0');
    strcpy(tempUsername, username.c_str());

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return 404;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)this, sizeof(Employee));

        if (strcmp(this->username, tempUsername) == 0) {            
            employeeFile.close();
            return 1;
        }
    }

    employeeFile.close();
    return 0;
}

int Employee :: searchEmail(const string email) {
    fstream employeeFile;
    int counter, fileSize;
    char tempEmail[30];

    strcpy(tempEmail, email.c_str());

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return 404;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)this, sizeof(Employee));

        if (strcmp(this->emailAddress, tempEmail) == 0) {
            employeeFile.close();
            return 1;
        }
    }

    employeeFile.close();
    return 0;
}

int Employee :: searchConatctNumber(const unsigned long int contactNumber) {
    fstream employeeFile;
    int counter, fileSize;    

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return 404;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)this, sizeof(Employee));

        if (this->contactNumber == contactNumber) {
            employeeFile.close();
            return 1;
        }
    }

    employeeFile.close();
    return 0;
}

int Employee :: login() {
    string tempString;
    int res;

    cout << "Enter username or enter -1 to go back: ";
    getline(cin, tempString);
    fflush(stdin);
    if (tempString == "-1") {
        return 2;
    }
    res = searchUsername(tempString);
    if (res != 1) {
        return res;
    }

    cout << "Enter password: ";
    getline(cin, tempString);
    fflush(stdin);
    if (verifyPassword(tempString)) {
        return 1;
    }
    else {
        return 0;
    }
}

bool checkEmployeeEmail(const string email) {
    fstream employeeFile;
    Employee obj;
    int counter, fileSize;
    char emailChar[30];

    strcpy(emailChar, email.c_str());

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return true;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)&obj, sizeof(Employee));

        if (strcmp(obj.emailAddress, emailChar) == 0) {
            employeeFile.close();
            return false;
        }
    }

    employeeFile.close();
    return true;
}

bool checkEmployeeUsername(const string username) {
    fstream employeeFile;
    Employee obj;
    int counter, fileSize;
    char usernameChar[30];

    strcpy(usernameChar, username.c_str());

    employeeFile.open(EmployeeFileLoc, ios::binary | ios::in);

    if (!employeeFile) {
        return true;
    }

    fileSize = numberOfRecords(employeeFile, sizeof(Employee));

    for (counter = 0; counter < fileSize; counter++) {
        employeeFile.read((char*)&obj, sizeof(Employee));

        if (strcmp(obj.username, usernameChar) == 0) {
            employeeFile.close();
            return false;
        }
    }

    employeeFile.close();
    return true;
}

bool verifyCreditCardID(const int id) {
    CreditCard object;
    fstream file;
    int fileSize, counter;

    file.open(CreditCardFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(CreditCard));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(CreditCard));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

CreditCard ::CreditCard()
{
    int i;

    id = 0;
    cardNumber = 0;
    dateOfIssue.date = 0;
    dateOfIssue.month = 0;
    dateOfIssue.year = 0;
    expiryDate.date = 0;
    expiryDate.month = 0;
    expiryDate.year = 0;
    cvc = 0;
    for (i = 0; i < 30; i++)
    {
        cardHolderName[i] = '\0';
    }
}

CreditCard :: ~CreditCard() {
    
}

int CreditCard :: getID() {
    return id;
}

void CreditCard ::inputInfo()
{
    do {
        assignID();
    } while (!verifyCreditCardID(id));

    int i;
    string tempString;

    assignID();

    cout << "Enter the card number: ";
    cin >> cardNumber;
    fflush(stdin);

    while (cardNumber < 1000000000000000 || cardNumber > 9999999999999999)
    {
        cout << "Incorrect number!" << endl;
        cout << "Enter the card number: ";
        cin >> cardNumber;
        fflush(stdin);
    }

    dateOfIssue.date = 0;

    cout << "Enter the month of issue date: ";
    cin >> dateOfIssue.month;
    fflush(stdin);

    cout << "Enter year of issue date: ";
    cin >> dateOfIssue.year;
    fflush(stdin);

    while (!dateVerification(dateOfIssue.date, dateOfIssue.month, dateOfIssue.year, 'I'))
    {
        cout << "Enter the month of issue date: ";
        cin >> dateOfIssue.month;
        fflush(stdin);

        cout << "Enter year of issue date: ";
        cin >> dateOfIssue.year;
        fflush(stdin);
    }

    expiryDate.date = 0;

    cout << "Enter the month of expiry date: ";
    cin >> expiryDate.month;
    fflush(stdin);

    cout << "Enter year of expiry date: ";
    cin >> expiryDate.year;
    fflush(stdin);

    while (!dateVerification(expiryDate.date, expiryDate.month, expiryDate.year, 'E'))
    {
        cout << "Enter the month of expiry date: ";
        cin >> expiryDate.month;
        fflush(stdin);

        cout << "Enter year of expiry date: ";
        cin >> expiryDate.year;
        fflush(stdin);
    }

    cout << "Enter card holder name: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() == 0)
    {
        cout << "Name category could not be left empty!" << endl;
        cout << "Enter card holder name: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(cardHolderName, tempString.c_str());

    cout << "Enter cvc: ";
    cin >> cvc;
    fflush(stdin);
    while (cvc < 100 && cvc > 999)
    {
        cout << "Incorrect cvc!" << endl;
        cout << "Enter cvc: ";
        cin >> cvc;
        fflush(stdin);
    }
}

void CreditCard ::displayInfo()
{
    int i;
    cout << "ID: " << id << endl;
    cout << "Card number: " << cardNumber << endl;
    cout << "Issue date: " << dateOfIssue.date << "/" << dateOfIssue.month << "/" << dateOfIssue.year << endl;
    cout << "Expiry date: " << expiryDate.date << "/" << expiryDate.month << "/" << expiryDate.year << endl;
    cout << "Crd holder name: ";
    for (i = 0; i < 30; i++)
    {
        cout << cardHolderName[i];
    }
    cout << endl;
    cout << "cvc: " << cvc << endl;
}

bool CreditCard :: modifyInfo()
{
    return false;
}

int CreditCard :: add()
{    
    fstream file;
    int res;

    res = fileTimeUpdate(1);
    if (res != 1) {
        return res;
    }

    file.open(CreditCardFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(CreditCardFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(CreditCardFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(CreditCard));
    file.close();
    return 1;
}

int CreditCard ::searchID(const int id)
{
    fstream CreditCardFile;
    int counter, fileSize;

    CreditCardFile.open(CreditCardFileLoc, ios::binary | ios::in);

    if (!CreditCardFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(CreditCardFile, sizeof(CreditCard));

    for (counter = 0; counter < fileSize; counter++)
    {
        CreditCardFile.read((char *)this, sizeof(CreditCard));

        if (this->id == id)
        {
            CreditCardFile.close();
            return 1;
        }
    }

    CreditCardFile.close();
    return 0;
}

int CreditCard :: searchCardNumber(const unsigned long int cardNumber) {
    fstream CreditCardFile;
    int counter, fileSize;

    CreditCardFile.open(CreditCardFileLoc, ios::binary | ios::in);

    if (!CreditCardFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(CreditCardFile, sizeof(CreditCard));

    for (counter = 0; counter < fileSize; counter++)
    {
        CreditCardFile.read((char *)this, sizeof(CreditCard));

        if (this->cardNumber == cardNumber)
        {
            CreditCardFile.close();
            return 1;
        }
    }

    CreditCardFile.close();
    return 0;
}

bool CreditCard ::verifyCard(const Date expiry, const int cvc)
{
    if (expiryDate == expiry && this->cvc == cvc) {
        return true;
    }
    else {
        return false;
    }
}

int CreditCard :: customerInputInfo() {
    unsigned long int number;
    Date expiry;
    int cvcCode, res;
    bool response;

    cout << "Enter card number: ";
    cin >> number;
    fflush(stdin);
    res = searchCardNumber(number);
    while (res == 0) {
        cout << "Card does not exist!" << endl;
        cout << "Enter card number again: ";
        cin >> number;
        fflush(stdin);
        res = searchCardNumber(number);
    }
    if (res == 404) {
        return 404;
    }

    cout << endl;
    
    expiry.date = 0;

    cout << "Enter expiry month: ";
    cin >> expiry.month;
    fflush(stdin);
    while (expiry.month <= 0 && expiry.month > 12) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter expiry month again: ";
        cin >> expiry.month;
        fflush(stdin);
    }

    cout << "Enter expiry year: ";
    cin >> expiry.year;
    fflush(stdin);
    while (expiry.year <= 0 && expiry.date > 9999) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter expiry year again: ";
        cin >> expiry.year;
        fflush(stdin);
    }

    cout << endl;

    cout << "Enter CVC: ";
    cin >> cvcCode;
    fflush(stdin);
    while (cvcCode < 100 && cvcCode > 999)
    {
        cout << "Incorrect CVC!" << endl;
        cout << "Enter CVC again: ";
        cin >> cvcCode;
        fflush(stdin);
    }

    response = verifyCard(expiry, cvcCode);
    if (response) {
        return 1;
    }
    else {
        return 0;
    }
}

int updateExpenseData(const Expense &obj) {
    fstream file;
    Expense object;
    int location, res;

    res = fileTimeUpdate(4);
    if (res == 404) {
        return 404;
    }

    file.open(ExpenseFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Expense));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(ExpenseFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Expense);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Expense));

    file.close();

    return 1;
}

bool verifyExpenseID(const int id) {
    Expense object;
    fstream file;
    int fileSize, counter;

    file.open(ExpenseFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Expense));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Expense));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Expense ::Expense()
{
    fill_n(name, 30, '\0');
    fill_n(description, 30, '\0');
    expenseDate.date = localTimeNow->tm_mday;
    expenseDate.month = localTimeNow->tm_mon + 1;
    expenseDate.year = localTimeNow->tm_year + 1900;
    subAmount = 0.0;
    tax = 0.0;
    totalAmount = 0.0;
}

Expense ::~Expense()
{
}

int Expense :: getID() {
    return id;
}

void Expense ::inputInfo()
{
    char choice;

    do {
        assignID();
    } while (!verifyExpenseID(id));

    string tempString;
    cout << "Enter name of expense: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0)
    {
        cout << "Name field can not be left empty!" << endl;
        cout << "Enter name of expense again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(name, tempString.c_str());
    cout << endl;

    cout << "Enter description of expense: ";
    getline(cin, tempString);
    fflush(stdin);
    while (tempString.length() <= 0)
    {
        cout << "Description field can not be left empty!" << endl;
        cout << "Enter decription of expense again: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(description, tempString.c_str());
    cout << endl;

    cout << "Enter date of expense: ";
    cin >> expenseDate.date;
    fflush(stdin);

    cout << "Enter month of expense: ";
    cin >> expenseDate.month;
    fflush(stdin);

    cout << "Enter year of expense: ";
    cin >> expenseDate.year;
    fflush(stdin);

    while (!dateVerification(expenseDate.date, expenseDate.month, expenseDate.year, 'X'))
    {
        cout << "Incorrect date!" << endl;
        cout << "Enter date of expense: ";
        cin >> expenseDate.date;
        fflush(stdin);

        cout << "Enter month of expense: ";
        cin >> expenseDate.month;
        fflush(stdin);

        cout << "Enter year of expense: ";
        cin >> expenseDate.year;
        fflush(stdin);
    }

    cout << "Enter sub amount of expense: ";
    cin >> subAmount;
    fflush(stdin);

    while (subAmount <= 0)
    {
        cout << "Incorrect sub amount!" << endl;
        cout << "Enter sub amount of expense again: ";
        cin >> subAmount;
        fflush(stdin);
    }

    cout << "Tax is applicable on this expense? " << endl;
    cout << "Press 'y' for yes and 'n' for no";
    cin >> choice;
    fflush(stdin);

    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter the tax percentage: ";
        cin >> tax;
        fflush(stdin);

        while (tax <= 0)
        {
            cout << "Incorrect tax choice!" << endl;
            cout << "Enter tax percentage again: ";
            cin >> tax;
            fflush(stdin);
        }

        calculation();
    }

    else if (choice == 'n' || choice == 'N')
    {
        tax = 0;
        calculation();
    }

    else
    {
        cout << "Incorrect choice!" << endl;
        cout << "Press enter to continue..";
        getchar();
    }

    system("cls");
}

void Expense ::displayInfo()
{
    cout << "Expense Information:" << endl;
    Id :: displayInfo();
    cout << "Name of expense: " << name << endl;
    cout << "Description of expense: " << description << endl;
    cout << "Expense date: " << expenseDate.date << "," << expenseDate.month << "," << expenseDate.year << endl;
    cout << "Sub amount of expense: " << subAmount << endl;
    if (tax == 0)
    {
        cout << "No tax applicable!" << endl;
    }
    else
    {
        cout << "Tax percentage: " << tax << "%" << endl;
    }
    cout << "Total amount: " << totalAmount << endl;
}

bool Expense ::modifyInfo()
{
    char choice;
    string tempString;
    int userOption;
    bool update = false;

    while (1)
    {
        cout << "Press 1 to update name of expense" << endl;
        cout << "Press 2 to update description of expense" << endl;
        cout << "Press 3 to update expense date" << endl;
        cout << "Press 4 to update sub amount of expense" << endl;
        cout << "Press 5 to go back";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1)
        {
            cout << "Enter name of expense: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0)
            {
                cout << "Name field can not be left empty!" << endl;
                cout << "Enter name of expense again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(name, tempString.c_str());
            cout << endl;

            update = true;
        }

        else if (userOption == 2)
        {
            cout << "Enter description of expense: ";
            getline(cin, tempString);
            fflush(stdin);
            while (tempString.length() <= 0)
            {
                cout << "Description field can not be left empty!" << endl;
                cout << "Enter decription of expense again: ";
                getline(cin, tempString);
                fflush(stdin);
            }

            strcpy(description, tempString.c_str());
            cout << endl;

            update = true;
        }

        else if (userOption == 3)
        {
            cout << "Enter date of expense: ";
            cin >> expenseDate.date;
            fflush(stdin);

            cout << "Enter month of expense: ";
            cin >> expenseDate.month;
            fflush(stdin);

            cout << "Enter year of expense: ";
            cin >> expenseDate.year;
            fflush(stdin);

            while (!dateVerification(expenseDate.date, expenseDate.month, expenseDate.year, 'X'))
            {
                cout << "Incorrect date!" << endl;
                cout << "Enter date of expense: ";
                cin >> expenseDate.date;
                fflush(stdin);

                cout << "Enter month of expense: ";
                cin >> expenseDate.month;
                fflush(stdin);

                cout << "Enter year of expense: ";
                cin >> expenseDate.year;
                fflush(stdin);
            }

            update = true;
        }

        else if (userOption == 4)
        {
            cout << "Enter sub amount of expense: ";
            cin >> subAmount;
            fflush(stdin);

            while (subAmount <= 0)
            {
                cout << "Incorrect sub amount!" << endl;
                cout << "Enter sub amount of expense again: ";
                cin >> subAmount;
                fflush(stdin);
            }

            cout << "Tax is applicable on this expense? " << endl;
            cout << "Press 'y' for yes and 'n' for no";
            cin >> choice;
            fflush(stdin);

            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter the tax percentage: ";
                cin >> tax;
                fflush(stdin);

                while (tax <= 0)
                {
                    cout << "Incorrect tax choice!" << endl;
                    cout << "Enter tax percentage again: ";
                    cin >> tax;
                    fflush(stdin);
                }

                calculation();
            }

            else if (choice == 'n' || choice == 'N')
            {
                tax = 0;
                calculation();
            }

            else
            {
                cout << "Incorrect choice!" << endl;
                cout << "Press enter to continue..";
                getchar();
            }

            system("cls");
            
            update = true;
        }

        else if (userOption == 5)
        {
            return update;
        }

        else
        {
            cout << endl
                 << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }
}

int Expense :: add()
{
    fstream file;
    int res;

    res = fileTimeUpdate(4);
    if (res != 1) {
        return res;
    }

    file.open(ExpenseFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(ExpenseFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(ExpenseFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Expense));
    file.close();
    return 1;
}

int Expense ::searchID(const int id)
{
    fstream ExpenseFile;
    int counter, fileSize;

    ExpenseFile.open(ExpenseFileLoc, ios::binary | ios::in);

    if (!ExpenseFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(ExpenseFile, sizeof(Expense));

    for (counter = 0; counter < fileSize; counter++)
    {
        ExpenseFile.read((char *)this, sizeof(Expense));

        if (this->id == id)
        {
            ExpenseFile.close();
            return 1;
        }
    }

    ExpenseFile.close();
    return 0;
}

void Expense ::calculation()
{
    totalAmount = subAmount + (subAmount * tax / 100);
}

int updateFeedData(const Feed &obj) {
    fstream file;
    Feed object;
    int location, res;

    res = fileTimeUpdate(5);
    if (res == 404) {
        return 404;
    }

    file.open(FeedFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Feed));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(FeedFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Feed);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Feed));

    file.close();

    return 1;
}

bool verifyFeedID(const int id) {
    Feed object;
    fstream file;
    int fileSize, counter;

    file.open(FeedFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Feed));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Feed));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Feed :: Feed() {
    feedingDate.date = localTimeNow->tm_mday;
    feedingDate.month = localTimeNow->tm_mon + 1;
    feedingDate.year = localTimeNow->tm_year + 1900;
    feedingTime.hours = localTimeNow->tm_hour;
    feedingTime.minutes = localTimeNow->tm_min;
    feedingTime.seconds = localTimeNow->tm_sec;

    cowID = 0;
    quantity = 0;
}

Feed :: Feed(const int id) {
    feedingDate.date = localTimeNow->tm_mday;
    feedingDate.month = localTimeNow->tm_mon + 1;
    feedingDate.year = localTimeNow->tm_year + 1900;
    feedingTime.hours = localTimeNow->tm_mday;
    feedingTime.minutes = localTimeNow->tm_min;
    feedingTime.seconds = localTimeNow->tm_sec;

    cowID = id;
    quantity = 0.0;
}

Feed :: Feed(const int id, const float quantity) {
    feedingDate.date = localTimeNow->tm_mday;
    feedingDate.month = localTimeNow->tm_mon + 1;
    feedingDate.year = localTimeNow->tm_year + 1900;
    feedingTime.hours = localTimeNow->tm_mday;
    feedingTime.minutes = localTimeNow->tm_min;
    feedingTime.seconds = localTimeNow->tm_sec;

    cowID = id;
    this->quantity = quantity;
}

Feed :: ~Feed() {
    
}

int Feed :: getID() {
    return id;
}

void Feed :: inputInfo() {
    do {
        assignID();
    } while (verifyFeedID(id));

    cout << "Enter quantity of feed given to cow: ";
    cin >> quantity;
    fflush(stdin);
    cout << endl;
}

void Feed :: displayInfo() {
    cout << "Cow ID: " << cowID << endl;
    cout << "Feeding Time: " << feedingTime.hours << ":" << feedingTime.minutes << ":" << feedingTime.seconds << endl;
    cout << "Feeding Date: " << feedingDate.date << "/" << feedingDate.month << "/" << feedingDate.year << endl;
}

bool Feed :: modifyInfo() {
    bool update = false;

    cout << "Enter quantity to update feed given to cow or enter -1 to go back: ";
    cin >> quantity;
    fflush(stdin);

    if (quantity == -1) {
        return update;
    } 

    while (quantity <= 0) {
        cout << "Incorrect value entered!" << endl;
        cout << "Enter quantity to update feed given to cow again or enter -1 to go back: ";
        cin >> quantity;
        fflush(stdin);

        if (quantity == -1) {
            return update;
        }
    }

    update = true;
    return update;
}

int Feed :: add() {
    fstream file;
    int res;

    res = fileTimeUpdate(5);
    if (res != 1) {
        return res;
    }

    file.open(FeedFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(FeedFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(FeedFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Feed));
    file.close();
    return 1;
}

int Feed :: searchID(const int id) {
    fstream feedFile;
    int counter, fileSize;

    feedFile.open(FeedFileLoc, ios::binary | ios::in);

    if (!feedFile) {
        return 404;
    }

    fileSize = numberOfRecords(feedFile, sizeof(Feed));

    for (counter = 0; counter < fileSize; counter++) {
        if (this->id == id) {
            feedFile.close();
            return 1;
        }
    }

    feedFile.close();

    return 0;
}

int updateParcelData(const Parcel &obj) {
    fstream file;
    Parcel object;
    int location, res;

    res = fileTimeUpdate(7);
    if (res == 404) {
        return 404;
    }

    file.open(ParcelFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Parcel));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(ParcelFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Parcel);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Parcel));

    file.close();

    return 1;
}

bool verifyParcelID(const int id) {
    Parcel object;
    fstream file;
    int fileSize, counter;

    file.open(ParcelFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Parcel));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Parcel));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Parcel ::Parcel()
{
    invoiceID = 0;
    status = 'u';
    customerID = 0;
}

Parcel :: Parcel(const int invoiceId, const int customerId)
{
    invoiceID = invoiceId;
    customerID = customerId;
    status = 'u';
}

Parcel :: ~Parcel()
{

}

int Parcel :: getID() {
    return id;
}

void Parcel ::inputInfo()
{
    do
    {
        assignID();
    } 
    while (!verifyParcelID(id));

    cout << "Press 1 for paid" << endl;
    cout << "Press 2 for unpaid" << endl;
    cout << "Press 3 for dispatched" << endl;
    cout << "Press 4 for delivered" << endl;
    cout << "Your choice: ";
    cin >> status;
    fflush(stdin);
    while (status != '1' && status != '2' && status != '3' && status != '4')
    {
        cout << "Incorrect choice!" << endl;
        cout << "Enter your choice again: ";
        cin >> status;
        fflush(stdin);
    }
}

void Parcel ::displayInfo()
{
    Invoice obj;
    int result;

    obj.searchID(invoiceID);
    
    cout << "Parcel Information: " << endl;
    cout << "Parcel ID: " << id << endl;
    cout << "Parcel status: ";

    if (status == 1)
    {
        cout << "Paid" << endl;
    }
    else if (status == 2)
    {
        cout << "Unpaid" << endl;
    }
    else if (status == 3)
    {
        cout << "Dispatched" << endl;
    }
    else if (status == 4)
    {
        cout << "Delivered" << endl;
    }

    obj.displayInfo();
    obj.displayProductList();    
}

bool Parcel ::modifyInfo()
{
    int userOption;
    bool update = false;

    while (1)
    {
        cout << "Press 1 to update the status of parcel" << endl;
        cout << "Press 2 to go back" << endl;
        cout << "Your choice: ";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1)
        {
            cout << "Press 1 for paid" << endl;
            cout << "Press 2 for unpaid" << endl;
            cout << "Press 3 for dispatched" << endl;
            cout << "Press 4 for delivered" << endl;
            cout << "Your choice: ";
            cin >> status;
            fflush(stdin);
            while (status != '1' && status != '2' && status != '3' && status != '4')
            {
                cout << "Incorrect choice!" << endl;
                cout << "Enter your choice again: ";
                cin >> status;
                fflush(stdin);
            }
            update = true;
        }

        else if (userOption == 2)
        {
            return update;
        }

        else
        {
            cout << endl
                 << "Incorrect choice entered!" << endl;
            cout << "Press enter to continue....";
            getchar();
        }
        system("cls");
    }
}

int Parcel :: add()
{
    fstream file;
    int res;

    res = fileTimeUpdate(7);
    if (res != 1) {
        return res;
    }

    file.open(ParcelFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(ParcelFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(ParcelFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Parcel));
    file.close();
    return 1;
}

int Parcel ::searchID(const int id)
{
    fstream ParcelFile;
    int counter, fileSize;

    ParcelFile.open(ParcelFileLoc, ios::binary | ios::in);

    if (!ParcelFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(ParcelFile, sizeof(Parcel));

    for (counter = 0; counter < fileSize; counter++)
    {
        ParcelFile.read((char *)this, sizeof(Parcel));

        if (this->id == id)
        {
            ParcelFile.close();
            return 1;
        }
    }

    ParcelFile.close();
    return 0;
}

int Parcel :: searchCustomerID(const int customerID) {
    fstream ParcelFile;
    int counter, fileSize;
    bool found = false, header = false;

    ParcelFile.open(ParcelFileLoc, ios::binary | ios::in);

    if (!ParcelFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(ParcelFile, sizeof(Parcel));

    for (counter = 0; counter < fileSize; counter++)
    {
        ParcelFile.read((char *)this, sizeof(Parcel));

        if (this->customerID == customerID)
        {
            if (!header) {
                cout << "Parcel List:" << endl;
                header = true;
            }
            displayParcel();
            found = true;
        }
    }

    ParcelFile.close();
    if (found) {
        return 1;
    }
    else {
        return 0;
    }
}

void Parcel :: displayParcel() {
    string tempString;
    if (status == 1)
        {
            tempString = "Paid";
        }
        else if (status == 2)
        {
            tempString = "Unpaid";
        }
        else if (status == 3)
        {
            tempString = "Dispatched";
        }
        else if (status == 4)
        {
            tempString = "Delivered";
        }
    cout << id << " - " << invoiceID << " - " << tempString << endl;
}

int customerNotification(const int id)
{
    Parcel parcelObj;
    int res;

    res = parcelObj.searchCustomerID(id);
    if (res != 1)
    {
        return res;
    }

    return 0;
}

int updateProductData(const Product &obj) {
    fstream file;
    Product object;
    int location, res;

    res = fileTimeUpdate(8);
    if (res == 404) {
        return 404;
    }

    file.open(ProductFileLoc, ios::binary | ios::in);
    
    if (!file) {
        return 404;
    }

    do {
        file.read((char*)&object, sizeof(Product));
    } while (obj.id != object.id);

    location = file.tellg();    

    file.close();

    file.open(ProductFileLoc, ios::binary | ios::out);
    
    if (!file) {
        return 404;
    }

    location -= sizeof(Product);
    file.seekg(0, ios::beg);
    file.seekg(location, ios::cur);
    file.seekg(0, ios::cur);    

    file.write((char*)&obj, sizeof(Product));

    file.close();

    return 1;
}

bool verifyProductID(const int id) {
    Product object;
    fstream file;
    int fileSize, counter;

    file.open(ProductFileLoc, ios::binary | ios::in);

    if (!file) {
        return true;
    }

    fileSize = numberOfRecords(file, sizeof(Product));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)&object, sizeof(Product));

        if (object.id == id) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

Product ::Product()
{
    int i;
    for (i = 0; i < 30; i++)
    {
        name[i] = '\0';
    }

    for (i = 0; i < 50; i++)
    {
        description[i] = '\0';
    }

    quantityAvailable = 0.0;
    quantitySold = 0.0;
    price = 0.0;
    status = 'u';
}

Product ::~Product()
{
}

int Product :: getID() {
    return id;
}

void Product ::inputInfo()
{
    string tempString;

    do
    {
        assignID();
    } while (!verifyProductID(id));

    cout << "Enter name of product: ";
    getline(cin, tempString);
    fflush(stdin);

    while (tempString.length() == 0)
    {
        cout << "Name field could not be left empty!" << endl;
        cout << "Enter name of product: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(name, tempString.c_str());

    cout << "Enter description of product: ";
    getline(cin, tempString);
    fflush(stdin);

    while (tempString.length() == 0)
    {
        cout << "Description field could not be left empty!" << endl;
        cout << "Enter description of product: ";
        getline(cin, tempString);
        fflush(stdin);
    }

    strcpy(description, tempString.c_str());

    cout << "Enter quantity available of product: ";
    cin >> quantityAvailable;
    fflush(stdin);

    while (quantityAvailable < 0.0)
    {
        cout << "Incorrect quantity!" << endl;
        cin >> quantityAvailable;
        fflush(stdin);
    }

    cout << "Enter quantity sold of product: ";
    cin >> quantitySold;
    fflush(stdin);

    while (quantityAvailable < 0.0)
    {
        cout << "Incorrect quantity!" << endl;
        cin >> quantitySold;
        fflush(stdin);
    }

    cout << "Enter price of product: ";
    cin >> price;
    fflush(stdin);

    while (price <= 0)
    {
        cout << "Incorrect price: " << endl;
        cout << "Enter price of product: ";
        cin >> price;
        fflush(stdin);
    }

    if (quantityAvailable > 0)
    {
        status = 'A';
    }
    else
    {
        status = 'N';
    }
}

void Product ::displayInfo()
{
    cout << "Product Information: " << endl;
    Id :: displayInfo();
    cout << "Product name: " << name << endl;
    cout << "Product description: " << description << endl;
    cout << "Quantity available of product: " << quantityAvailable << endl;
    cout << "Quantity sold of product: " << quantitySold << endl;
    cout << "Price of product: " << price << endl;
    cout << "Status: ";
    if (status == 'A')
    {
        cout << "Available" << endl;
    }
    else if (status == 'N')
    {
        cout << "Not Available" << endl;
    }
}

bool Product ::modifyInfo()
{
    int userOption;
    bool update = false;

    while (1)
    {
        cout << "Enter 1 to update quantity available" << endl;
        cout << "Enter 2 to update price" << endl;
        cout << "Enter 3 to go back" << endl;
        cout << "Enter desired option: ";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1)
        {
            float quantityToBeAdded;
            cout << "Enter the quantity of product that you want to add:";
            cin >> quantityToBeAdded;
            fflush(stdin);

            while (quantityToBeAdded <= 0)
            {
                cout << "Incorrect quantity!" << endl;
                cout << "Enter the quantity of product again that you want to add:";
                cin >> quantityToBeAdded;
                fflush(stdin);
            }

            quantityAvailable += quantityToBeAdded;

            if (quantityAvailable > 0)
            {
                status = 'A';
            }

            else
            {
                status = 'N';
            }
            updateProductionLog(quantityToBeAdded);
            update = true;
        }

        else if (userOption == 2)
        {
            cout << "Enter the price of product: ";
            cin >> price;
            fflush(stdin);

            while (price <= 0)
            {
                cout << "Incorrect price!" << endl;
                cout << "Enter the price of product again: ";
                cin >> price;
                fflush(stdin);
            }

            update = true;
        }

        else if (userOption == 3)
        {
            return update;
        }

        else
        {
            cout << endl
                 << "Incorrect option entered!" << endl;
            cout << "Press enter to continue...";
            getchar();
        }
        system("cls");
    }
}

int Product :: add()
{
    fstream file;
    int res;

    res = fileTimeUpdate(8);
    if (res != 1) {
        return res;
    }

    file.open(ProductFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(ProductFileLoc, ios::binary | ios::trunc | ios::out);
        if (!file) {
            return 404;
        }
        file.close();

        file.open(ProductFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    file.seekg(0, ios::end);
    file.write((char*)this, sizeof(Product));
    file.close();
    return 1;
}

int Product ::searchID(const int id)
{
    fstream productFile;
    int counter, fileSize;

    productFile.open(ProductFileLoc, ios::binary | ios::in);

    if (!productFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(productFile, sizeof(Product));

    for (counter = 0; counter < fileSize; counter++)
    {
        productFile.read((char *)this, sizeof(Product));

        if (this->id == id)
        {
            productFile.close();
            return 1;
        }
    }

    productFile.close();
    return 0;
}

int Product::searchName(const string name)
{
    fstream ProductFile;
    int counter, fileSize;
    char tempString[30];

    strcpy(tempString, name.c_str());

    ProductFile.open(ProductFileLoc, ios::binary | ios::in);

    if (!ProductFile) {
        return 404;
    }

    fileSize = numberOfRecords(ProductFile, sizeof(Product));

    for (counter = 0; counter < fileSize; counter++) {
        ProductFile.read((char*)this, sizeof(Product));

        if (strcmp(this->name, tempString) == 0) {
            ProductFile.close();
            return 1;
        }
    }

    ProductFile.close();
    return 0;
}

int Product ::addProduct(const float QuantityToBeAdded)
{
    int res;
    
    quantityAvailable += QuantityToBeAdded;
    res = updateProductData(*this);
    return res;
}

int Product :: updateProductionLog(const float quantity) {
    fstream file;
    ProductionLog data;
    int res;

    res = fileTimeUpdate(10);
    if (res == 404) {
        return 404;
    }

    file.open(ProductQuantityFileLoc, ios::binary | ios::app);

    if (!file) {
        file.open(ProductQuantityFileLoc, ios::binary | ios::out | ios::trunc);
        if (!file) {
            return 404;
        }

        file.close();
        file.open(ProductQuantityFileLoc, ios::binary | ios::app);
        if (!file) {
            return 404;
        }
    }

    data.id = id;
    data.date.date = localTimeNow->tm_mday;
    data.date.month = localTimeNow->tm_mon + 1;
    data.date.year = localTimeNow->tm_year + 1900;
    data.time.hours = localTimeNow->tm_hour;
    data.time.minutes = localTimeNow->tm_min;
    data.time.seconds = localTimeNow->tm_sec;
    data.quantity = quantity;

    file.seekg(0, ios::end);
    file.write((char*)&data, sizeof(ProductionLog));
    file.close();
    return 1;
}

void Product :: displayProduct() {
    cout << id << " - " << name << " - $" << fixed << setprecision(2) << price << " - " << fixed << setprecision(2) << quantityAvailable << endl;
}

int Product :: displayProductList() {
    fstream file;
    int fileSize, counter;
    bool header = false;

    file.open(ProductFileLoc, ios::binary | ios::in);

    if (!file) {
        return 404;
    }

    fileSize = numberOfRecords(file, sizeof(Product));

    for (counter = 0; counter < fileSize; counter++) {
        file.read((char*)this, sizeof(Product));        
        if (status == 'A') {
            if (!header) {
                cout << "ProductList: " << endl;
                header = true;
            }
            displayProduct();
        }
    }

    file.close();
    if (header) {
        return 1;
    }
    else {
        return 0;
    }    
}

int productNotification()
{
    fstream productFile;
    int counter, fileSize, counter2;
    bool heading = false;
    Product obj;

    productFile.open(ProductFileLoc, ios::binary | ios::in);

    if (!productFile)
    {
        return 404;
    }

    fileSize = numberOfRecords(productFile, sizeof(Product));

    for (counter = 0; counter < fileSize; counter++)
    {
        productFile.read((char *)&obj, sizeof(Product));

        if (obj.quantityAvailable < 25)
        {
            if (!heading)
            {
                cout << "Less Quantity Notification:" << endl;
                heading = true;
            }
            cout << obj.id << " - ";
            for (counter2 = 0; counter2 < 30; counter2++)
            {
                cout << obj.name[counter2];
            }
            cout << " - "
                 << "Quantity: " << fixed << setprecision(2) << obj.quantityAvailable << endl;
        }
    }

    productFile.close();
    return 1;
}