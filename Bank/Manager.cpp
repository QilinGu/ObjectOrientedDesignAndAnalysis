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


/**
 * \brief
 * Create Member Function
 * This is the first step for a manager to create a new member
 * This function returns an integer which corresponds with what type of member you want to create
 * 1 (Client), 2 (Manager), and 3 (Maintainer)
 * \return
 */
int Manager::createMember()
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                             New Member of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What type of member is this?" << endl;
	cout << " 1. Client" << endl;
	cout << " 2. Manager" << endl;
	cout << " 3. Maintainer" << endl;
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

/**
 * \brief
 * Member Input Function
 * This function is called from the Member Initializer functions
 * This function gathers the information needed to create a new member
 * \param firstname
 * \param lastname
 * \param username
 * \param password
 * \param accounts
 */
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
		cout << " What type of account is this: ";
		cin >> accountType;
		cout << " How much money is going to be deposited in this account: $";

		do
		{
			cin >> balance;
			inputFail2 = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (balance <= 0)
				inputFail2 = true;
		} while (inputFail2 == true);

		cout << endl;

		Account account(accountType, balance);
		accounts.push_back(account);
	}

	cout << "--------------------------------------------------------------------------\n";
	cout << "                         Finished Creating Account" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

/**
 * \brief
 * Initialize Client Function
 * This is the second step for a Manager to create a new member
 * The reason this function cannot be called from the first step is because we do not yet know which type of memebr we will return
 * This function also calls Member Input, which is called with each Member Initializer that gets all new Member info
 * \return
 */
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

/**
* \brief
* Initialize Manager Function
* This is the second step for a Manager to create a new member
* The reason this function cannot be called from the first step is because we do not yet know which type of memebr we will return
* This function also calls Member Input, which is called with each Member Initializer that gets all new Member info
* \return
*/
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

/**
* \brief
* Initialize Maintainer Function
* This is the second step for a Manager to create a new member
* The reason this function cannot be called from the first step is because we do not yet know which type of memebr we will return
* This function also calls Member Input, which is called with each Member Initializer that gets all new Member info
* \return
*/
Maintainer Manager::initializeMaintainer()
{
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

/**
 * \brief 
 * Close Account Function
 * This function takes all the members of the bank and search for a username, if it finds the user account it will ask what account you want
 * to delete, and if there is only one account it will delete that.
 * The account will only be deleted if there is zero dollars in it
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void Manager::closeAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	string username;
	bool deleted = false;
	bool found = false;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                            Close Member Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What is the username of the member you wish to close: ";
	cin >> username;

	// Delete the users account if they are a client
	if (!deleted)
	{
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (username == clients[i].getUsername())
			{
				deleted = clients[i].deleteAccount(*(clients[i].selectAccount("close for " + clients[i].getFirstname() + " " + clients[i].getLastname())));
				if (deleted)
					addTransaction(getFirstname() + " deleted one of " + clients[i].getFirstname() + " " + clients[i].getLastname() + "'s accounts.");
				found = true;
				break;
			}
		}
	}

	// Delete the users account if they are a manager
	if (!deleted)
	{
		for (size_t i = 0; i < managers.size(); i++)
		{
			if (username == managers[i].getUsername())
			{
				deleted = managers[i].deleteAccount(*(managers[i].selectAccount("close for " + managers[i].getFirstname() + " " + managers[i].getLastname())));
				if (deleted)
					addTransaction(getFirstname() + " deleted one of " + managers[i].getFirstname() + " " + managers[i].getLastname() + "'s accounts.");
				found = true;
				break;
			}
		}
	}

	// Delete the users account if they are a maintainer
	if (!deleted)
	{
		for (size_t i = 0; i < maintainers.size(); i++)
		{
			if (username == maintainers[i].getUsername())
			{
				deleted = maintainers[i].deleteAccount(*(maintainers[i].selectAccount("close for " + maintainers[i].getFirstname() + " " + maintainers[i].getLastname())));
				if (deleted)
					addTransaction(getFirstname() + " deleted one of " + maintainers[i].getFirstname() + " " + maintainers[i].getLastname() + "'s accounts.");
				found = true;
				break;
			}
		}
	}

	if (!found)
		cout << "\n Sorry, we could not find a member matching that username.\n" << endl;
}

/**
 * \brief 
 * Open Account Function
 * This function takes all members of the bank as a parameter and finds the current user accounts based on a username.
 * If it finds the user, it will add a new account to their current ones.
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void Manager::openAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	string username;
	bool opened = false;
	bool inputFail;
	string accountType;
	double balance;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                           Open Member Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What is the username of the member you wish to open: ";
	cin >> username;
	cout << "\n What type of account is this: ";
	cin >> accountType;
	cout << " How much money is going to be deposited in this account: $";

	do
	{
		cin >> balance;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (balance <= 0)
			inputFail = true;
	} while (inputFail == true);

	cout << endl;

	Account account(accountType, balance);

	//Add account if they are a client
	if(!opened)
	{
		for(size_t i = 0; i < clients.size(); i++)
		{
			if(username == clients[i].getUsername())
			{
				opened = true;
				clients[i].addAccount(account);
				addTransaction(getFirstname() + " opened a new account for " + clients[i].getFirstname() + " " + clients[i].getLastname());
				break;
			}
		}
	}

	//Add account if they are a manager
	if (!opened)
	{
		for (size_t i = 0; i < managers.size(); i++)
		{
			if (username == managers[i].getUsername())
			{
				opened = true;
				managers[i].addAccount(account);
				addTransaction(getFirstname() + " opened a new account for " + managers[i].getFirstname() + " " + managers[i].getLastname());
				break;
			}
		}
	}

	//Add account if they are a maintainer
	if (!opened)
	{
		for (size_t i = 0; i < maintainers.size(); i++)
		{
			if (username == maintainers[i].getUsername())
			{
				opened = true;
				maintainers[i].addAccount(account);
				addTransaction(getFirstname() + " opened a new account for " + maintainers[i].getFirstname() + " " + maintainers[i].getLastname());
				break;
			}
		}
	}

	if (!opened)
		cout << " Sorry, we could not find a member matching that username.\n" << endl;
	else
		cout << " The account has been added.\n" << endl;
}
