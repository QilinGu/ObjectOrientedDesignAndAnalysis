/**
 * Created by: Pearson Radu
 * The Member class is a parent class for Client, Manager, and Maintainer. This class give
 * members a skeleton which will hold names, username, passwords as well as account detials.
*/

#include "stdafx.h"
#include "Member.h"
#include <iomanip>

Member::Member()
{
}

Member::~Member()
{
}

/**
 * \brief
 * Initialize Member Function
 * this function allows for the program to add a member with basic parameters
 * \param first
 * \param last
 * \param user
 * \param pass
 * \param account
 */
void Member::initialize(string first, string last, string user, string pass, Account account)
{
	firstname = first;
	lastname = last;
	username = user;
	password = pass;
	addAccount(account);
	transactions.shrink_to_fit();
}

void Member::checkCredit()
{
	for (size_t i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountType() == "Credit")
		{
			accounts[i].checkPayment();
			break;
		}
	}
}

/**
 * \brief
 * Additional Account Function
 * takes a parameter of an account and adds it to the accounts vector
 * \param account
 */
void Member::addAccount(Account account)
{
	accounts.push_back(account);
}

/**
 * \brief
 * Delete Account Function
 * Removes a specified account from the members account (only if it has a balance of zero)
 * \param account
 */
bool Member::deleteAccount(Account &account)
{
	if (account.getBalance() == 0)
	{
		int location = 0;
		int size = accounts.size();
		Account *accountLocation = &account;
		Account *vectorLocation;

		for (int i = 0; i < size; i++)
		{
			vectorLocation = &accounts[i];
			if (accountLocation == vectorLocation)
				location = i;
		}

		cout << "\n " << getFirstname() << " " << getLastname() << "'s " << account.getAccountType() << " account has been deleted.\n" << endl;


		//The account has been deleted.\n" << endl;
		accounts.erase(accounts.begin() + location);
		return true;
	}
	else
	{
		cout << "\n The balance of " << getFirstname() << " " << getLastname() << "'s account must be zero to close it." << endl;
		return false;
	}
}

/**
 * \brief
 * Account Selector Function
 * Finds the account the user wishes to use
 * If there is only one account present automatically returns that account
 * \return
 */
Account *Member::selectAccount(string option)
{
	if (accounts.size() == 1)
		return &accounts[0];

	// If there is more than one account open, it will list all accounts and 
	// a corresponding number will choose the desired account
	cout << "\n Which account would you like to " << option << "?" << endl;
	for (size_t i = 0; i < accounts.size(); i++)
	{
		cout << " " << i + 1 << ". " << accounts[i].getAccountType() << endl;
	}
	cout << " Please enter the corresponding number to the account: ";

	int choice;
	bool inputFail;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice <= 0 || choice >= accounts.size() + 1)
			inputFail = true;

	} while (inputFail == true);

	// Return choice -1 because we do not display zero as an option
	return &accounts[choice - 1];
}

/**
 * \brief
 * Print Account Function
 * This prints all the accounts and the balances of the member
 */
void Member::printAccount()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                               " << firstname << " " << lastname << endl;
	cout << "--------------------------------------------------------------------------\n" << endl;

	int size = accounts.size();
	for (int i = 0; i < size; i++)
	{
		cout << " Account: " << i + 1 << endl;
		cout << " Account: " << setprecision(2) << fixed << accounts[i].getAccountType() << endl;
		cout << " Balance: $" << setprecision(2) << fixed << accounts[i].getBalance() << endl << endl;

		// Use << setprecision(2) << fixed to show 2 decimal place
		// Use << fixed or << scientific to display the numbers in scientific notation or as a fixed number
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

/*Getter for transactions*/
vector<string> Member::getTransactions()
{
	return transactions;
}

/**
 * \brief
 * Function to add a transaction to the member
 * Adds a string to the list of 10 most recent transactions
 * \param transaction
 */
void Member::addTransaction(string transaction)
{
	// Make sure there is only at most 10 transactions saved
	if (transactions.size() == 10)
	{
		transactions.erase(transactions.begin());
		transactions.shrink_to_fit();
	}

	transactions.push_back(transaction);
}
