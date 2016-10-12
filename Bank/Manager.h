#pragma once
#include "Member.h"
#include "Client.h"
#include "Maintainer.h"
using namespace std;

class Manager : public Member
{
	private:
	void memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts);
	Client* findClient(string username, vector<Client>& clients, int &location);
	Manager* findManager(string username, vector<Manager> &managers, int &location);
	Maintainer* findMaintainer(string username, vector<Maintainer> &maintainers, int &location);
	bool getChoice(string text);

	public:
	Manager();
	Manager(string firstname, string lastname, string username, string password, Account account);
	~Manager();
	int createMember();
	Client initializeClient();
	Manager initializeManager();
	Maintainer initializeMaintainer();
	string closeAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
	string openAccount(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
	void viewDetails(vector<Client> &clients, vector<Manager> &managers, vector<Maintainer> &maintainers);
};
