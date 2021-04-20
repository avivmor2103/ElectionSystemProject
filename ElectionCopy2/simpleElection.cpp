#include "simpleElection.h"

simpleElection::simpleElection(int totalRepNum) : Election()
{
	if (totalRepNum < 0)
		throw "Illegal number of representatives value.";
	Election::addDistrict("simple Election",totalRepNum,true);
}

simpleElection::simpleElection(const Date& date, int totalRepNum ):Election(date)
{
	if (totalRepNum < 0)
		throw "Illegal number of representatives value.";
	Election::addDistrict("simple Election", totalRepNum, true);
}

simpleElection::~simpleElection() {}

void simpleElection::addCitizen(const string& name, const string& id, int yearOfBirth, int  disId)
{
	Election::addCitizen(name, id, yearOfBirth, disId);
}

void simpleElection::addRep(int partyId, const Citizen* rep, int disId)
{
	Election::addRep(partyId, rep, disId);
}

void simpleElection::addVote(int disId,const Party* party)
{
	Election::addVote(disId, party);
}

void simpleElection::printDistrictStatistics(const District& dis)
{
	cout << "District's votes precent: " << dis.getVotePrecent() << "%" << endl;
	cout << "* * * * * * * * * * * *" << endl;
}
