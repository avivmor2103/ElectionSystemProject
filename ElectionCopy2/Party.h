#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"RepsByDis.h"
#include "FileManger.h"


class District;
class DistrictArr;
class Party{
private:
	string partyName;
	int partyID;
	int numberOfVoters;
	int numOfElectors;
	const Citizen* president;
	RepsByDis repsByDis;

public:
	Party();
	Party(const Party& origin)=delete;
	//this function loads party from a file
	Party(ifstream& file,  const DistrictArr& disList);
	Party(const string& name, const Citizen* president,int partyID);
	~Party();

	/***********Getters************/
	const string getPartyName()const {
		return partyName;
	}
	int getNumberOfVotes()const {
		return this->numberOfVoters;
	}
	int getPartyID()const {
		return partyID;
	}
	int getnumOfElectors()const {
		return numOfElectors;
	}
	const Citizen& getPresident()const { 
		return *president;
	}
	const RepsByDis& getRepsArr()const {
		return repsByDis;
	}
	const Reps& getRepsByDis(int disId)const;

	
	/***********Setters************/
	bool setName(const string name);
	// this function rest num of voters and electors for a party
	bool resetVoters();

	//this function add rep to the  rep party list
	void addRep(const Citizen* rep, int disId);
	
	//this function add district to the rep party list
	void addDistrict(const District* district);
	
	//this function gets a number of electors and adds it to total electors of the party
	void addElectors(int numOfElectors);
	
	//this function gets a number of votes and adds it to total votes of the party
	void addVotes(int numOfVotes);
	
	//this function saves a party to a file
	void saveParty(ofstream& file)const;
	//this function loads a rep party list from a file
	void loadReps(ifstream& file,const DistrictArr& disList);

	friend ostream& operator<<(ostream& os, Party& party);
	friend ostream& operator<<(ostream& os, const Party& party);

	const Party& operator=(const Party& origin) = delete;
	bool operator>(const Party& origin);

};