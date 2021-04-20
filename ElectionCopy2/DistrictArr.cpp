#include "DistrictArr.h"


DistrictArr::DistrictArr(){}

DistrictArr::~DistrictArr(){}

const District& DistrictArr::getDistrict(int disId) const
{
    for (int i = 0; i < dArr.size(); i++) {
        if (dArr[i]->getIdNum() == disId)
            return *dArr[i];
    }
}

District* DistrictArr::addDistrict(string name, int representatives,bool isShared)
{
    District* newDis=nullptr;
    if (isShared)
    {
        try
        {
            newDis = new shareDistrict(name, dArr.size() + 1, representatives, true);
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
    }
    else
    {
        try
        {
            newDis = new UnionDistrict(name, dArr.size() + 1, representatives, false);
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
    }
    dArr.push_back(newDis);;
    return newDis;
}

void DistrictArr::addParty(const Party* party)
{
    for (int i = 0; i < dArr.size(); i++) {
        dArr[i]->addParty(party);
    }
}

void DistrictArr::addVote(const Party* party, int disId)
{
    for (int i = 0; i < dArr.size(); i++) {
        if(dArr[i]->getIdNum() == disId) {
             dArr[i]->addVote(party);
        }
     }
}

const Citizen* DistrictArr::findCitizen(string& id)const 
{
    const Citizen* citizen = nullptr;
    int i = 0;
    while (citizen == nullptr && i < dArr.size()) {
        citizen = dArr[i]->getCitizen(id);
        i++;
    }
    return citizen;
}

void DistrictArr::saveDistrictArr(ofstream& file)const
{
    int size = dArr.size();
    file.write(rcastcc(&size), sizeof(int));
    for (int i = 0; i < dArr.size(); i++) {
        dArr[i]->saveDistrict(file);
        if (!file.good())
            throw "problem occurred while loading data from the file";
    }    
}

void DistrictArr::saveResultsArr(ofstream& file)const
{
    for (int i = 0; i < dArr.size(); i++) {
        dArr[i]->saveResults(file);
        if (!file.good()) 
          throw "problem occurred while loading data from the file";
    }
}

void DistrictArr::loadDistricts(ifstream& file)
{
    dArr.clear();
    int size;
    bool isShare;
    District* newDis = nullptr;
    file.read(rcastc(&size), sizeof(int));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";
    }      
    for (int i = 0; i < size; i++) {
        file.read(rcastc (&isShare), sizeof(bool));
        if (isShare) {
            try
            {
                newDis = new shareDistrict(file, isShare);
            }
            catch (std::bad_alloc& ex)
            {
                cout << ex.what() << endl;
                exit(1);
            }
        }
        else
        {
            try
            {
                newDis = new UnionDistrict(file, isShare);
            }
            catch (std::bad_alloc& ex)
            {
                cout << ex.what() << endl;
                exit(1);
            }
        }
        newDis->loadCitizenArr(file);
        dArr.push_back(newDis);
        if (!file.good()) {
            throw "problem occurred while loading data from the file";
        }
    }
}

void DistrictArr::loadDistrictResults(ifstream& file, const PartyArr& partyList)
{
    for (int i = 0; i < dArr.size(); i++) {
        dArr[i]->loadDistrictResults(file, partyList); 
    }
}

District& DistrictArr::operator[](int i)
{
    return *dArr[i];
}

const District& DistrictArr::operator[](int i) const
{
    return *dArr[i];
}

ostream& operator<<(ostream& os, const DistrictArr& disArr)
{
    for (int i = 0; i < disArr.getlSize(); i++) {
          cout << "* * * * * * * * * * * * * ";
          cout << disArr.getDistrict(i);
    }
    return os;
} 
