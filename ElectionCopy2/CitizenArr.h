#pragma once  
#include "Citizen.h"
#include <map>
class CitizenArr
{
	private:
		map<string, Citizen*>cArr2;
	public:
		CitizenArr();
		CitizenArr(const CitizenArr& origin) = delete;
		~CitizenArr();
		/*****	Getters	****/
		int getlSize()const { 
			return cArr2.size();
		}
		Citizen* getCitizenById(const string& id)const;
	
		/*********This functions add a ptr to citizen to arr*******/
		void addCitizen(const string& name, const string& id, int yearOfBirth, District* dis, bool vote = false);
		//void addCitizen(CitizenPtr citizen);
		
		//this function save the citizen arr to a file
		void saveCitizenArr(ofstream& file)const;

		//this function load the citizen arr from a file
		void loadCitizens(ifstream& file, const District* district);

		const Citizen& operator[](int i)const {
			int counter = 0;
			for (auto itr : cArr2) {
				if (counter == i)
					return *itr.second;
				counter++;
			}
		}
		
		const CitizenArr& operator=(const CitizenArr& arr)=delete;





};

