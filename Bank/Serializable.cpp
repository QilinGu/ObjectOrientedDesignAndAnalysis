#include "stdafx.h"
#include "Serializable.h"

Serializable::Serializable()
{
	file = "members.pr";
}

Serializable::~Serializable()
{
}

void Serializable::save(vector<Member> &vMember)
{
	ofstream fileWriter(file);
	size_t vSize = vMember.size();
	fileWriter.write((char*)&vSize, sizeof(vSize));
	fileWriter.write((char*)&vMember[0], vSize * sizeof(Member));
	fileWriter.close();
}

vector<Member> Serializable::load()
{
	vector<Member> newVMember;
	size_t vSize;
	ifstream fileReader(file);
	fileReader.read((char*)&vSize, sizeof(vSize));
	newVMember.resize(vSize);
	fileReader.read((char*)&newVMember[0], vSize * sizeof(Member));
	fileReader.close();

	return newVMember;
}
