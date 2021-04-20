#pragma once
#include "Election.h"

class Election;
class simpleElection : public Election
{
public:
	simpleElection(int totalRepNum=0);
	simpleElection(const Date& date, int totalRepNum = 0);
	virtual ~simpleElection();

   	//this functoin add a citizen in simple election (the disId will always be 1)
	virtual void addCitizen(const string& name, const string& id, int yearOfBirth, int  disId1)override;
	
	//this functoin add a represntive in simple election (the disId will always be 1)
	virtual void addRep(int partyId, const Citizen* rep, int disId)override;
	
	//this functoin add a vote in simple election (the disId will always be 1)
	virtual void addVote(int disId,const Party* party)override;

	//this function print the ditrict votes statistics
	virtual void printDistrictStatistics(const District& dis);
};
