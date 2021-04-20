#include "CitizenArr.h"


CitizenArr::CitizenArr(){}

CitizenArr::~CitizenArr(){}

Citizen* CitizenArr::getCitizenById(const string& id) const
{
    map<string, Citizen*>::const_iterator  itr= cArr2.find(id);
    if (itr == cArr2.end())return nullptr;
    return  itr->second;
}
                
void CitizenArr::addCitizen(const string& name, const string& id, int yearOfBirth, District* dis, bool vote)
{
    cArr2.insert(pair< string, Citizen* >(id, new Citizen(name, id, yearOfBirth, dis, vote)));
}


void CitizenArr::saveCitizenArr(ofstream& file)const
{
    for (auto itr:cArr2) {
        itr.second->saveCitizen(file);
        if (!file.good())
            throw "problem occurred while loading data from the file";
    }
}

void CitizenArr::loadCitizens(ifstream& file,const District* district)
{
    int size;
    Citizen* newCit = nullptr;
    file.read(rcastc(&size), sizeof(int));
    cArr2.erase(cArr2.begin(), cArr2.end());
    for (int i = 0; i < size; i++) {
        newCit=new Citizen(file, district);
        if (!file.good())
            throw "problem occurred while loading data from the file";
        cArr2.insert(pair< string, Citizen*>(newCit->getId(), newCit));
    }
}




