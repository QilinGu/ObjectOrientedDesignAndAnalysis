#pragma once
#include "Member.h"

class Client : public Member
{
	public:
	Client();
	Client(string firstname, string lastname, string username, string password, Account account);
	~Client();
};
