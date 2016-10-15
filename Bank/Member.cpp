/**
 * Created by: Pearson Radu
 * The Member class is a parent class for Client, Manager, and Maintainer. This class give
 * members a skeleton which will hold names, username, passwords as well as account detials.
*/

#include "stdafx.h"
#include "Member.h"

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
 * Delete Account Functions
 * removes a specified account from the members account if it has a balance of zero
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
	else
	{
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

		return &accounts[choice - 1];
	}
}

/**
 * \brief
 * Print Account Function
 * This prints all the accounts and the balances of them
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

vector<string> Member::getTransactions()
{
	/*if (transactions.empty())
		cout << " Sorry, you do not have any recent transactions." << endl;*/

	return transactions;
}

void Member::addTransaction(string transaction)
{
	if (transactions.size() == 10)
	{
		transactions.erase(transactions.begin());
		transactions.shrink_to_fit();
	}

	transactions.push_back(transaction);
}
