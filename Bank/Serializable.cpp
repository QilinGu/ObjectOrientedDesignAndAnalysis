/**
* Created by: Pearson Radu
* The Serializable class saves or loads a vector of one of the three types of members.
* Simply just puts the data in a text file.
* Previously I did have a method that would use actual object serialization to save the data.
* Unfortunately I was unable to unserialize the data properly, or I would have to resort to boost serialization.
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
			getline(fileReader, line);
			double credit = stod(line);
			getline(fileReader, line);
			double loan = stod(line);

			Account account(accountType, balance);
			account.setCreditLimit(credit);
			account.setLoanLimit(loan);
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
			getline(fileReader, line);
			double credit = stod(line);
			getline(fileReader, line);
			double loan = stod(line);

			Account account(accountType, balance);
			account.setCreditLimit(credit);
			account.setLoanLimit(loan);
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
			getline(fileReader, line);
			double credit = stod(line);
			getline(fileReader, line);
			double loan = stod(line);

			Account account(accountType, balance);
			account.setCreditLimit(credit);
			account.setLoanLimit(loan);
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
 * This function takes a vector of strings, as well as a size and bool and writes it to a file
 * \param traces
 * \param toggle
 */
void Serializable::saveTrace(vector<string>& traces, bool toggle)
{
	ofstream fileWriter("traces.pr");

	if (fileWriter.is_open())
	{
		fileWriter << toggle << "\n";
		fileWriter << traces.size() << "\n";

		for (size_t i = 0; i < traces.size(); i++)
			fileWriter << traces[i] << "\n";
	}

	fileWriter.close();
}

/**
 * \brief
 * Load Trace Function
 * This function reads strings from a file and saves it to a vector
 * It returns a boolean to show the if the trace was on or off previously
 * \param traces
 * \return
 */
bool Serializable::loadTrace(vector<string> &traces)
{
	ifstream fileReader("traces.pr");
	string line;
	getline(fileReader, line);
	bool toggle = true;
	if (line == "0")
		toggle = false;
	getline(fileReader, line);
	int numTrace = stoi(line);

	for (int i = 0; i < numTrace; i++)
	{
		getline(fileReader, line);
		traces.push_back(line);
		getline(fileReader, line);
	}

	fileReader.close();

	return toggle;
}
