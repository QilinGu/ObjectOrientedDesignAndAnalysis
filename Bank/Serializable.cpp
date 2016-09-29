/**
* Created by: Pearson Radu
* The Serializable class saves or loads a vector of one of the three types of members.
* Simply just puts the data in a text file.
* Previously I did have a method that would use actual object serialization to save the data.
* Unfortunately I was unable to unserialize the data properly.
*/

#include "stdafx.h"
#include "Serializable.h"

Serializable::Serializable()
{
}

Serializable::~Serializable()
{
}


/**
 * \brief
 * Save Clients Function
 * This function takes a vector of members and saves the attributes individually to a file
 * \param clients
 */
void Serializable::saveClients(vector<Client>& clients)
{
	ofstream fileWriter("clients.pr");

	if (fileWriter.is_open())
	{
		fileWriter << clients.size() << "\n";
		for (size_t i = 0; i < clients.size(); i++)
		{
			fileWriter << clients[i].getFirstname() << "\n";
			fileWriter << clients[i].getLastname() << "\n";
			fileWriter << clients[i].getUsername() << "\n";
			fileWriter << clients[i].getPassword() << "\n";
			fileWriter << clients[i].getAccounts().size() << "\n";

			for (size_t j = 0; j < clients[i].getAccounts().size(); j++)
			{
				fileWriter << clients[i].getAccounts()[j].getAccountType() << "\n";
				fileWriter << clients[i].getAccounts()[j].getBalance() << "\n";
			}

			fileWriter << clients[i].getTransactions().size() << "\n";

			for (size_t j = 0; j < clients[i].getTransactions().size(); j++)
				fileWriter << clients[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}


/**
 * \brief
 * Load Clients Function
 * This function returns a vector of members that have been pulled and created from a file
 * \return
 */
vector<Client> Serializable::loadClients()
{
	ifstream fileReader("clients.pr");
	string line;
	getline(fileReader, line);
	int numClients = stoi(line);
	vector<Client> newClients;

	for (int i = 0; i < numClients; i++)
	{
		Client client;

		getline(fileReader, line);
		client.setFirtname(line);
		getline(fileReader, line);
		client.setLastname(line);
		getline(fileReader, line);
		client.setUsername(line);
		getline(fileReader, line);
		client.setPassword(line);

		getline(fileReader, line);
		int accounts = stoi(line);

		for (int j = 0; j < accounts; j++)
		{
			getline(fileReader, line);
			string accountType = line;
			getline(fileReader, line);
			double balance = stod(line);

			Account account(accountType, balance);
			client.addAccount(account);
		}

		getline(fileReader, line);
		int transNum = stoi(line);

		for (int j = 0; j < transNum; j++)
		{
			getline(fileReader, line);
			client.addTransaction(line);
		}

		newClients.push_back(client);
	}

	fileReader.close();

	return newClients;
}

/**
* \brief
* Save Managers Function
* This function takes a vector of members and saves the attributes individually to a file
* \param managers
*/
void Serializable::saveManagers(vector<Manager>& managers)
{
	ofstream fileWriter("managers.pr");

	if (fileWriter.is_open())
	{
		fileWriter << managers.size() << "\n";
		for (size_t i = 0; i < managers.size(); i++)
		{
			fileWriter << managers[i].getFirstname() << "\n";
			fileWriter << managers[i].getLastname() << "\n";
			fileWriter << managers[i].getUsername() << "\n";
			fileWriter << managers[i].getPassword() << "\n";
			fileWriter << managers[i].getAccounts().size() << "\n";

			for (size_t j = 0; j < managers[i].getAccounts().size(); j++)
			{
				fileWriter << managers[i].getAccounts()[j].getAccountType() << "\n";
				fileWriter << managers[i].getAccounts()[j].getBalance() << "\n";
			}

			fileWriter << managers[i].getTransactions().size() << "\n";

			for (size_t j = 0; j < managers[i].getTransactions().size(); j++)
				fileWriter << managers[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}

/**
* \brief
* Load Managers Function
* This function returns a vector of members that have been pulled and created from a file
* \return
*/
vector<Manager> Serializable::loadManagers()
{
	ifstream fileReader("managers.pr");
	string line;
	getline(fileReader, line);
	int numManagers = stoi(line);
	vector<Manager> newManagers;

	for (int i = 0; i < numManagers; i++)
	{
		Manager manager;

		getline(fileReader, line);
		manager.setFirtname(line);
		getline(fileReader, line);
		manager.setLastname(line);
		getline(fileReader, line);
		manager.setUsername(line);
		getline(fileReader, line);
		manager.setPassword(line);

		getline(fileReader, line);
		int accounts = stoi(line);

		for (int j = 0; j < accounts; j++)
		{
			getline(fileReader, line);
			string accountType = line;
			getline(fileReader, line);
			double balance = stod(line);

			Account account(accountType, balance);
			manager.addAccount(account);
		}

		getline(fileReader, line);
		int transNum = stoi(line);

		for (int j = 0; j < transNum; j++)
		{
			getline(fileReader, line);
			manager.addTransaction(line);
		}

		newManagers.push_back(manager);
	}

	fileReader.close();

	return newManagers;
}

/**
* \brief
* Save Maintainers Function
* This function takes a vector of members and saves the attributes individually to a file
* \param maintainers
*/
void Serializable::saveMaintainers(vector<Maintainer>& maintainers)
{
	ofstream fileWriter("maintainers.pr");

	if (fileWriter.is_open())
	{
		fileWriter << maintainers.size() << "\n";
		for (size_t i = 0; i < maintainers.size(); i++)
		{
			fileWriter << maintainers[i].getFirstname() << "\n";
			fileWriter << maintainers[i].getLastname() << "\n";
			fileWriter << maintainers[i].getUsername() << "\n";
			fileWriter << maintainers[i].getPassword() << "\n";
			fileWriter << maintainers[i].getAccounts().size() << "\n";

			for (size_t j = 0; j < maintainers[i].getAccounts().size(); j++)
			{
				fileWriter << maintainers[i].getAccounts()[j].getAccountType() << "\n";
				fileWriter << maintainers[i].getAccounts()[j].getBalance() << "\n";
			}

			fileWriter << maintainers[i].getTransactions().size() << "\n";

			for (size_t j = 0; j < maintainers[i].getTransactions().size(); j++)
				fileWriter << maintainers[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}

/**
* \brief
* Load Maintainers Function
* This function returns a vector of members that have been pulled and created from a file
* \return
*/
vector<Maintainer> Serializable::loadMaintainers()
{
	ifstream fileReader("maintainers.pr");
	string line;
	getline(fileReader, line);
	int numMaintainers = stoi(line);
	vector<Maintainer> newMaintainers;

	for (int i = 0; i < numMaintainers; i++)
	{
		Maintainer maintainer;

		getline(fileReader, line);
		maintainer.setFirtname(line);
		getline(fileReader, line);
		maintainer.setLastname(line);
		getline(fileReader, line);
		maintainer.setUsername(line);
		getline(fileReader, line);
		maintainer.setPassword(line);

		getline(fileReader, line);
		int accounts = stoi(line);

		for (int j = 0; j < accounts; j++)
		{
			getline(fileReader, line);
			string accountType = line;
			getline(fileReader, line);
			double balance = stod(line);

			Account account(accountType, balance);
			maintainer.addAccount(account);
		}

		getline(fileReader, line);
		int transNum = stoi(line);

		for (int j = 0; j < transNum; j++)
		{
			getline(fileReader, line);
			maintainer.addTransaction(line);
		}

		newMaintainers.push_back(maintainer);
	}

	fileReader.close();

	return newMaintainers;
}

/**
 * \brief 
 * Save Trace Function 
 * This function takes a vector of strings and write them to a file
 * \param traces 
 */
void Serializable::saveTrace(vector<string>& traces)
{
	ofstream fileWriter("traces.pr");

	if (fileWriter.is_open())
	{
		fileWriter << traces.size() << "\n";

		for (size_t i = 0; i < traces.size(); i++)
			fileWriter << traces[i] << "\n";
	}

	fileWriter.close();
}

/**
 * \brief 
 * Load Trace Function
 * This function reads strings from a file a saves it to a vector that it later returns
 * \return 
 */
vector<string> Serializable::loadTrace()
{
	ifstream fileReader("traces.pr");
	string line;
	getline(fileReader, line);
	int numTrace = stoi(line);
	vector<string> traces;

	for (int i = 0; i < numTrace; i++)
	{
		getline(fileReader, line);
		traces.push_back(line);
	}

	fileReader.close();

	return traces;
}
