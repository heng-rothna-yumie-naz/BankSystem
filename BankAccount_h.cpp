#include <iostream>
#include "BankAcount.h"
using namespace std;

int main() {
    int n;
    cout << "Enter number of accounts: ";
    cin >> n;

    BankAccount* acc = new BankAccount[n];

    // Create accounts
    for (int i = 0; i < n; i++) {
        string name, accNo;
        float bal;
        cout << "\nAccount " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Account Number: ";
        cin >> accNo;
        cout << "Initial Balance: ";
        cin >> bal;
        acc[i].setData(name, accNo, bal);
    }

    int choice;
    do {
        cout << "\n====== BANK MENU ======\n";
        cout << "1. Show All Accounts\n";
        cout << "2. Search Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Update Holder Name\n";
        cout << "6. Transfer Money\n";
        cout << "7. Delete Account (reset data)\n";
        cout << "8. Total Balance of All Accounts\n";
        cout << "9. Add New Account\n";
        cout << "10. Exit\n";
        cout << "Choose option (1-10): ";
        cin >> choice;

        string accNum, accTo;
        float amount;
        bool found = false;

        switch (choice) {
            case 1:{ // Show all
                for (int i = 0; i < n; i++) {
                    cout << "\n--- Account " << i + 1 << " ---\n";
                    acc[i].showData();
                }
                break;
            }

            case 2:{// Search
                cout << "Enter account number to search: ";
                cin >> accNum;
                found = false;
                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum) {
                        acc[i].showData();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Account not found!\n";
                break;
            }

            case 3:{// Deposit
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount: ";
                cin >> amount;
                found = false;
                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum) {
                        acc[i].deposit(amount);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Account not found!\n";
                break;
            }

            case 4: {// Withdraw
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount: ";
                cin >> amount;
                found = false;
                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum) {
                        acc[i].withdraw(amount);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Account not found!\n";
                break;
            }

            case 5:{ // Update name
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter new name: ";
                cin >> ws;
                getline(cin, accTo);  // reusing accTo as new name
                found = false;
                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum) {
                        acc[i].updateName(accTo);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Account not found!\n";
                break;
            }

            case 6:{// Transfer (simplified using index)
                cout << "From account: ";
                cin >> accNum;
                cout << "To account: ";
                cin >> accTo;
                cout << "Amount: ";
                cin >> amount;

                int fromIndex = -1, toIndex = -1;

                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum)
                        fromIndex = i;
                    if (acc[i].getAccNum() == accTo)
                        toIndex = i;
                }

                if (fromIndex != -1 && toIndex != -1) {
                    if (amount <= acc[fromIndex].getBalance()) {
                        acc[fromIndex].withdraw(amount);
                        acc[toIndex].deposit(amount);
                        cout << "Transfer successful!\n";
                    } else {
                        cout << "Not enough balance to transfer!\n";
                    }
                } else {
                    cout << "One or both accounts not found!\n";
                }
                break;
				}

            case 7:{// Delete (reset)
                cout << "Enter account number to delete: ";
                cin >> accNum;
                found = false;
                for (int i = 0; i < n; i++) {
                    if (acc[i].getAccNum() == accNum) {
                        acc[i].setData("NULL", "000", 0);
                        cout << "Account deleted (reset).\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Account not found!\n";
                break;
            }

            case 8:{ // Total balance
                {
                    float total = 0;
                    for (int i = 0; i < n; i++) {
                        total += acc[i].getBalance();
                    }
                    cout << "Total balance in bank: $" << total << "\n";
                }
                break;
            }

            case 9:{// Add new account
                {
                    BankAccount* temp = new BankAccount[n + 1];
                    for (int i = 0; i < n; i++)
                        temp[i] = acc[i];

                    string name, accNo;
                    float bal;
                    cout << "New account name: ";
                    cin >> ws;
                    getline(cin, name);
                    cout << "Account number: ";
                    cin >> accNo;
                    cout << "Initial balance: ";
                    cin >> bal;
                    temp[n].setData(name, accNo, bal);

                    delete[] acc;
                    acc = temp;
                    n++;

                    cout << "New account added.\n";
                }
                break;
            }

            case 10:{
                cout << "Goodbye!\n";
                break;
            }

            default:
                cout << "Invalid option!\n";
        }

    } while (choice != 10);

    delete[] acc;
    return 0;
}

