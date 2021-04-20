#pragma once
#include"FileManger.h"
#include "shareDistrict.h"
#include "UnionDistrict.h"

class DistrictArr
{
	private:
		DynamicArray<District*>dArr;	
	public:
		DistrictArr();
		DistrictArr(const DistrictArr& origin)=delete;
		~DistrictArr();

		/*******Getters******/
		int getlSize()const {
			return dArr.size();
		  }
		//this function gets district id number and return the district with the same id number
		const District& getDistrict(int disId)const;

		//this function add a district and return a pointer to the district that added
		District* addDistrict(string name, int representatives,bool isShared);
		
		//this function add party to all district(in the results arr)
		void addParty(const Party* partynum);
		
		//this function add a vote to the party in the district
		//(the function gets the disId and find the district to add vote to)
		void addVote(const Party* party, int disId);
		
		//this function search a citizen by id and return its address
		const Citizen* findCitizen(string& id)const ;
		
		//this function saves the district arr to the file
		void saveDistrictArr(ofstream& file)const;
		
		//this function saves the results arr to the file
		void saveResultsArr(ofstream& file)const;

		//this function loads the district arr from the file
		void loadDistricts(ifstream& file);

		//this function loads the results arr from the file
		void loadDistrictResults(ifstream& file, const PartyArr& partyList);
		
		District& operator[](int i);
		const District& operator[](int i)const ;
		friend ostream& operator<<(ostream& os, const DistrictArr& disArr);
		const DistrictArr& operator=(const DistrictArr& origin) = delete;
		


};

