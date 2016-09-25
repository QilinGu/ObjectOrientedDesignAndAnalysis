#include "stdafx.h"
#include "Member.h"

/*
	Member Constructor
	This will ask the user for their first and last name, username, password and accounts
*/
Member::Member()
{
	/**/
}

Member::~Member()
{
}

void Member::initialize(string first, string last, string user, string pass, Account account)
{
	firstname = first;
	lastname = last;
	username = user;
	password = pass;
	addAccount(account);
}

void Member::initialize()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                             New Member of PR Bank\n";
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Please enter the member's first name: ";
	cin >> firstname;
	cout << "Please enter the member's last name: ";
	cin >> lastname;
	cout << "Please enter the member's username: ";
	cin >> username;
	cout << "Please enter the member's password: ";
	cin >> password;
	cout << "How many accounts do you want to create for " << firstname << ": ";

	bool inputFail1;
	int num1;
	do
	{
		cin >> num1;
		inputFail1 = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (inputFail1 == true);

	for (int i = 0; i < num1; i++)
	{
		bool inputFail2;
		string accountType;
		double balance;
		cout << "--------------------------------------------------------------------------\n";
		cout << "                                  Account " << i + 1 << endl;
		cout << "--------------------------------------------------------------------------" << endl;
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

		Account account(accountType, balance);
		addAccount(account);
	}

	cout << "--------------------------------------------------------------------------\n";
	cout << "                         Finished Creating Account" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

/*
	Additional Account Function
	Takes a parameter of an account and adds it to the vector
*/
void Member::addAccount(Account account)
{
	accounts.push_back(account);
}

/*
	Remove Account Functions
*/
void Member::removeAccount(Account account)
{
	int location;
	int size = accounts.size();
	Account *accountLocation = &account;
	Account *vectorLocation;

	for (int i = 0; i < size; i++)
	{
		vectorLocation = &accounts[i];
		if (accountLocation == vectorLocation)
			location = i;
	}

	accounts.erase(accounts.begin() + location);
}

/*
	Account Selector Function
*/
Account *Member::selectAccount()
{
	if (accounts.size() == 1)
		return &accounts[0];
}

/*
	Print Account Function
	This prints all the accounts and the balances of them
*/
void Member::printAccount()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                               " << firstname << " " << lastname << endl;
	cout << "--------------------------------------------------------------------------\n" << endl;

	int size = accounts.size();
	for (int i = 0; i < size; i++)
	{
		cout << " Account " << i + 1 << endl;

		cout << " Account: " << accounts[i].getAccountType() << endl;
		cout << " Balance: $" << accounts[i].getBalance() << endl << endl;
	}
}

/*Getter for firstname*/
string Member::getFirstname()
{
	return firstname;
}

/*Setter for firstname*/
void Member::setFirtname(string first)
{
	firstname = first;
}

/*Getter for lastname*/
string Member::getLastname()
{
	return lastname;
}

/*Setter for lastname*/
void Member::setLastname(string last)
{
	lastname = last;
}

/*Getter for username*/
string Member::getUsername()
{
	return username;
}

/*Setter for username*/
void Member::setUsername(string user)
{
	username = user;
}

/*Getter for password*/
string Member::getPassword()
{
	return password;
}

/*Setter for password*/
void Member::setPassword(string pass)
{
	password = pass;
}

/*Getter for accounts*/
vector<Account> Member::getAccounts()
{
	return accounts;
}

/*Getter for type*/
string Member::getType()
{
	return type;
}

/*Setter for type*/
void Member::setType(string newType)
{
	type = newType;
}
