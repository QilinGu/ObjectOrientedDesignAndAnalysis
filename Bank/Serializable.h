#pragma once
#include <vector>
#include <fstream>
#include "Manager.h"
#include <ctime>
using namespace std;

class Serializable
{
	private:
	void saveTime(ofstream &fileWriter, struct tm time);

	public: 
	Serializable();
	~Serializable();

	template <class T>
	void saveMembers(vector<T> &members, string file);

	template <class T>
	void loadMembers(vector<T> &members, string file);

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
				saveTime(fileWriter, members[i].getAccounts()[j].getCreditTime());

				fileWriter << members[i].getAccounts()[j].getLoanLimit() << "\n";
				saveTime(fileWriter, members[i].getAccounts()[j].getLoanTime());
			}

			// Save the number of transactions (so we know how many to search for when we load them back), and the individual transaction data
			fileWriter << members[i].getTransactions().size() << "\n";
			for (size_t j = 0; j < members[i].getTransactions().size(); j++)
				fileWriter << members[i].getTransactions()[j] << "\n";
		}
	}

	fileWriter.close();
}

template <class T>
void Serializable::loadMembers(vector<T>& members, string file)
{
	ifstream fileReader(file);
	string line;
	getline(fileReader, line);
	int numMembers = stoi(line);

	for (int i = 0; i < numMembers; i++)
	{
		T member;

		getline(fileReader, line);
		member.setFirtname(line);
		getline(fileReader, line);
		member.setLastname(line);
		getline(fileReader, line);
		member.setUsername(line);
		getline(fileReader, line);
		member.setPassword(line);

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

			// Load the Credit Time Structure
			// Seconds
			getline(fileReader, line);
			int cSec = stoi(line);
			// Minutes
			getline(fileReader, line);
			int cMin = stoi(line);
			// Hours
			getline(fileReader, line);
			int cHour = stoi(line);
			// Days
			getline(fileReader, line);
			int cDay = stoi(line);
			// Months
			getline(fileReader, line);
			int cMon = stoi(line);
			// Years
			getline(fileReader, line);
			int cYear = stoi(line);
			struct tm creditTime = { cSec, cMin, cHour, cDay, cMon, cYear };

			double loan = stod(line);

			// Load the Loan Time Structure
			// Seconds
			getline(fileReader, line);
			int lSec = stoi(line);
			// Minutes
			getline(fileReader, line);
			int lMin = stoi(line);
			// Hours
			getline(fileReader, line);
			int lHour = stoi(line);
			// Days
			getline(fileReader, line);
			int lDay = stoi(line);
			// Months
			getline(fileReader, line);
			int lMon = stoi(line);
			// Years
			getline(fileReader, line);
			int lYear = stoi(line);
			struct tm loanTime = { lSec, lMin, lHour, lDay, lMon, lYear };

			Account account(accountType, balance);
			account.setCreditLimit(credit);
			account.setCreditTime(creditTime);
			account.setLoanLimit(loan);
			account.setLoanTime(loanTime);
			member.addAccount(account);
		}

		getline(fileReader, line);
		int transNum = stoi(line);

		for (int j = 0; j < transNum; j++)
		{
			getline(fileReader, line);
			member.addTransaction(line);
		}

		members.push_back(member);
	}

	fileReader.close();
}
