#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
using namespace std;

class Serializable
{
	public:
	Serializable();
	~Serializable();
	void Serializable::saveClients(vector<Client> &clients);
	vector<Client> Serializable::loadClients();
	void Serializable::saveManagers(vector<Manager> &managers);
	vector<Manager> Serializable::loadManagers();
	void Serializable::saveMaintainers(vector<Maintainer> &maintainers);
	vector<Maintainer> Serializable::loadMaintainers();
};
