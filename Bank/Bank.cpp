// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
#include "serializable.h"
using namespace std;

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
	startMenu(username, password, clients, managers, maintainers);

	/*int selection = managers[0].createMember();

	if (selection == 1)
	{
	Client client = managers[0].initializeClient();
	client.printAccount();
	}
	else if (selection == 2)
	{
	Manager manager = managers[0].initializeManager();
	manager.printAccount();
	}
	else if (selection == 3)
	{
	Maintainer maintainer = managers[0].initializeMaintainer();
	maintainer.printAccount();
	}*/

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
			optionMenu(username, password, clients, managers, maintainers, "client", i);
		}
	}

	for (size_t i = 0; i < managers.size(); i++)
	{
		if (managers[i].getUsername() == username && managers[i].getPassword() == password)
		{
			found = true;
			cout << " We have found your account, " << managers[i].getFirstname() << " " << managers[i].getLastname() << "." << endl << endl;
			optionMenu(username, password, clients, managers, maintainers, "manager", i);
		}
	}

	for (size_t i = 0; i < maintainers.size(); i++)
	{
		if (maintainers[i].getUsername() == username && maintainers[i].getPassword() == password)
		{
			found = true;
			cout << " We have found your account, " << maintainers[i].getFirstname() << " " << maintainers[i].getLastname() << "." << endl << endl;
			optionMenu(username, password, clients, managers, maintainers, "maintainer", i);
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
	cout << "                                 Main Menu\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please select an option from below:" << endl;
	cout << " 1. Check Balance" << endl;
	cout << " 2. Withdraw Funds" << endl;
	cout << " 3. Deposit Funds" << endl;
	cout << " 4. Transfer Funds" << endl;
	cout << " 5. Print Recent Transactions" << endl;
	cout << " 6. Quit\n" << endl;

	if (type == "manager")
	{
		cout << " Additional Manager Options:" << endl;
		cout << " 7. Open Account" << endl;
		cout << " 8. Close Account" << endl;
		cout << " 9. View Details of Account(s)\n" << endl;
	}

	if (type == "maintainer")
	{
		cout << " Additional Maintenance Options" << endl;
		cout << " 7. Turn On Execution Trace" << endl;
		cout << " 8. Turn Off Execution Trace\n" << endl;
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
			if (choice <= 0 || choice >= 10)
				inputFail = true;
		}
		else if (type == "maintainer")
		{
			if (choice <= 0 || choice >= 9)
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

	switch (choice)
	{
		case 1:
			// Print Account Balances
			if (type == "client")
				clients[element].printAccount();
			else if (type == "manager")
				managers[element].printAccount();
			else if (type == "maintainer")
				maintainers[element].printAccount();

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
				clients[element].selectAccount("withdraw from")->withdraw(value);
			else if (type == "manager")
				managers[element].selectAccount("withdraw from")->withdraw(value);
			else if (type == "maintainer")
				maintainers[element].selectAccount("withdraw from")->withdraw(value);

			cout << endl;
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
				clients[element].selectAccount("deposit to")->deposit(value);
			else if (type == "manager")
				managers[element].selectAccount("deposit to")->deposit(value);
			else if (type == "maintainer")
				maintainers[element].selectAccount("deposit to")->deposit(value);

			cout << endl;
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
				clients[element].selectAccount("transfer from")->transfer(value, clients[element].selectAccount("transfer to"));
			else if (type == "manager")
				managers[element].selectAccount("transfer from")->transfer(value, managers[element].selectAccount("transfer to"));
			else if (type == "maintainer")
				maintainers[element].selectAccount("transfer from")->transfer(value, maintainers[element].selectAccount("transfer to"));

			cout << endl;
			saveMembers(clients, managers, maintainers);
			optionMenu(username, password, clients, managers, maintainers, type, element);
			break;

		case 5:
			break;
		case 6:
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " Logging out, thank you for choosing PR Bank.\n" << endl;
			startMenu(username, password, clients, managers, maintainers);
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			cout << "--------------------------------------------------------------------------\n\n";
			cout << " INTERNAL ERROR: Returning to main menu...\n" << endl;
			startMenu(username, password, clients, managers, maintainers);
	}
}
