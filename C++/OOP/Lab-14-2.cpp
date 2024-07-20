#include<iostream>
using namespace std;

const int maxCustomer = 1000;
const int maxAccounts = 1000;

class Customer {
private:
    int customerID;
    string name;
    string contactInformation;

public:
    Customer() { }
    Customer(int id, string n, string c)
    {
        customerID = id;
        name = n;
        contactInformation = c;
    }
    int getCustomerID()
    {
        return customerID;
    }

    void setCustomerID(int id) 
    {
        customerID = id;
    }

    string getName()
    {
        return name;
    }

    void setName(string n) 
    {
        name = n;
    }

    string getContactInformation()
    {
        return contactInformation;
    }

    void setContactInformation(string c) 
    {
        contactInformation = c;
    }
};

class Account {
private:
    int accountNumber;
    double accountBalance;


public:
    Account(int num, double bal)
    {
        accountNumber = num;
        accountBalance = bal;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    void setAccountNumber(int num) 
    {
        accountNumber = num;
    }

    double getAccountBalance()
    {
        return accountBalance;
    }

    void setAccountBalance(double bal) 
    {
        accountBalance = bal;
    }

    virtual void deposit(double amount) 
    {
        accountBalance += amount;
    }

    virtual void withdraw(double amount) 
    {
        accountBalance -= amount;
    }
};

class SavingsAccount : public Account 
{
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(int num, double bal, double rate, double minBal) : Account(num, bal) 
    {
        interestRate = rate;
        minimumBalance = minBal;
    }
    double getInterestRate()
    {
        return interestRate;
    }

    void setInterestRate(double rate) 
    {
        interestRate = rate;
    }

    double getMinimumBalance()
    {
        return minimumBalance;
    }

    void setMinimumBalance(double minBal) 
    {
        minimumBalance = minBal;
    }

    virtual void deposit(double amount) 
    {
        Account::deposit(amount);
        if (getAccountBalance() >= minimumBalance) 
        {
            double interest = (getAccountBalance() - minimumBalance) * interestRate;
            Account::deposit(interest);
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;
    int transactionLimit;

public:
    CurrentAccount(int num, double bal, double limit, int transLim) : Account(num, bal) 
    {
        overdraftLimit = limit;
        transactionLimit = transLim;
    }
    double getOverdraftLimit() {
        return overdraftLimit;
    }

    void setOverdraftLimit(double limit) 
    {
        overdraftLimit = limit;
    }

    int getTransactionLimit() 
    {
        return transactionLimit;
    }

    void setTransactionLimit(int transLim) 
    {
        transactionLimit = transLim;
    }

    virtual void withdraw(double amount) 
    {
        if (getAccountBalance() - amount >= -overdraftLimit) {
            Account::withdraw(amount);
        }
    }
};

class Bank {
private:

    Customer customers[maxCustomer];
    Account* accounts[maxAccounts];
    int numCustomers;
    int numAccounts;

public:
    Bank() 
    {
        numCustomers = 0;
        numAccounts = 0;
    }

    void addCustomer(Customer c) 
    {
        if (numCustomers < maxCustomer) 
        {
            customers[numCustomers] = c;
            numCustomers++;
        }
    }

    void addAccount(Account* a) 
    {
        if (numAccounts < maxAccounts) 
        {
            accounts[numAccounts] = a;
            numAccounts++;
        }
    }

    Customer* getCustomerByID(int id) 
    {
        for (int i = 0; i < numCustomers; i++) 
        {
            if (customers[i].getCustomerID() == id) 
            {
                return &customers[i];
            }
        }
        return nullptr;
    }

    Account* getAccountByNumber(int number) 
    {
        for (int i = 0; i < numAccounts; i++) 
        {
            if (accounts[i]->getAccountNumber() == number) 
            {
                return accounts[i];
            }
        }
        return nullptr;
    }

    void deposit(int number, double amount) 
    {
        Account* acc = getAccountByNumber(number);
        if (acc != nullptr) 
        {
            acc->deposit(amount);
        }
    }

    void withdraw(int number, double amount) 
    {
        Account* acc = getAccountByNumber(number);
        if (acc != nullptr) 
        {
            acc->withdraw(amount);
        }
    }

    void transfer(int from, int to, double amount) 
    {
        Account* accFrom = getAccountByNumber(from);
        Account* accTo = getAccountByNumber(to);
        if (accFrom != nullptr && accTo != nullptr) 
        {
            accFrom->withdraw(amount);
            accTo->deposit(amount);
        }
    }
    void displayDetail(int number) 
    {
        Account* acc = getAccountByNumber(number);
        if (acc != nullptr) 
        {
            cout << "Account number   : " << acc->getAccountNumber() << endl;
            cout << "Account balance  : " << acc->getAccountBalance() << endl;
        }
        else 
        {
            cout << "Account not found." << endl;
        }
    }

};

int main() {
    Bank bank;
    int choice = 0;

    while (true) 
    {
        cout << "1. Add customer" << endl;
        cout << "2. Add account" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. Transfer" << endl;
        cout << "6. Display Data" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice (1-6) : ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            int id;
            string name, contact;

            cout << "Enter customer ID      : ";
            cin >> id;
            cout << "Enter customer name    : ";
            cin >> name;
            cout << "Enter customer contact : ";
            cin >> contact;

            Customer c(id, name, contact);
            bank.addCustomer(c);

            cout << "Customer added successfully" << endl;
            break;
        }
        case 2: {
            int type, number;
            double balance, rate, minBalance;
            Customer* customer;

            cout << "Enter account type \n(1 - Savings, 2 - Current) : ";
            cin >> type;
            cout << "Enter account number   : ";
            cin >> number;
            cout << "Enter account balance  : ";
            cin >> balance;
            cout << "Enter customer ID      : ";
            int id;
            cin >> id;
            customer = bank.getCustomerByID(id);
            if (customer == nullptr) {
                cout << "Customer not found" << endl;
                break;
            }
            if (type == 1)
            {
                cout << "Enter interest rate: ";
                cin >> rate;
                SavingsAccount s(number, balance, rate, 100);
                bank.addAccount(&s);
            }
            else if (type == 2)
            {
                cout << "Enter minimum balance: ";
                cin >> minBalance;
                CurrentAccount c(number, balance, minBalance, 100);
                bank.addAccount(&c);
            }
            else
            {
                cout << "Invalid account type" << endl;
            }

            cout << "Account added successfully" << endl;
            break;
        }
        case 3:
        {
            int number;
            double amount;

            cout << "Enter account number  : ";
            cin >> number;
            cout << "Enter deposit amount  : ";
            cin >> amount;

            bank.deposit(number, amount);

            cout << "Deposit successful" << endl;
            break;
        }
        case 4: 
        {
            int number;
            double amount;

            cout << "Enter account number   : ";
            cin >> number;
            cout << "Enter withdraw amount  : ";
            cin >> amount;

            bank.withdraw(number, amount);

            cout << "Withdrawal successful" << endl;
            break;
        }
        case 5: 
        {
            int from, to;
            double amount;

            cout << "Enter account number to transfer from  : ";
            cin >> from;
            cout << "Enter account number to transfer to    : ";
            cin >> to;
            cout << "Enter transfer amount                  : ";
            cin >> amount;

            bank.transfer(from, to, amount);

            cout << "Transfer successful" << endl;
            break;
        }
        case 6:
        {
            int number;

            cout << "Enter account number   : ";
            cin >> number;
            bank.displayDetail(number);
            break;
        }
        case 0:
        {
            return 0;
        }
        }
        system("Pause");
        system("cls");
    }
}
