#pragma once
#include "DistrictArr.h"
#include "PartyArr.h"
#include "Date.h"
#include"Reps.h"
#include "FileManger.h"

struct DistrictVotes;
class Election {
	private:
		Date elecDate;
		DistrictArr disList;
		PartyArr partyList;

	public:
		Election();
		Election(const Date& date);
		Election(const Election& election);
		virtual ~Election();
		
		/********Getters*****/
		 Date& getDateOfElection(){ 
			return elecDate; 
		}
		const PartyArr& getPartyList()const { 
			return partyList;
		}
		const DistrictArr& getDistrictList()const { 
			return disList;
		}
		const District& getDistrict(int disId)const {
			return disList.getDistrict(disId);
		}
		
		//this function sets the election date
		bool SetDate(int day, int month, int year);
		
		//this function add party to the party Lisr
		void addParty(const string& name, const Citizen* president);
		
		//this function add district to the district Lisr
		virtual void addDistrict(const string& name, int repNumber,bool isShared);
		
		//this function add a citizen to the citizen list
		virtual void addCitizen(const string& name, const string& id, int yearOfBirth, int  disId);
		
		//this function add a rep to the party he belongs to
		virtual	void addRep(int partyId,const Citizen* rep, int disId);
		 
		//this function add a vote to the suitable party in the appropriate district 
		virtual void addVote(int  disId, const Party* party);
		
		//this function search for a citizen with a given id
		Citizen* findCitizen(const string& idNumber);
		
		//this function prints all district
		void printDistrictList();
		
		//this function prints all parties
		void printPartyList();
		
		//this function prints all citizens
		void printCitizenList();

		//this function shows the election results
		void showElectionResults();
		
		//this function print the Candidate from a given party
		void showCandidateParty(PartyArr& pList, int size, int* arrRep);
		
		//this function prints the reps that chosen forom a given party
		void printRepByVotePrecent(int size, const Reps& repList)const;
		
		//this function calculate the votes precent  int each district and return is
		float* getArrayOfVotesPrecent(const DistrictResult& votPerParty, int totalVotes, int numOfParties)const;
		
		//this function gets the her president name by party name
		const string getPresByPartyName(PartyArr pL, string partyName)const;
				
		//this function prints the party who wins in the district
		void printWinnerInDis(const District& dis, const PartyArr& partyList, int* partyIndex);
		
		//this function prints the district statistics
		virtual void printDistrictStatistics(const District& dis);
		
		//this function responable of  printing the selected reps form given party name 
		void printSelectedReps(const string partyName, const Reps& repList, int repSize, int numOfvoters, float votePrecent);

		//this function saves the election to a file
		void saveElection(ofstream& file)const;
		//this function load election from a file
		void loadElection(string path);
		//this function load district list from a file
		void loadDistricts(ifstream& file);
		//this function load party list from a file
		void loadParties(ifstream& file);
		//this function load resulst from a file
		void loadResults(ifstream& file);
		
		void operator=(const Election& election) = delete;

};
