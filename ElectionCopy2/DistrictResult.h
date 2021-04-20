#pragma once
#include"FileManger.h"
#include "PartyArr.h"

class Party;

class DistrictResult
{
	struct DistrictVotes {

		const Party* party;
		int numberOfVoters;
		int numOfReps;
		DistrictVotes() {
			party = nullptr;
			numberOfVoters = 0;
			numOfReps = 0;
		}
		//this function load Districts votes from file
		DistrictVotes(ifstream& file,const  PartyArr& partyList);
	};
private:
	int phSize;
	int lSize;
	DistrictVotes* result;

public:
	DistrictResult();
	~DistrictResult();
	DistrictResult(const DistrictResult& res);
	
	/****************Getters*************/
	int   getNumOfVotes(int partyId)const;
	int   getLSize()const;

	//this function add a pointer to a party in the results arr 
	void addParty(const Party* party);

	//this funtion save the results arr to a file
	void saveResults(ofstream& file)const;

	//this funtion loads the results arr from a file
	void loadDistricResults(ifstream& file, const PartyArr& partyList);

	DistrictVotes& operator[](int ind) { 
		return result[ind];
	}
	const DistrictVotes& operator[](int ind) const { 
		return result[ind]; 
	}
	const DistrictResult& operator=(const DistrictResult& origin);
};

