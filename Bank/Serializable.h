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
	void saveClients(vector<Client> &clients);
	vector<Client> loadClients();
	void saveManagers(vector<Manager> &managers);
	vector<Manager> loadManagers();
	void saveMaintainers(vector<Maintainer> &maintainers);
	vector<Maintainer> loadMaintainers();
	void saveTrace(vector<string> &traces);
	vector<string> loadTrace();
};
