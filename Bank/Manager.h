#pragma once
#include "Member.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"

class Manager : public Member
{
	private:
	void memberInput(string &firstname, string &lastname, string &username, string &password, vector<Account> &accounts);

	public:
	Manager();
	~Manager();
	int createMember();
	Client initializeClient();
	Manager initializeManager();
	Maintainer initializeMaintainer();
};
