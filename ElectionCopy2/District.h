 #pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "FileManger.h"
#include "DistrictResult.h"
#include "CitizenArr.h"
#include <fstream>
#include <iostream>
class UnionDistrict;
class shareDistrict;
class District {

protected:
	string name;
	int idNumber;
	int representatives;
	int numOfpeople;
	int numOfVotes;
	float votedPrecent;
	bool isShared;
	CitizenArr citizenArr;
	DistrictResult electionResult;
	

public:
	District();
	District(string& disName,int disId,int numOfRep,bool isShared=false);
	District(const District& district);
	
	//this function reads a District from a file
	District(ifstream& file, bool isShared = false);
	
	virtual ~District();
	
	/******Getters******/
	const string& getName()const;
	int getIdNum() const;
	int getNumOfRep()const;
	int getNumOfPeople()const;
	int getNumberOfVoters() const;
	float getVotePrecent()const;
	
	//this funtion gets an id and search the citizen with this id and return its address
	 Citizen* getCitizen(const string& id) const {
		return citizenArr.getCitizenById(id);
	}
	
	 //this function return the citizen arr
	 const CitizenArr& getCitizenArr() const {
		return citizenArr;
	}
	
	 //this function return the results arr
	 const DistrictResult& getDisResults()const {
		 return electionResult;
	 }
	 
	 /******Setter******/
	bool setName(const string name);
	bool setRepresentatives(int representatives);
	bool setID(int id);
	bool setNumOfPeople(int numOfPeople);
	bool setnumOfVoters(int numOfVoters);
	bool setVotesPrecent(float votesPrecent);
	
	//this function return if the district is shared or not 
	bool isSharedDis() {
		return isShared;
	}
	
	// this function add a party to the results arr
	void addParty(const Party* party);
	
	//this function add a vote to the suitable party in the results arr
	void addVote(const Party* party);
	
	//this function add a party to the citizen arr
	void addCitizen(string name, string id, int yearOfBirth, int disId);
	
	//this function responsable for calculate the Election Results in the district
	void calculateElectionResults();
	
	//this function is respnable to divide the reps to parties
	void checkNumOfRepresentativesNum(float vtingRatio);
		
	//this function gets the party who won in the districts
	int getWinParty()const;

	//this function sets the electors to the parties
	virtual void setElectors() {}
	
	//this function save the district to the file
	void saveDistrict(ofstream& file)const;

	//this function saves the result arr to the file
	void saveResults(ofstream& file)const;

	//this function loads the citizen arr from a file
	void loadCitizenArr(ifstream& file);

	//this function loads the districts results  arr from a file
	void loadDistrictResults(ifstream& file, const PartyArr& partList);

	const District& operator=(const District& district);
	friend ostream& operator<<(ostream& os, const District& district);
	virtual void printMySelf(ostream& os, const District& district)const{}

};