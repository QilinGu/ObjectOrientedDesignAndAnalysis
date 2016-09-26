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
void optionMenu(string &username, string &password, vector<Member> &vMember, Member &member);
void choiceValidate(int &choice, string &username, string &password, vector<Member> &vMember, Member &member);

int main()
{
	vector<Client> clients;
	vector<Manager> managers;
	vector<Maintainer> maintainers;
	loadMembers(clients, managers, maintainers);
	
	int selection = managers[0].createMember();

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
	}

	//string username, password;
	//startMenu(username, password, vMember);

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
	int size = vMember.size();
	bool found = false;
	int element = 0;
	for (int i = 0; i < size; i++)
	{
		if (vMember[i].getUsername() == username && vMember[i].getPassword() == password)
		{
			found = true;
			element = i;
			break;
		}
	}

	if (found)
	{
		cout << " We have found your account, " << vMember[element].getFirstname() << " " << vMember[element].getLastname() << "." << endl << endl;
		optionMenu(username, password, vMember, vMember[element]);
	}
	else
	{
		cout << " Sorry, we were unable to find your account. Going back to main menu...\n" << endl;
		startMenu(username, password, clients, managers, maintainers);
	}
}

void optionMenu(string &username, string &password, vector<Member> &vMember, Member &member)
{
	/*cout << "--------------------------------------------------------------------------\n";
	cout << "                                 Main Menu\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please select an option from below:" << endl;
	cout << " 1. Check Balance" << endl;
	cout << " 2. Withdraw Funds" << endl;
	cout << " 3. Deposit Funds" << endl;
	cout << " 4. Transfer Funds" << endl;
	cout << " 5. Print Recent Transactions" << endl;
	cout << " 6. Quit\n" << endl;

	if (member.getType() == "manager")
	{
		cout << " Additional Manager Options:" << endl;
		cout << " 7. Open Account" << endl;
		cout << " 8. Close Account" << endl;
		cout << " 9. View Details of Account(s)\n" << endl;
	}

	if (member.getType() == "maintainer:")
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

		if (member.getType() == "client")
		{
			if (choice <= 0 || choice >= 7)
				inputFail = true;
		}
		else if (member.getType() == "manager")
		{
			if (choice <= 0 || choice >= 10)
				inputFail = true;
		}
		else if (member.getType() == "maintainer")
		{
			if (choice <= 0 || choice >= 9)
				inputFail = true;
		}
	} while (inputFail == true);

	cout << endl << endl;

	choiceValidate(choice, username, password, vMember, member);*/
}

void choiceValidate(int &choice, string &username, string &password, vector<Member> &vMember, Member &member)
{
	double value = 0;

	switch (choice)
	{
		case 1:
			member.printAccount();
			optionMenu(username, password, vMember, member);
			break;
		case 2:
			cout << "Please enter a value you would like to withdraw: $";
			bool inputFail;
			do
			{
				cin >> value;
				inputFail = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (inputFail == true);
			member.selectAccount()->withdraw(value);
			cout << endl;
			optionMenu(username, password, vMember, member);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
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
			cout << " INTERNAL ERROR: Returning to main menu...\n" << endl;
			startMenu(username, password, clients, managers, maintainers);
	}
}

