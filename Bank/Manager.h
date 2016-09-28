#pragma once
#include "Member.h"
#include "Client.h"
#include "Maintainer.h"

class Manager : public Member
{
	private:
	void memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts);

	public:
	Manager();
	Manager(string firstname, string lastname, string username, string password, Account account);
	~Manager();
	int createMember();
	Client initializeClient();
	Manager initializeManager();
	Maintainer initializeMaintainer();
	void closeAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
};
