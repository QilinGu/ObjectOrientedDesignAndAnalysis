#pragma once
#include <vector>
#include <fstream>
#include "Member.h"
class Serializable
{
	private:
	string file;

	public:
	Serializable();
	~Serializable();
	void save(vector<Member> &vMember);
	vector<Member> load();
};

