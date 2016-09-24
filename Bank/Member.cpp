#include "stdafx.h"
#include "Member.h"

/*
	Member Constructor
	This will ask the user for their first and last name, username, password and accounts
*/
Member::Member()
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

Member::~Member()
{
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
	Print Account Function
	This prints all the accounts and the balances of them
*/
void Member::printAccount()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                               " << firstname << " " << lastname << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	
	int size = accounts.size();
	for (int i = 0; i < size; i++)
	{
		cout << "\tAccount " << i + 1 << endl;
		
		cout << "\tAccount: $" << accounts[i].getAccountType() << endl;
		cout << "\tBalance: $" << accounts[i].getBalance() << endl;
	}
	cout << "--------------------------------------------------------------------------" << endl;
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
