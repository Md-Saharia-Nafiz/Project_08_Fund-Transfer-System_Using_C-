#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Base class for Bank Account
class BankAccount
{
protected:
    string bankName;
    string accountName;
    long long accountNumber;
    double balance;
    double interestRate; // For saving account
public:
    BankAccount(string bName, string aName, long long aNumber, double bal, double rate = 0.0)
    {
        bankName = bName;
        accountName = aName;
        accountNumber = aNumber;
        balance = bal;
        interestRate = rate;
    }

    // Show account details
    void showBalance()
    {
        cout << "Bank: " << bankName << endl;
        cout << "Account Name: " << accountName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << " BDT" << endl;
        cout << "Interest_Rate: " << interestRate << "%" << endl << endl;
    }

    // Deposit money
    void deposit(double amount)
    {
        balance += amount;
        cout << amount << " BDT deposited successfully!!" << endl;
        logTransaction("Deposit", amount);
    }

    // Withdraw money
    bool withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            cout << amount << " BDT withdrawn successfully!" << endl;
            logTransaction("Withdraw", amount);
            return true;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
    }

    // Transfer money
    bool transfer(BankAccount &receiver, double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            receiver.balance += amount;
            cout << "The Fund transfer has been completed successfully!" << endl;
            logTransaction("Transfer to " + receiver.accountName, amount);
            receiver.logTransaction("Received from " + accountName, amount);
            return true;
        }
        else
        {
            cout << "Sorry, you do not have enough funds for this transfer." << endl;
            return false;
        }
    }

    // Calculate interest (for saving account)
    void calculateInterest()
    {
        if (interestRate > 0)
        {
            double interest = balance * interestRate / 100;
            cout << "Interest Amount: " << interest << " BDT" << endl;
            balance += interest;
            logTransaction("Interest Added", interest);
        }
    }

    // Getter for balance
    double getBalance()
    {
        return balance;
    }

    // Transaction log function (File Handling)
    void logTransaction(string type, double amount)
    {
        ofstream file;
        string fileName = to_string(accountNumber) + "_transactions.txt";
        file.open(fileName, ios::app); // Append mode
        if (file.is_open())
        {
            time_t now = time(0);
            char* dt = ctime(&now);
            file << dt << " | " << type << " | " << amount << " BDT | Balance: " << balance << " BDT" << endl;
            file.close();
        }
    }
};

// Bank App class
class BankApp
{
private:
    BankAccount* userAccount;
public:
    BankApp(BankAccount* acc)
    {
        userAccount = acc;
    }

    void checkBalance()
    {
        cout << "=== Checking Balance via App ===" << endl;
        userAccount->showBalance();
    }

    void depositMoney()
    {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        userAccount->deposit(amount);
    }

    void withdrawMoney()
    {
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        userAccount->withdraw(amount);
    }

    void transferMoney(BankAccount &receiver)
    {
        double amount;
        cout << "Enter amount to transfer to " << receiver.getBalance() << ": ";
        cin >> amount;
        userAccount->transfer(receiver, amount);
    }

    void addInterest()
    {
        userAccount->calculateInterest();
    }
};

int main()
{
    // Create accounts
    BankAccount myAccount("BRAC_Bank", "MD. SAHARIA NAFIZ 786", 20255103318, 70000, 5.0);
    BankAccount bigBrotherAccount("Bank_Asia_PLC", "MD. BAPPI 3785", 96873524491, 0);

    BankApp asthaApp(&myAccount);

    int choice;

    do
    {
        cout << "\n=== Welcome to Astha App (BRAC_Bank) ===" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Money to Big Brother" << endl;
        cout << "5. Add Interest" << endl;
        cout << "6. Exit" << endl;
        cout << "Please Enter your choice Number: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            asthaApp.checkBalance();
            break;
        case 2:
            asthaApp.depositMoney();
            break;
        case 3:
            asthaApp.withdrawMoney();
            break;
        case 4:
            asthaApp.transferMoney(bigBrotherAccount);
            break;
        case 5:
            asthaApp.addInterest();
            break;
        case 6:
            cout << "Thank you for using Astha App!" << endl;
            break;
        default:
            cout << "Invalid choice! Try again.." << endl;
        }

    }
    while(choice != 6);

    // Show final balances
    cout << "\n=== Final Balances ===" << endl;
    myAccount.showBalance();
    bigBrotherAccount.showBalance();

    return 0;
}
