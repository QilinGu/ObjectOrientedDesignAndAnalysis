/**
 * Created by: Pearson Radu
 * The Manager class is an inherited class from Member. This class holds a managers data
 * (like username, password and accounts). It also allows for additional managers roles
 * like adding, closing and viewing accounts.
 */

#include "stdafx.h"
#include "Manager.h"

Manager::Manager()
{
}

/**
 * \brief
 * Constructor that will call initializer from Member parent class
 * \param firstname
 * \param lastname
 * \param username
 * \param password
 * \param account
 */
Manager::Manager(string firstname, string lastname, string username, string password, Account account)
{
	initialize(firstname, lastname, username, password, account);
}

Manager::~Manager()
{
}

int Manager::createMember()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                             New Member of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What type of member is this?" << endl;
	cout << " 1. Client" << endl;
	cout << " 2. Manager" << endl;
	cout << " 3, Maintainer" << endl;
	cout << " Please enter a value from above: ";

	bool inputFail;
	int choice;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice <= 0 || choice >= 4)
			inputFail = true;
	} while (inputFail == true);

	cout << endl;

	return choice;
}

void Manager::memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts)
{
	cout << "Please enter the member's first name: ";
	cin >> firstname;
	cout << "Please enter the member's last name: ";
	cin >> lastname;
	cout << "Please enter the member's username: ";
	cin >> username;
	cout << "Please enter the member's password: ";
	cin >> password;
	cout << "How many accounts do you want to create for " << firstname << ": ";
	bool inputFail;
	int choice;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice <= 0)
			inputFail = true;
	} while (inputFail == true);

	cout << endl;

	for (int i = 0; i < choice; i++)
	{
		bool inputFail2;
		string accountType;
		double balance;
		cout << "--------------------------------------------------------------------------\n";
		cout << "                                  Account " << i + 1 << endl;
		cout << "--------------------------------------------------------------------------\n" << endl;
		cout << "What type of account is this: ";
		cin >> accountType;
		cout << "How much money is going to be deposited in this account: $";

		do
		{
			cin >> balance;
			inputFail2 = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (inputFail2 == true);

		cout << endl;

		Account account(accountType, balance);
		accounts.push_back(account);
	}

	cout << "--------------------------------------------------------------------------\n";
	cout << "                         Finished Creating Account" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

Client Manager::initializeClient()
{
	int choice;
	vector<Account> accounts;
	string firstname, lastname, username, password;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                             New Client of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	memberInput(firstname, lastname, username, password, accounts);

	Client client(firstname, lastname, username, password, accounts[0]);

	for (size_t i = 1; i < accounts.size(); i++)
		client.addAccount(accounts[i]);

	return client;
}

Manager Manager::initializeManager()
{
	int choice;
	vector<Account> accounts;
	string firstname, lastname, username, password;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                            New Manager of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	memberInput(firstname, lastname, username, password, accounts);

	Manager manager(firstname, lastname, username, password, accounts[0]);

	for (size_t i = 1; i < accounts.size(); i++)
		manager.addAccount(accounts[i]);

	return manager;
}

Maintainer Manager::initializeMaintainer()
{
	int choice;
	vector<Account> accounts;
	string firstname, lastname, username, password;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                          New Maintainer of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	memberInput(firstname, lastname, username, password, accounts);

	Maintainer maintainer(firstname, lastname, username, password, accounts[0]);

	for (size_t i = 1; i < accounts.size(); i++)
		maintainer.addAccount(accounts[i]);

	return maintainer;
}

