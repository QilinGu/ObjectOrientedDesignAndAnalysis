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
int Manager::chooseMemberType()
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
* Initialize Client Function
* This is the second step for a Manager to create a new member of type client
* The reason this function cannot be called from the first step is because we do not yet know which type of memebr we will return
* This function also calls Member Input, which is called with each Member Initializer that gets all new Member info
* \return
*/
Client Manager::initializeClient()
{
	vector<Account> accounts;
	string firstname, lastname, username, password;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                             New Client of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	// Call memberInput to get all the information for the members account
	memberInput(firstname, lastname, username, password, accounts);

	// Create the Client with the input gathered, only a parameter of one account will be used because that is the default
	Client client(firstname, lastname, username, password, accounts[0]);

	// Add any other remaining accounts if there is some
	for (size_t i = 1; i < accounts.size(); i++)
		client.addAccount(accounts[i]);

	return client;
}

/**
* \brief
* Initialize Manager Function
* This is the second step for a Manager to create a new member of type manager
* The reason this function cannot be called from the first step is because we do not yet know which type of memebr we will return
* This function also calls Member Input, which is called with each Member Initializer that gets all new Member info
* \return
*/
Manager Manager::initializeManager()
{
	vector<Account> accounts;
	string firstname, lastname, username, password;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                            New Manager of PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;

	// Call memberInput to get all the information for the members account
	memberInput(firstname, lastname, username, password, accounts);

	// Create the Manager with the input gathered, only a parameter of one account will be used because that is the default
	Manager manager(firstname, lastname, username, password, accounts[0]);

	// Add any other remaining accounts if there is some
	for (size_t i = 1; i < accounts.size(); i++)
		manager.addAccount(accounts[i]);

	return manager;
}

/**
* \brief
* Initialize Maintainer Function
* This is the second step for a Manager to create a new member  of type maintainer
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

	// Call memberInput to get all the information for the members account
	memberInput(firstname, lastname, username, password, accounts);

	// Create the Maintainer with the input gathered, only a parameter of one account will be used because that is the default
	Maintainer maintainer(firstname, lastname, username, password, accounts[0]);

	// Add any other remaining accounts if there is some
	for (size_t i = 1; i < accounts.size(); i++)
		maintainer.addAccount(accounts[i]);

	return maintainer;
}

/**
 * \brief
 * Member Input Function
 * This function is called from the Initialize Member functions
 * This function gathers the information needed to create a new member
 * \param firstname
 * \param lastname
 * \param username
 * \param password
 * \param accounts
 */
void Manager::memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts)
{
	cout << " Please enter the member's first name: ";
	cin >> firstname;
	cout << " Please enter the member's last name: ";
	cin >> lastname;
	cout << " Please enter the member's username: ";
	cin >> username;
	cout << " Please enter the member's password: ";
	cin >> password;
	cout << "\n How many accounts do you want to create for " << firstname << "?" << endl;
	cout << " The member must have a minimum of 1 and maximum of 4 accounts: ";
	bool inputFail;
	int choice;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice <= 0 || choice >= 5)
			inputFail = true;
	} while (inputFail == true);
	cout << endl;

	for (int i = 0; i < choice; i++)
	{
		bool inputFail2;
		double balance;
		cout << "--------------------------------------------------------------------------\n";
		cout << "                                  Account " << i + 1 << endl;
		cout << "--------------------------------------------------------------------------\n" << endl;

		// Loop until an account is chosen
		string accountType = "";
		while(accountType == "")
			accountType = chooseAccount(accounts);		
		
		cout << " What is the balance/limit of this account going to be: $";

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

		if (account.getAccountType() == "Loan")
		{
			account.setLoanLimit(balance);
			account.setBalance(0);
		}

		if (account.getAccountType() == "Credit")
		{
			account.setCreditLimit(balance);
			account.setBalance(0);
		}

		accounts.push_back(account);
	}

	cout << "--------------------------------------------------------------------------\n";
	cout << "                         Finished Creating Account" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

/**
 * \brief
 * Find Client Function
 * Trys to return a pointer to a client if they match the username, as well as their relative position in the vector
 * \param username
 * \param clients
 * \return
 */
Client* Manager::findClient(string username, vector<Client>& clients, int &location)
{
	Client * client = NULL;

	for (size_t i = 0; i < clients.size(); i++)
	{
		if (username == clients[i].getUsername())
		{
			location = i;
			return &clients[i];
		}
	}
	return client;
}

/**
 * \brief
 * Find Manager Function
 * Trys to return a pointer to a manager if they match the username, as well as their relative position in the vector
 * \param username
 * \param managers
 * \return
 */
Manager* Manager::findManager(string username, vector<Manager>& managers, int &location)
{
	Manager * manager = NULL;
	bool found = false;

	for (size_t i = 0; i < managers.size(); i++)
	{
		if (username == managers[i].getUsername())
		{
			location = i;
			return &managers[i];
		}
	}

	return manager;
}

/**
 * \brief
 * Find Maintainer Function
 * Trys to return a pointer to a maintainer if they match the username, as well as their relative position in the vector
 * \param username
 * \param maintainers
 * \return
 */
Maintainer* Manager::findMaintainer(string username, vector<Maintainer>& maintainers, int & location)
{
	Maintainer  * maintainer = NULL;

	for (size_t i = 0; i < maintainers.size(); i++)
	{
		if (username == maintainers[i].getUsername())
		{
			location = i;
			return &maintainers[i];
		}
	}

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
 * \return 
 */
string Manager::closeAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	string username;
	bool deleted = false;
	bool removed = false;
	int location = 0;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                            Close Member Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What is the username of the member you wish to close: ";
	cin >> username;


	//Find the clinet
	Client * client = findClient(username, clients, location);
	// If the client is not NULL, which means we found them, and they have more than one account
	if (client != NULL && client->getAccounts().size() > 1)
	{
		// Call delete account, which will take in a selected account (with a string) and return true if it was deleted
		deleted = client->deleteAccount(*client->selectAccount("close for " + client->getFirstname() + " " + client->getLastname()));
		// If the account was deleted add a transaction saying so
		if (deleted)
			addTransaction(getFirstname() + " deleted one of " + client->getFirstname() + " " + client->getLastname() + "'s accounts.");
	}
	// If the client is not NULL, which means we found them, and they have only one account
	else if (client != NULL && client->getAccounts().size() == 1)
	{
		// Get confirmation from the manager that it is ok to remove them from the system completely
		bool choice = getChoice(client->getFirstname() + " " + client->getLastname() + " only has one account, do you want to remove them?");
		if (choice)
		{
			// Erase the client and add a trace saying so
			removed = choice;
			addTransaction(getFirstname() + " deleted " + client->getFirstname() + " " + client->getLastname() + " from PR Bank.");
			clients.erase(clients.begin() + location);
		}
	}

	if (!deleted)
	{
		// Find the manager
		Manager * manager = findManager(username, managers, location);
		// If the manager is not NULL, which means we found them and that they have more than one account
		if (manager != NULL && manager->getAccounts().size() > 1)
		{
			// Call delete account, which will take in a selected account (with a string) and return true if it was deleted
			deleted = manager->deleteAccount(*manager->selectAccount("close for " + manager->getFirstname() + " " + manager->getLastname()));
			// If the account was deleted add a transaction saying so
			if (deleted)
				addTransaction(getFirstname() + " deleted one of " + manager->getFirstname() + " " + manager->getLastname() + "'s accounts.");
		}
		// If the manager is not NULL, which means we found them, and they have only one account
		else if (manager != NULL && manager->getAccounts().size() == 1)
		{
			// Get confirmation from the manager that it is ok to remove them from the system completely
			// An error persists when trying to completely remove a manager, since there accounts are running while you delete them
			/*bool choice = getChoice(manager->getFirstname() + " " + manager->getLastname() + " only has one account, do you want to remove them?");
			if (choice)
			{
				// Erase the manager and add a trace saying so
				removed = choice;
				addTransaction(getFirstname() + " deleted " + manager->getFirstname() + " " + manager->getLastname() + " from PR Bank.");
				managers.erase(managers.begin() + location);
			}*/
		}
	}

	if (!deleted)
	{
		// Find the maintainer
		Maintainer * maintainer = findMaintainer(username, maintainers, location);
		// If the maintainer is not NULL, which means we found them and that they have more than one account
		if (maintainer != NULL && maintainer->getAccounts().size() > 1)
		{
			// Call delete account, which will take in a selected account (with a string) and return true if it was deleted
			deleted = maintainer->deleteAccount(*maintainer->selectAccount("close for " + maintainer->getFirstname() + " " + maintainer->getLastname()));
			// If the account was deleted add a transaction saying so
			if (deleted)
				addTransaction(getFirstname() + " deleted one of " + maintainer->getFirstname() + " " + maintainer->getLastname() + "'s accounts.");
		}
		// If the maintainer is not NULL, which means we found them, and they have only one account
		else if (maintainer != NULL && maintainer->getAccounts().size() == 1)
		{
			// Get confirmation from the manager that it is ok to remove them from the system completely
			bool choice = getChoice(maintainer->getFirstname() + " " + maintainer->getLastname() + " only has one account, do you want to remove them?");
			if (choice)
			{
				// Erase the manager and add a trace saying so
				removed = choice;
				addTransaction(getFirstname() + " deleted " + maintainer->getFirstname() + " " + maintainer->getLastname() + " from PR Bank.");
				maintainers.erase(maintainers.begin() + location);
			}
		}
	}

	// If they are deleted or removed print success 
	if (deleted || removed)
	{
		cout << "\n Successfully removed the account associated with " << username << " from PR Bank.\n" << endl;
		return " closed an account for" + username;
	}
	
	if (!deleted)
	{
		cout << "\n Sorry, there was a problem closing the requested account.\n" << endl;
		return " failed to close an account for" + username;
	}
}

/**
 * \brief 
 * * Open Account Function
 * This function takes all members of the bank as a parameter and finds the current user accounts based on a username.
 * If it finds the user, it will add a new account to their current ones.
 * \param clients 
 * \param managers 
 * \param maintainers 
 * \return 
 */
string Manager::openAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	string username;
	bool opened = false;
	bool inputFail;
	string accountType = "";
	double balance;
	// dummy variable
	int location = 0;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                           Open Member Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " What is the username of the member you wish to open: ";
	cin >> username;

	cout << " What is the balance/limit of this account going to be: $";
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

	// Find the client and if they are not NULL we have found them
	Client * client = findClient(username, clients, location);
	if (client != NULL && client->getAccounts().size() < 4)
	{
		opened = true;
		// Continuously try to find an account the user does not have open already
		while (accountType == "")
			accountType = chooseAccount(client->getAccounts());
		Account account(accountType, balance);

		// If the account type is a loan, set the balance to 0 and set the loan limit
		if (account.getAccountType() == "Loan")
		{
			account.setLoanLimit(balance);
			account.setBalance(0);
		}

		// If the account type is a credit, set the balance to 0 and set the credit limit
		if (account.getAccountType() == "Credit")
		{
			account.setCreditLimit(balance);
			account.setBalance(0);
			account.setCreditTime();
		}

		client->addAccount(account);
		addTransaction(getFirstname() + " opened a new account for " + client->getFirstname() + " " + client->getLastname());
	}

	if (!opened)
	{
		// Find the client and if they are not NULL we have found them
		Manager * manager = findManager(username, managers, location);
		if (manager != NULL && manager->getAccounts().size() < 4)
		{
			opened = true;
			// Continuously try to find an account the user does not have open already
			while (accountType == "")
				accountType = chooseAccount(manager->getAccounts());
			Account account(accountType, balance);

			// If the account type is a loan, set the balance to 0 and set the loan limit
			if (account.getAccountType() == "Loan")
			{
				account.setLoanLimit(balance);
				account.setBalance(0);
			}

			// If the account type is a credit, set the balance to 0 and set the credit limit
			if (account.getAccountType() == "Credit")
			{
				account.setCreditLimit(balance);
				account.setBalance(0);
			}

			manager->addAccount(account);
			addTransaction(getFirstname() + " opened a new account for " + manager->getFirstname() + " " + manager->getLastname());
		}
	}

	if (!opened)
	{
		// Find the client and if they are not NULL we have found them
		Maintainer * maintainer = findMaintainer(username, maintainers, location);
		if (maintainer != NULL && maintainer->getAccounts().size() < 4)
		{
			opened = true;
			// Continuously try to find an account the user does not have open already
			while (accountType == "")
				accountType = chooseAccount(maintainer->getAccounts());
			Account account(accountType, balance);

			// If the account type is a loan, set the balance to 0 and set the loan limit
			if (account.getAccountType() == "Loan")
			{
				account.setLoanLimit(balance);
				account.setBalance(0);
			}

			// If the account type is a credit, set the balance to 0 and set the credit limit
			if (account.getAccountType() == "Credit")
			{
				account.setCreditLimit(balance);
				account.setBalance(0);
			}

			maintainer->addAccount(account);
			addTransaction(getFirstname() + " opened a new account for " + maintainer->getFirstname() + " " + maintainer->getLastname());
		}
	}

	if (!opened)
	{
		cout << " Sorry, we could not find a member matching that username,\n";
		cout << " or the user currently has the maximum number of accounts." << endl;
		return " failed to open an account for " + username;
	}
	else
	{
		cout << " The account has been added.\n" << endl;
		return " opened a new account for " + username;
	}
}

/**
 * \brief 
 * Choose Account Function
 * Find the account type of a user that does not already exist
 * \param accounts 
 * \return 
 */
string Manager::chooseAccount(vector<Account> &accounts)
{
	cout << " What type of account is this?" << endl;
	cout << " 1. Savings" << endl;
	cout << " 2. Chequing" << endl;
	cout << " 3. Credit" << endl;
	cout << " 4. Loan" << endl;
	cout << " Please choose an option from above: ";

	bool inputFail;
	int choice;
	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice <= 0 && choice >= 5)
			inputFail = true;
	} while (inputFail == true);
	cout << endl;

	string accountType = "";
	if (choice == 1)
		accountType = "Savings";
	else if (choice == 2)
		accountType = "Chequing";
	else if (choice == 3)
		accountType = "Credit";
	else if (choice == 4)
		accountType = "Loan";

	bool alreadyExists = false;
	for (size_t j = 0; j < accounts.size(); j++)
		if (accounts[j].getAccountType() == accountType)
			alreadyExists = true;

	if (alreadyExists)
	{
		cout << " Sorry, this user already has a " << accountType << " account, please choose another.\n" << endl;
		return "";
	}
	
	return accountType;
}

/**
 * \brief 
 * View Details Function
 * Allows a manager to choice if they want to view all details of bank members or search by username
 * \param clients 
 * \param managers 
 * \param maintainers 
 */
void Manager::viewDetails(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers)
{
	int choice = 0;;
	string username;
	bool found = false;
	bool inputFail;

	cout << "--------------------------------------------------------------------------\n";
	cout << "                           View Member Details\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Here are some options that you can sort the members of the bank: " << endl;
	cout << " 1. View All Members" << endl;
	cout << " 2. Find A Member By Username" << endl;
	cout << " How would you like to proceed: ";

	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice <= 0 || choice >= 3)
			inputFail = true;
	} while (inputFail == true);

	cout << endl;

	// Print Details of all members of the bank
	if (choice == 1)
	{
		for (size_t i = 0; i < clients.size(); i++)
			clients[i].printAccount();
		for (size_t i = 0; i < managers.size(); i++)
			managers[i].printAccount();
		for (size_t i = 0; i < maintainers.size(); i++)
			maintainers[i].printAccount();
	}

	// Print details of a specific user
	if (choice == 2)
	{
		cout << " What is the username of the member you wish to open: ";
		cin >> username;
		cout << endl;

		// dummy variable
		int location = 0;

		Client * client = findClient(username, clients, location);
		if (client != NULL)
			client->printAccount();

		Manager * manager = findManager(username, managers, location);
		if (manager != NULL)
			manager->printAccount();

		Maintainer * maintainer = findMaintainer(username, maintainers, location);
		if (maintainer != NULL)
			maintainer->printAccount();
	}
}

/**
 * \brief 
 * Get Choice Function
 * Returns a confirmation
 * \param text 
 * \return 
 */
bool Manager::getChoice(string text)
{
	int choice = 0;
	bool inputFail;
	bool result = false;

	cout << "\n " << text << endl;
	cout << " Press 1 to confirm, press any other button to decline: ";

	do
	{
		cin >> choice;
		inputFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice == 1)
			result = true;
	} while (inputFail == true);

	return result;
}