// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include "Account.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
#include "serializable.h"
using namespace std;

// Two Public Variables that maintain the execution traces and if the trace is turned on or off
vector<string> traces;
bool toggle = false;

void loadMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
void saveMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
void startMenu(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
void validate(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
void optionMenu(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void choiceValidate(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element, int choice);

int main()
{
	string username, password;

	vector<Client> clients;
	vector<Manager> managers;
	vector<Maintainer> maintainers;
	loadMembers(clients, managers, maintainers);

	Serializable objSerial;
	toggle = objSerial.loadTrace(traces);

	startMenu(username, password, clients, managers, maintainers);

	return 0;
}

void loadMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	Serializable memberSerial;
	clients.clear();
	clients = memberSerial.loadClients();
	managers.clear();
	managers = memberSerial.loadManagers();
	maintainers.clear();
	maintainers = memberSerial.loadMaintainers();
}

void saveMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	Serializable memberSerial;
	memberSerial.saveClients(clients);
	memberSerial.saveManagers(managers);
	memberSerial.saveMaintainers(maintainers);
}

void addTrace(string trace)
{
	if (toggle)
	{
		// Get the starting value of clock
		clock_t start = clock();
		tm* my_time;
		// Get current time in format of time_t
		time_t t = time(NULL);
		// Convert time_t to char*, and charTime will be the current time
		// Need to put in the header something to ignore the error for ctime
		char* charTime = ctime(&t);

		traces.push_back(trace + "\t" + charTime);
		Serializable objSerial;
		objSerial.saveTrace(traces, toggle);
	}
}

void startMenu(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                             Welcome To PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please login to your account to begin." << endl;
	cout << " Username: ";
	cin >> username;
	cout << " Password: ";
	cin >> password;
	cout << endl;
	validate(username, password, clients, managers, maintainers);
}

void validate(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                           Searching For Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	bool found = false;

	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].getUsername() == username && clients[i].getPassword() == password)
		{
			found = true;
			cout << " We have found your account, " << clients[i].getFirstname() << " " << clients[i].getLastname() << "." << endl << endl;
			addTrace(" " + clients[i].getUsername() + " successfully logged into PR Bank");
			optionMenu(username, password, clients, managers, maintainers, "client", i);
		}
	}

	if (!found)
	{
		for (size_t i = 0; i < managers.size(); i++)
		{
			if (managers[i].getUsername() == username && managers[i].getPassword() == password)
			{
				found = true;
				cout << " We have found your account, " << managers[i].getFirstname() << " " << managers[i].getLastname() << "." << endl << endl;
				addTrace(" " + managers[i].getUsername() + " successfully logged into PR Bank");
				optionMenu(username, password, clients, managers, maintainers, "manager", i);
			}
		}
	}

	if (!found)
	{
		for (size_t i = 0; i < maintainers.size(); i++)
		{
			if (maintainers[i].getUsername() == username && maintainers[i].getPassword() == password)
			{
				found = true;
				cout << " We have found your account, " << maintainers[i].getFirstname() << " " << maintainers[i].getLastname() << "." << endl << endl;
				addTrace(" " + maintainers[i].getUsername() + " successfully logged into PR Bank");
				optionMenu(username, password, clients, managers, maintainers, "maintainer", i);
			}
		}
	}

	if (!found)
	{
		cout << " Sorry, we were unable to find your account. Going back to main menu...\n" << endl;
		startMenu(username, password, clients, managers, maintainers);
	}
}

void optionMenu(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                                Main Menu\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please select an option from below:" << endl;
	cout << " 1. Print Account Summary" << endl;
	cout << " 2. Withdraw Funds" << endl;
	cout << " 3. Deposit Funds" << endl;
	cout << " 4. Transfer Funds" << endl;
	cout << " 5. Print Recent Transactions" << endl;
	cout << " 6. Quit\n" << endl;

	if (type == "manager")
	{
		cout << " Additional Manager Options:" << endl;
		cout << " 7. Create New Member" << endl;
		cout << " 8. Open Account" << endl;
		cout << " 9. Close Account" << endl;
		cout << " 10. View Details of Account(s)\n" << endl;
	}

	if (type == "maintainer")
	{
		cout << " Additional Maintenance Options" << endl;
		cout << " 7. Turn On Execution Trace" << endl;
		cout << " 8. Turn Off Execution Trace" << endl;
		cout << " 9. Print Execution Trace\n" << endl;
	}

	cout << " How would you like to proceed: ";
	int choice = 0;
	bool inputFail;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (type == "client")
		{
			if (choice <= 0 || choice >= 7)
				inputFail = true;
		}
		else if (type == "manager")
		{
			if (choice <= 0 || choice >= 11)
				inputFail = true;
		}
		else if (type == "maintainer")
		{
			if (choice <= 0 || choice >= 10)
				inputFail = true;
		}
	} while (inputFail == true);

	cout << endl;

	choiceValidate(username, password, clients, managers, maintainers, type, element, choice);
}

void choiceValidate(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element, int choice)
{
	double value = 0;
	bool inputFail;
	vector<string> transactions;

	switch (choice)
	{
		case 1:
			// Print Account Summary
			if (type == "client")
				clients[element].printAccount();
			else if (type == "manager")
				managers[element].printAccount();
			else if (type == "maintainer")
				maintainers[element].printAccount();

			addTrace(" " + username + " printed a summary of their accounts");
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 2:
			// Withdraw Money From Account
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Please enter a value you would like to withdraw: $";
			do
			{
				cin >> value;
				inputFail = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (inputFail == true);

			if (type == "client")
			{
				Account *account = clients[element].selectAccount("withdraw from");
				account->withdraw(value);
				clients[element].addTransaction(clients[element].getFirstname() + " withdrew $" + to_string(value) + " from " + account->getAccountType());
			}
			else if (type == "manager")
			{
				Account *account = managers[element].selectAccount("withdraw from");
				account->withdraw(value);
				managers[element].addTransaction(managers[element].getFirstname() + " withdrew $" + to_string(value) + " from " + account->getAccountType());
			}
			else if (type == "maintainer")
			{
				Account *account = maintainers[element].selectAccount("withdraw from");
				account->withdraw(value);
				maintainers[element].addTransaction(maintainers[element].getFirstname() + " withdrew $" + to_string(value) + " from " + account->getAccountType());
			}

			cout << endl;
			addTrace(" " + username + " withdrew money from their account");
			saveMembers(clients, managers, maintainers);
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 3:
			// Deposit Money To Account
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Please enter a value you would like to deposit: $";
			do
			{
				cin >> value;
				inputFail = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (inputFail == true);

			if (type == "client")
			{
				Account *account = clients[element].selectAccount("deposit to");
				account->deposit(value);
				clients[element].addTransaction(clients[element].getFirstname() + " deposited $" + to_string(value) + " to " + account->getAccountType());
			}
			else if (type == "manager")
			{
				Account *account = managers[element].selectAccount("deposit to");
				account->deposit(value);
				managers[element].addTransaction(managers[element].getFirstname() + " deposited $" + to_string(value) + " to " + account->getAccountType());
			}
			else if (type == "maintainer")
			{
				Account *account = maintainers[element].selectAccount("deposit to");
				account->deposit(value);
				maintainers[element].addTransaction(maintainers[element].getFirstname() + " deposited $" + to_string(value) + " to " + account->getAccountType());
			}

			cout << endl;
			addTrace(" " + username + " deposited money into their account");
			saveMembers(clients, managers, maintainers);
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 4:
			// Transfer Money To Account
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Please enter a value you would like to transfer: $";
			do
			{
				cin >> value;
				inputFail = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (value <= 0)
					inputFail = true;
			} while (inputFail == true);

			if (type == "client")
			{
				Account *account1 = clients[element].selectAccount("transfer from");
				Account *account2 = clients[element].selectAccount("transfer to");
				account1->transfer(value, account2);
				clients[element].addTransaction(clients[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + account2->getAccountType());
			}
			else if (type == "manager")
			{
				Account *account1 = managers[element].selectAccount("transfer from");
				Account *account2 = managers[element].selectAccount("transfer to");
				account1->transfer(value, account2);
				managers[element].addTransaction(managers[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + account2->getAccountType());
			}
			else if (type == "maintainer")
			{
				Account *account1 = maintainers[element].selectAccount("transfer from");
				Account *account2 = maintainers[element].selectAccount("transfer to");
				account1->transfer(value, account2);
				maintainers[element].addTransaction(maintainers[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + account2->getAccountType());
			}

			cout << endl;
			addTrace(" " + username + " transferred money between their accounts");
			saveMembers(clients, managers, maintainers);
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 5:
			// Print Recent Transactions
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Here are your most recent transactions: \n" << endl;

			if (type == "client")
				transactions = clients[element].getTransactions();
			else if (type == "manager")
				transactions = managers[element].getTransactions();
			else if (type == "maintainer")
				transactions = maintainers[element].getTransactions();

			for (size_t i = 0; i < transactions.size(); i++)
			{
				cout << " " << i + 1 << ". " << transactions[i] << endl;
			}

			if (transactions.empty())
				cout << " Sorry, you do not have any recent transactions." << endl;

			cout << endl;
			addTrace(" " + username + " printed their recent transactions");
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 6:
			// Log out
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Logging out, thank you for choosing PR Bank.\n" << endl;
			addTrace(" " + username + " logged out of PR Bank");
			startMenu(username, password, clients, managers, maintainers);
			break;

		case 7:
			// Create New Member if you are a Manager
			if (type == "manager")
			{
				int selection = managers[element].createMember();

				if (selection == 1)
				{
					Client client = managers[element].initializeClient();
					clients.push_back(client);
					client.printAccount();
					addTrace(" " + username + " added " + client.getUsername() + " to PR Bank");
				}
				else if (selection == 2)
				{
					Manager manager = managers[element].initializeManager();
					managers.push_back(manager);
					manager.printAccount();
					addTrace(" " + username + " added " + manager.getUsername() + " to PR Bank");
				}
				else if (selection == 3)
				{
					Maintainer maintainer = managers[element].initializeMaintainer();
					maintainers.push_back(maintainer);
					maintainer.printAccount();
					addTrace(" " + username + " added " + maintainer.getUsername() + " to PR Bank");
				}
				saveMembers(clients, managers, maintainers);
			}

			// Turn Execution Trace on if you are a Maintainer
			if (type == "maintainer")
			{
				if (toggle)
					cout << " The execution trace function is alreayd turned on.\n" << endl;
				else
				{
					toggle = true;
					cout << " You have turned the execution trace function on.\n" << endl;
					addTrace(" " + username + " turned the execution trace on");
				}
			}

			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 8:
			// Open Account if you are a Manager
			if (type == "manager")
			{
				string accountHolder = managers[element].openAccount(clients, managers, maintainers);
				addTrace(" " + username + accountHolder);
				saveMembers(clients, managers, maintainers);
			}

			// Turn Execution Trace off if you are a Maintainer
			if (type == "maintainer")
			{
				if (toggle == false)
					cout << " The execution trace function is already turned off.\n" << endl;
				else
				{
					toggle = false;
					cout << " You have turned the execution trace function off.\n" << endl;
					addTrace(" " + username + " turned the execution trace off");
				}
			}

			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 9:
			// Close Account if you are a Manager
			if (type == "manager")
			{
				string accountHolder = managers[element].closeAccount(clients, managers, maintainers);
				addTrace(" " + username + accountHolder);
				saveMembers(clients, managers, maintainers);
			}

			//Print Execution Trace if you are a Maintainer
			if (type == "maintainer")
			{
				maintainers[element].printTrace();
				addTrace(" " + username + " printed the execution trace");
			}

			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 10:
			// View Details of Accounts if you are a Manager
			if (type == "manager")
			{
				managers[element].viewDetails(clients, managers, maintainers);
				addTrace(" " + username + " viewed details of accounts");
				optionMenu(username, password, clients, managers, maintainers, type, element);
			}
			break;

		default:
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " INTERNAL ERROR: Returning to main menu...\n" << endl;
			addTrace(" " + username + " encountered an error while using PR Bank");
			startMenu(username, password, clients, managers, maintainers);
	}
}
