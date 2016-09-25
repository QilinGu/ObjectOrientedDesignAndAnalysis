/*
Created by: Pearson Radu
The Member class is a parent class for Client, Manager, and Maintainer. This class give
members a skeleton which will hold names, username, passwords as well as account detials.
*/

#include "stdafx.h"
#include "Member.h"

Member::Member()
{
}

Member::~Member()
{
}

/*
	Initialize Member Function
	This function allows for the program to add a member with basic parameters
*/
void Member::initialize(string first, string last, string user, string pass, Account account)
{
	firstname = first;
	lastname = last;
	username = user;
	password = pass;
	addAccount(account);
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
