#include <iostream>
#include <string>

using namespace std;

class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNum = 0, string accHoldername = "", double bal = 0)
    {
        accountNumber = accNum;
        accountHolderName = accHoldername;
        balance = bal;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Amount Deposited Successfully!" << endl;
    }

    virtual void withdraw(double amount)
    {
        if (balance > amount)
        {
            balance -= amount;
            cout << "Amount Withdraw Successfully!" << endl;
        }
        else
        {
            cout << "Amount is not sufficient for Withdrawal!" << endl;
        }
    }

    virtual void displayAccountInfo()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Balance: " << balance << endl;
    }

    double getBalance()
    {
        return balance;
    }

    virtual double calculateInterest()
    {
        return 0;
    }

    virtual ~BankAccount() {};
};

class SavingAccount : public BankAccount
{
    double interestRate;

public:
    SavingAccount(int accNum = 0, string accHoldername = "", double bal = 0, double ir = 0) : BankAccount(accNum, accHoldername, bal)
    {
        interestRate = ir;
    }
    double calculateInterest()
    {
        return balance * interestRate / 100;
    }
    void displayAccountInfo()
    {
        double totalBal = balance + calculateInterest();

        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Balance: " << balance << endl;
        cout << "Account total Balance(with interestl): " << totalBal << endl;
    }
    double getbalance()
    {
        return balance + calculateInterest();
    }
};

class CheckingAccount : public BankAccount
{
    double overdraftLimit;

public:
    CheckingAccount(int accNum = 0, string accHoldername = "", double bal = 0, double odLimit = 0) : BankAccount(accNum, accHoldername, bal)
    {
        overdraftLimit = odLimit;
    }

    void withdraw(double amount)
    {
        if (amount <= balance + overdraftLimit)
        {
            balance -= amount;
            cout << "Withdraw Successfully..." << endl;
        }
        else
        {
            cout << "Amount is more then balance can't widthdraw...." << endl;
        }
    }

    double calculateInterest()
    {
        return 0;
    }
};

class FixedDepositAccount : public BankAccount
{
    int month;

public:
    FixedDepositAccount(int accNum = 0, string accHoldername = "", double bal = 0, int month = 0) : BankAccount(accNum, accHoldername, bal)
    {
        this->month = month;
    }

    double calculateInterest()
    {
        double rate = 7.5;
        return (balance * rate * month) / (100 * 12);
    }
    void displayAccountInfo()
    {
        double totalBalance = balance + calculateInterest();

        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account total Balance: " << totalBalance << endl;
    }
    double getBalance()
    {
        return balance + calculateInterest();
    }
    void deposit(double amount)
    {
        cout<< endl << "Deposit NOT allowed in Fixed Deposit Account!" << endl;
    }
    void withdraw(double amount)
    {
        cout<< endl << "Withdrawal NOT allowed in Fixed Deposit Account!" << endl;
    }
};

int main()
{
    BankAccount *acc;
    SavingAccount sa;
    CheckingAccount ca;
    FixedDepositAccount fda;

    int chooseAcc, choice;

    do
    {
        cout << endl
             << "Choose Account Type: " << endl;
        cout << " 1 for Saving Account." << endl;
        cout << " 2 for Checking Account." << endl;
        cout << " 3 for Fixed Deposit Account." << endl;
        cout << " 4 for Exit." << endl;
        cout << endl
             << "Enter your choice: ";
        cin >> chooseAcc;

        if (chooseAcc == 4)
        {
            cout << "Thank you for visiting..." << endl;
            break;
        }

        if (chooseAcc > 4)
        {
            cout << "Invalid Choice!!!" << endl;
            continue;
        }

        int accNum;
        string name;
        double bal;

        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Enter Account Holder Name: ";
        cin >> name;
        cout << "Enter Initial Balance: ";
        cin >> bal;

        if (chooseAcc == 1)
        {
            double interestRate;
            cout << "Enter Interest rate: ";
            cin >> interestRate;

            sa = SavingAccount(accNum, name, bal, interestRate);
            acc = &sa;
        }
        else if (chooseAcc == 2)
        {
            double odLimit;
            cout << "Enter Overdraft Limit: ";
            cin >> odLimit;

            ca = CheckingAccount(accNum, name, bal, odLimit);
            acc = &ca;
        }
        else if (chooseAcc == 3)
        {
            int months;
            cout << "Enter Fixed deposit months: ";
            cin >> months;

            fda = FixedDepositAccount(accNum, name, bal, months);
            acc = &fda;
        }

        do
        {
            cout << endl
                 << "Choose Account Operation: " << endl;
            cout << " 1 for Deposit." << endl;
            cout << " 2 for Withdraw." << endl;
            cout << " 3 for check balance." << endl;
            cout << " 4 for Calculate interest." << endl;
            cout << " 5 for Exit." << endl;
            cout << endl
                 << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                int depositAmount;

                if (chooseAcc == 3)
                {
                    acc->deposit(depositAmount);
                }
                else
                {
                    cout << "Enter Deposit Amount: ";
                    cin >> depositAmount;
                    acc->deposit(depositAmount);
                }

                break;

            case 2:
                int withdrawAmount;

                if(chooseAcc == 3)
                {
                    acc->withdraw(withdrawAmount);
                }
                else
                {
                    cout << "Enter withrawal Amount: ";
                    cin >> withdrawAmount;
                    acc->withdraw(withdrawAmount);
                }

                break;

            case 3:
                acc->displayAccountInfo();
                break;

            case 4:
                cout << "Interest: " << acc->calculateInterest() << endl;
                break;

            case 5:
                cout << endl
                     << "Thank you for visiting." << endl;
                break;

            default:
                cout << endl
                     << "Invalid number!!!" << endl;
            }
        } while (choice != 5);

    } while (true);

    return 0;
}