#pragma once
#include "FileManger.h"
#include "Party.h"

class District;
class PartyArr
{
	private:
		DynamicArray<Party*> pArr;
	
	public:
		PartyArr();
		PartyArr(const PartyArr& origin);
		~PartyArr();

		/***********Getters************/
		const Party& getParty(int partyId)const;
		int getlSize()const { 
			return pArr.size();
		}

		//this function add a new party to the party arr 
		Party* addParty(const string& name, const Citizen* president);
		
		//this function add a district to the reps arr in all parties 
		void addDistrict(District* newdis);
		
		//this function add rep to the suitable party in the district he represntive at
		void addRep(int partyId, int disId, const Citizen* newRep);
		
		//this function add  votes to the party with the same id that is given
		void addVotes(int partyId, int votes);
		
		//this function add electors to the party with the same id that is given
		void addElectors(int partyId, int numOfElectors);

		//this function search for a rep by id, if found in any party the function return true,flase otherwise
		bool CheckRep(const string& repId)const;
		
		//this function saves the party arr to a file
		void savePartyArr(ofstream& file)const;

		//this function loads the party arr from a file
		void loadPartyArr(ifstream& file,const DistrictArr& disList);
		
		Party& operator[](int i) {
			return *pArr[i];
		} 
		const Party& operator[](int i)const {
			return *pArr[i];
		}
		const PartyArr& operator=(const PartyArr& origin) = delete;
};

