#include "stdafx.h"
#include "Serializable.h"

Serializable::Serializable()
{
}

Serializable::~Serializable()
{
}

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
		}
	}

	fileWriter.close();
}

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
		newClients.push_back(client);
	}

	fileReader.close();

	return newClients;
}

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
		}
	}

	fileWriter.close();
}

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
		newManagers.push_back(manager);
	}

	fileReader.close();

	return newManagers;
}

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
		}
	}

	fileWriter.close();
}

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
		newMaintainers.push_back(maintainer);
	}

	fileReader.close();

	return newMaintainers;
}
