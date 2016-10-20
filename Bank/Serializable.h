#pragma once
#include <vector>
#include <fstream>
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
using namespace std;

class Serializable
{
	public:
	Serializable();
	~Serializable();

	template <class T> 
	void saveMembers(vector<T> &members, string file);

	vector<Client> loadClients();
	vector<Manager> loadManagers();
	vector<Maintainer> loadMaintainers();
	void saveTrace(vector<string> &traces, bool toggle);
	bool loadTrace(vector<string> &traces);
};

template <class T>
void Serializable::saveMembers(vector<T>& members, string file)
{
	ofstream fileWriter(file);

	if (fileWriter.is_open())
	{
		fileWriter << members.size() << "\n";
		for (size_t i = 0; i < members.size(); i++)
		{
			fileWriter << members[i].getFirstname() << "\n";
			fileWriter << members[i].getLastname() << "\n";
			fileWriter << members[i].getUsername() << "\n";
			fileWriter << members[i].getPassword() << "\n";
			fileWriter << members[i].getAccounts().size() << "\n";

			for (size_t j = 0; j < members[i].getAccounts().size(); j++)
			{
				fileWriter << members[i].getAccounts()[j].getAccountType() << "\n";
				fileWriter << members[i].getAccounts()[j].getBalance() << "\n";
				fileWriter << members[i].getAccounts()[j].getCreditLimit() << "\n";
				fileWriter << members[i].getAccounts()[j].getLoanLimit() << "\n";
			}

			fileWriter << members[i].getTransactions().size() << "\n";

			for (size_t j = 0; j < members[i].getTransactions().size(); j++)
				fileWriter << members[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}
