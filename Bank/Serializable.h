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


/**
 * \brief 
 * Template function for saving the members of the bank (clients, managers, & maintainers)
 * Takes a vector of members and a string for file location to save the members to a text file
 * \tparam T 
 * \param members 
 * \param file 
 */
template <class T>
void Serializable::saveMembers(vector<T>& members, string file)
{
	ofstream fileWriter(file);

	if (fileWriter.is_open())
	{
		// Save the number of members so we know how many to search for when we load them back
		fileWriter << members.size() << "\n";
		for (size_t i = 0; i < members.size(); i++)
		{
			// Save their firstname, lastname, username, password, and number of accounts (so we know how many to search for when we load them back)
			fileWriter << members[i].getFirstname() << "\n";
			fileWriter << members[i].getLastname() << "\n";
			fileWriter << members[i].getUsername() << "\n";
			fileWriter << members[i].getPassword() << "\n";
			fileWriter << members[i].getAccounts().size() << "\n";

			for (size_t j = 0; j < members[i].getAccounts().size(); j++)
			{
				// Save their account type, balance, credit limit, and loan limit
				fileWriter << members[i].getAccounts()[j].getAccountType() << "\n";
				fileWriter << members[i].getAccounts()[j].getBalance() << "\n";
				fileWriter << members[i].getAccounts()[j].getCreditLimit() << "\n";
				fileWriter << members[i].getAccounts()[j].getLoanLimit() << "\n";
			}

			// Save the number of transactions (so we know how many to search for when we load them back), and the individual transaction data
			fileWriter << members[i].getTransactions().size() << "\n";
			for (size_t j = 0; j < members[i].getTransactions().size(); j++)
				fileWriter << members[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}
