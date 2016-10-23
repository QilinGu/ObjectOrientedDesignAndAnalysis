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

void printSummary(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void withdrawMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void depositMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void transferMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void transferMoneyToMember(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void printRecentTransactions(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void createMember(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void createAutoPayment(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void cancelAutoPayment(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element);
void calculatePayment(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
double getValue();

int main()
{
	// Create most of the variables that will be passed through menu functions
	string username, password;

	vector<Client> clients;
	vector<Manager> managers;
	vector<Maintainer> maintainers;
	// Load bank members into their corresponding vectors
	loadMembers(clients, managers, maintainers);

	// Load the traces
	Serializable objSerial;
	toggle = objSerial.loadTrace(traces);

	// Go to start menu!
	startMenu(username, password, clients, managers, maintainers);

	return 0;
}

/**
 * \brief 
 * Load Members Function
 * Make sure all vectors are empty before loading their contents 
 * Use of loadMembers function from serilization class to load members
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void loadMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	Serializable memberSerial;
	clients.clear();
	memberSerial.loadMembers(clients, "clients.pr");
	managers.clear();
	memberSerial.loadMembers(managers, "managers.pr");
	maintainers.clear();
	memberSerial.loadMembers(maintainers, "maintainers.pr");
}

/**
 * \brief 
 * Save Members Function
 * Uses serialization class to save members
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void saveMembers(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	Serializable memberSerial;
	memberSerial.saveMembers(clients, "clients.pr");
	memberSerial.saveMembers(managers, "managers.pr");
	memberSerial.saveMembers(maintainers, "maintainers.pr");
}

/**
 * \brief 
 * Add Trace Function
 * Simply adds a new trace with a time stamp when called
 * \param trace 
 */
void addTrace(string trace)
{
	if (toggle)
	{
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

/**
 * \brief 
 * Start Menu Function
 * Prompts the user to enter their username and password
 * Called validate function to check if they are a member
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
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

/**
 * \brief 
 * Validate Function
 * Checks to see if the users input corresponds to an existing account
 * If they are, continue to the options menu
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
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

/**
 * \brief 
 * Option Menu Function
 * Depending on the type of member, they will be supplied with a number of options
 * There option will be sent to the Choice Validate Function
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void optionMenu(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	calculatePayment(clients, managers, maintainers);

	cout << "--------------------------------------------------------------------------\n";
	cout << "                                Main Menu\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please select an option from below:" << endl;
	cout << " 1. Print Account Summary" << endl;
	cout << " 2. Withdraw Funds" << endl;
	cout << " 3. Deposit Funds" << endl;
	cout << " 4. Transfer Funds" << endl;
	cout << " 5. Transfer Funds To Another Member" << endl;
	cout << " 6. Print Recent Transactions" << endl;
	cout << " 7. Create Automatic Payment" << endl;
	cout << " 8. Cancel Automatic Payment" << endl;
	cout << " 9. Quit\n" << endl;

	if (type == "manager")
	{
		cout << " Additional Manager Options:" << endl;
		cout << " 10. Create New Member" << endl;
		cout << " 11. Add Account" << endl;
		cout << " 12. Close Account" << endl;
		cout << " 13. View Details of Account(s)\n" << endl;
	}

	if (type == "maintainer")
	{
		cout << " Additional Maintenance Options" << endl;
		cout << " 10. Turn On Execution Trace" << endl;
		cout << " 11. Turn Off Execution Trace" << endl;
		cout << " 12. Print Execution Trace\n" << endl;
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
			if (choice <= 0 || choice >= 10)
				inputFail = true;
		}
		else if (type == "manager")
		{
			if (choice <= 0 || choice >= 14)
				inputFail = true;
		}
		else if (type == "maintainer")
		{
			if (choice <= 0 || choice >= 13)
				inputFail = true;
		}
	} while (inputFail == true);

	cout << endl;

	choiceValidate(username, password, clients, managers, maintainers, type, element, choice);
}

/**
 * \brief 
 * Choice Validate Function
 * Takes the members inputted choice and runs it through a switch case that corresponds to their input
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 * \param choice 
 */
void choiceValidate(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element, int choice)
{
	switch (choice)
	{
		case 1:
			printSummary(username, password, clients, managers, maintainers, type, element);
			break;
		case 2:
			withdrawMoney(username, password, clients, managers, maintainers, type, element);
			break;
		case 3:
			depositMoney(username, password, clients, managers, maintainers, type, element);
			break;
		case 4:
			transferMoney(username, password, clients, managers, maintainers, type, element);
			break;
		case 5:
			transferMoneyToMember(username, password, clients, managers, maintainers, type, element);
			break;
		case 6:
			printRecentTransactions(username, password, clients, managers, maintainers, type, element);
			break;
		case 7:
			createAutoPayment(username, password, clients, managers, maintainers, type, element);
			break;
		case 8:
			cancelAutoPayment(username, password, clients, managers, maintainers, type, element);
			break;
		case 9:
			// Log out
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Logging out, thank you for choosing PR Bank.\n" << endl;
			addTrace(" " + username + " logged out of PR Bank");
			startMenu(username, password, clients, managers, maintainers);
			break;
		case 10:
			// Create New Member if you are a Manager
			if (type == "manager")
			{
				createMember(username, password, clients, managers, maintainers, type, element);
			}

			// Turn Execution Trace on if you are a Maintainer
			if (type == "maintainer")
			{
				if (toggle)
					cout << " The execution trace function is already turned on.\n" << endl;
				else
				{
					toggle = true;
					cout << " You have turned the execution trace function on.\n" << endl;
					addTrace(" " + username + " turned the execution trace on");
				}
			}
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;
		case 11:
			// Add Account if you are a Manager
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
					addTrace(" " + username + " turned the execution trace off");
					toggle = false;
					cout << " You have turned the execution trace function off.\n" << endl;
				}
			}
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;
		case 12:
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
				addTrace(" " + username + " printed the execution trace");
				maintainers[element].printTrace();
			}
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;
		case 13:
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

/**
 * \brief 
 * Print Summary Function
 * Prints an account summary to the logged in user
 * Return back to the option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void printSummary(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Print Account Summary
	if (type == "client")
		clients[element].printAccount();
	else if (type == "manager")
		managers[element].printAccount();
	else if (type == "maintainer")
		maintainers[element].printAccount();

	addTrace(" " + username + " printed a summary of their accounts");
	optionMenu(username, password, clients, managers, maintainers, type, element);
}

/**
 * \brief 
 * Withdraw Money Function
 * User selects the accounts they would like to withdraw from 
 * Calls withdraw function from account to withdraw money
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void withdrawMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Withdraw Money From Account
	cout << "--------------------------------------------------------------------------\n\n";
	cout << " Please enter a value you would like to withdraw: $";
	double value = getValue();

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
}

/**
 * \brief 
 * Deposit Money Function
 * User selects the accounts they would like to deposit to
 * Calls deposit function from account to deposit money
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void depositMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Deposit Money To Account
	cout << "--------------------------------------------------------------------------\n\n";
	cout << " Please enter a value you would like to deposit: $";
	double value = getValue();

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
}

/**
 * \brief 
 * Transfer Money Function
 * User selects the accounts they would like to transfer to 
 * Calls transfer function from account to transfer money
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void transferMoney(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Transfer Money To Account
	cout << "--------------------------------------------------------------------------\n\n";
	cout << " Please enter a value you would like to transfer: $";
	double value = getValue();

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
}

/**
 * \brief 
 * Transfer Money To Member Function
 * User selects the accounts they would like to withdraw from 
 * User selects the users account they would like to deposit to
 * Calls transfer function from account to transfer money
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void transferMoneyToMember(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Transfer Money To Another Member
	double value = 0;
	string memberName;
	Account *account1 = NULL;
	Account *account2 = NULL;

	cout << "--------------------------------------------------------------------------\n\n";
	cout << " Please enter a value you would like to transfer: $";
	value = getValue();
	cout << " What is the username of the member you wish to transfer to: ";
	cin >> memberName;

	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getUsername() == memberName)
			account2 = clients[i].selectAccount("transfer to");
	if (account2 == NULL)
		for (size_t i = 0; i < managers.size(); i++)
			if (managers[i].getUsername() == memberName)
				account2 = managers[i].selectAccount("transfer to");
	if (account2 == NULL)
		for (size_t i = 0; i < maintainers.size(); i++)
			if (maintainers[i].getUsername() == memberName)
				account2 = maintainers[i].selectAccount("transfer to");

	if (account2 == NULL)
		cout << "\n Sorry, we can not find the member matching that username.\n" << endl;
	else
	{
		if (type == "client")
		{
			account1 = clients[element].selectAccount("transfer from");
			clients[element].addTransaction(clients[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + username + "'s" + account2->getAccountType());
		}
		else if (type == "manager")
		{
			account1 = managers[element].selectAccount("transfer from");
			managers[element].addTransaction(managers[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + username + "'s" + account2->getAccountType());
		}
		else if (type == "maintainer")
		{
			account1 = maintainers[element].selectAccount("transfer from");
			maintainers[element].addTransaction(maintainers[element].getFirstname() + " transfered $" + to_string(value) + " from " + account1->getAccountType() + " to " + username + "'s" + account2->getAccountType());
		}

		account1->transfer(value, account2);
		cout << endl;
		addTrace(" " + username + " transferred money between " + memberName + "'s accounts");
		saveMembers(clients, managers, maintainers);
	}

	optionMenu(username, password, clients, managers, maintainers, type, element);
}

/**
 * \brief 
 * Print Recent Transaction Function
 * Prints the users (at most 10) recent transactions
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void printRecentTransactions(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	// Print Recent Transactions
	vector<string> transactions;
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
}

/**
 * \brief 
 * Create Member Function
 * Manager utilizes this function to create a new member
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void createMember(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	int selection = managers[element].chooseMemberType();

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

/**
 * \brief 
 * Create Automatic Payment Function
 * Creates an automatic payment for the user
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void createAutoPayment(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	cout << "--------------------------------------------------------------------------\n\n";
	cout << " What would you like to name this automatic payment to be: ";
	string payment;
	cin >> payment;
	cout << " Please enter a value to be automatically withdrawn: $";

	double value = 0;
	while (value <= 0)
		value = getValue();

	if (type == "client")
		clients[element].addPayment(payment, value);
	else if (type == "manager")
		managers[element].addPayment(payment, value);
	else if (type == "maintainer")
		maintainers[element].addPayment(payment, value);

	optionMenu(username, password, clients, managers, maintainers, type, element);
}

/**
 * \brief 
 * Cancel Automatic Payment Function
 * Cancels a users desired automatic payment
 * Returns to option menu when finished
 * \param username 
 * \param password 
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \param type 
 * \param element 
 */
void cancelAutoPayment(string &username, string &password, vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers, string type, int element)
{
	cout << "--------------------------------------------------------------------------\n\n";
	cout << " Here are your current automatic payments:\n";

	vector<Account> payments;

	if (type == "client")
		payments = clients[element].getPayments();
	else if (type == "manager")
		payments = managers[element].getPayments();
	else if (type == "maintainer")
		payments = maintainers[element].getPayments();

	if (payments.size() > 0)
	{
		for (size_t i = 0; i < payments.size(); i++)
			cout << " " << payments[i].getAccountType() << endl;

		cout << "\n What is the name of the payment you would like to cancel: ";
		string payment;
		cin >> payment;

		bool found = false;

		if (type == "client")
			found = clients[element].cancelPayment(payment);
		else if (type == "manager")
			found = managers[element].cancelPayment(payment);
		else if (type == "maintainer")
			found = maintainers[element].cancelPayment(payment);

		if (!found)
			cout << "\n Sorry, we could not find a payment with that name." << endl;
		else
			cout << "\n The payment, " << payment << ", has been canceled." << endl;
	}
	else
		cout << "\n Currently, you have no automatic payments set up.\n" << endl;

	optionMenu(username, password, clients, managers, maintainers, type, element);
}

/**
 * \brief 
 * Calculate Payment Function
 * Goes through all members to see if the have any automatic payments, loans or credit accounts to charge them
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void calculatePayment(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	for (size_t i = 0; i < clients.size(); i++)
		clients[i].checkPayment();
	for (size_t i = 0; i < managers.size(); i++)
		managers[i].checkPayment();
	for (size_t i = 0; i < maintainers.size(); i++)
		maintainers[i].checkPayment();

	saveMembers(clients, managers, maintainers);
}

/**
 * \brief 
 * Get Value Function
 * Returns an double used for input
 * \return 
 */
double getValue()
{
	double value = 0;
	bool inputFail;
	do
	{
		cin >> value;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (inputFail == true);

	return value;
}
