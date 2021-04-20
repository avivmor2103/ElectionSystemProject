#pragma once
#include "District.h"
class District;
class UnionDistrict : public District
{
public:
	UnionDistrict(string disName, int disId, int numOfRep, bool isShared = false);

	//this function read a union District from a file
	UnionDistrict(ifstream& file, bool isShared = false);

	virtual ~UnionDistrict();

	//this function return the index of the party who won in this district
	int getWinParty()const;

	//	this function set the electors to parties
	void setElectors();
	virtual void printMySelf(ostream& os, const District& district)const;


};

