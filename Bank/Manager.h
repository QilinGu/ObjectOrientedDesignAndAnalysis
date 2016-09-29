#pragma once
#include "Member.h"
#include "Client.h"
#include "Maintainer.h"
using namespace std;

class Manager : public Member
{
	private:
	void memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts);
	Client* findClient(string username, vector<Client>& clients);
	Manager* findManager(string username, vector<Manager> &managers);
	Maintainer* findMaintainer(string username, vector<Maintainer> &maintainers);

	public:
	Manager();
	Manager(string firstname, string lastname, string username, string password, Account account);
	~Manager();
	int createMember();
	Client initializeClient();
	Manager initializeManager();
	Maintainer initializeMaintainer();
	void closeAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
	void openAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
	void viewDetails(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
};
