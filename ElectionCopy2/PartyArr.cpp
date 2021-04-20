#include "PartyArr.h"

PartyArr::PartyArr(){}

PartyArr::PartyArr(const PartyArr& origin)
{
    this->pArr = origin.pArr;
}

PartyArr::~PartyArr(){}

const Party& PartyArr::getParty(int partyId) const
{
    for (int i = 0; i < pArr.size(); i++) {
        if (pArr[i]->getPartyID() == partyId)
            return *pArr[i];
    }
}

Party* PartyArr::addParty(const string& name, const Citizen* president)
{
    Party* newP = nullptr;
    try
    {
        newP = new Party(name, president, pArr.size() + 1);
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    pArr.push_back(newP);
    return newP;
}

void PartyArr::addDistrict(District* newdis)
{
    for (int i = 0; i < pArr.size(); i++) {
        pArr[i]->addDistrict(newdis);
    }
}

void PartyArr::addRep(int partyId, int disId, const Citizen* newRep)
{
   for (int i = 0; i < pArr.size(); i++) {
      if (pArr[i]->getPartyID() == partyId) {
            pArr[i]->addRep(newRep, disId);
      }
   }
}

void PartyArr::addVotes(int partyId, int votes)
{
    for (int i = 0; i < pArr.size(); i++) {
        if (pArr[i]->getPartyID() == partyId) {
            pArr[i]->addVotes(votes);
        }
    }
}

void PartyArr::addElectors(int partyId, int numOfElectors)
{
    for (int i = 0; i < pArr.size(); i++) {
        if (pArr[i]->getPartyID() == partyId) {
            pArr[i]->addElectors(numOfElectors);
        }
    }
}

bool PartyArr::CheckRep(const string& repId) const
{
    for (int i = 0; i < pArr.size(); i++) {
        if (pArr[i]->getPresident().getId() == repId)
            throw "This citizen is already represents other party";
        for (int j = 0; j < pArr[i]->getRepsArr().getlSize(); j++) {
            for(int k=0;k< pArr[i]->getRepsArr()[j].getlSize();k++) {
                 if (pArr[i]->getRepsArr()[j].getRepId(k) == repId)
                     throw "This citizen is already represents other party";
            }
        }
    }
    return false;
}

void PartyArr::savePartyArr(ofstream& file)const
{
    int size = pArr.size();
    file.write(rcastcc(&size), sizeof(int));
    for (int i = 0; i < size; i++) {
        pArr[i]->saveParty(file);
    }
}

void PartyArr::loadPartyArr(ifstream& file, const DistrictArr& disList)
{
    int size;
    Party* newParty = nullptr;
    file.read(rcastc(&size), sizeof(int));
    if (!file.good()) 
        throw "problem occurred while loading data from the file";
    pArr.erase(pArr.begin(),pArr.end());
 
    for (int i = 0; i < size; i++) {
        try
        {
            newParty = new Party(file, disList);
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        newParty->loadReps(file, disList);
        pArr.push_back(newParty);
        if (!file.good()) {
            throw "problem occurred while loading data from the file";
        }
    }
    newParty = nullptr;
    delete newParty;
}

