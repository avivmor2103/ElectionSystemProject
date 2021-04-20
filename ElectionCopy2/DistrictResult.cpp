#include "DistrictResult.h"

DistrictResult::DistrictResult()
{
    this->lSize = 0;
    this->phSize = 1;
    try
    {
        result = new DistrictVotes[phSize];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

DistrictResult::~DistrictResult() {
    delete[] result;
}

DistrictResult::DistrictResult(const DistrictResult& res)
{
    this->lSize = res.lSize;
    this->phSize = res.phSize;
    this->result = res.result;
}

int DistrictResult::getNumOfVotes(int partyId) const
{
    return result[partyId].numberOfVoters;
}

int DistrictResult::getLSize() const {
    return  this->lSize;
}

void DistrictResult::addParty(const Party* party)
{
    if (lSize == phSize) {
        phSize *= 2;
        DistrictVotes* temp = nullptr;
        try
        {
            temp = new DistrictVotes[phSize];
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        memcpy(temp, result, lSize * sizeof(DistrictVotes));
        delete[]result;
        result = temp;
    }
    result[lSize].party = party;
    lSize++;
}

void DistrictResult::saveResults(ofstream& file)const
{
    int partyid;
    for (int i = 0; i < lSize; i++) {
        partyid = result[i].party->getPartyID();
        file.write(rcastcc(&partyid), sizeof(int));
        file.write(rcastcc(&(result[i].numberOfVoters)), sizeof(int));
        file.write(rcastcc(&(result[i].numOfReps)), sizeof(int));
        if (!file.good())
            throw "problem occurred while loading data from the file";
    }
}

void DistrictResult::loadDistricResults(ifstream& file,  const PartyArr& partyList)
{
    int size;
   
    file.read(rcastc(&size), sizeof(int));
    if (!file.good())
        throw "problem occurred while loading data from the file";
    delete[]result;
    try
    {
        result = new DistrictVotes[size];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    DistrictVotes* newDisVotes = nullptr;
    for (int i = 0; i < size; i++) {
        try
        {
            newDisVotes = new DistrictVotes(file, partyList);
        }
        catch (bad_alloc& ex)
        {
            cout << "Error:" << ex.what() << endl;
            exit(1);
        }
        if (!file.good())
            throw "problem occurred while loading data from the file";
        result[i].party = newDisVotes->party;
        result[i].numberOfVoters = newDisVotes->numberOfVoters;
        result[i].numOfReps = newDisVotes->numOfReps;
        newDisVotes = nullptr;
    }
    lSize = size;
    phSize = size;
    delete newDisVotes;
}

DistrictResult::DistrictVotes::DistrictVotes(ifstream& file, const PartyArr& partyList)
{
    int paryId, numOfVotes, numOfReps;
    file.read(rcastc(&paryId), sizeof(int));
    file.read(rcastc(&numOfVotes), sizeof(int));
    file.read(rcastc(&numOfReps), sizeof(int));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";
    }
    this->party = &partyList.getParty(paryId);
    this->numberOfVoters = numOfVotes;
    this->numOfReps = numOfReps;
}

const DistrictResult& DistrictResult::operator=(const DistrictResult& origin)
{
    this->lSize = origin.lSize;
    this->phSize = origin.phSize;
    delete[]result;
    result = new DistrictVotes[phSize];
    for (int i = 0; i < lSize; i++) {
        result[i].numberOfVoters = origin.result[i].numberOfVoters;
        result[i].numOfReps = origin.result[i].numOfReps;
        result[i].party = origin.result[i].party;
    }
    return *this;
}