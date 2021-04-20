#include "Reps.h"
 #include "District.h"
 #include "DistrictArr.h"

Reps::Reps(const District* district, int phSize, int lsize)
{
    this->lSize = lsize;
    this->phSize = phSize;
    this->dis = district;
    if (lSize > phSize)
    {
        throw "Illigel size value";
    }
    try {
        repArr = new const Citizen * [phSize];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

Reps::Reps(ifstream& file, const DistrictArr& disList)
{ 
    int size, IDsize, disId;
    char* repId;
    lSize = 0;
    phSize = 1;
    file.read(rcastc(&disId), sizeof(int));
    file.read(rcastc(&size), sizeof(int));
    if (!file.good())
        throw "problem occurred while loading data from the file";
    dis=&disList.getDistrict(disId);
    delete[]repArr;
    try
    {
        repArr = new const Citizen * [size];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        file.read(rcastc(&IDsize), sizeof(int));
        try
        {
            repId = new char[IDsize];
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        file.read(repId, IDsize);
        if (!file.good())
            throw "A problem has occurred in this file.";
        repId[IDsize] = '\0';
        string id = repId;
        repArr[i] =(disList.findCitizen(id));
    }
    phSize = size;
    lSize = size;
}

Reps::~Reps(){
    for (int i = 0; i < lSize; i++)
        repArr[i] = nullptr;
    delete[]repArr;

}

int Reps::getlSize() const
{
    return this->lSize;
}

int Reps::getDisNum() const
{
    return dis->getIdNum();
}

const District* Reps::getDistrict() const
{
    return dis;
}

const string& Reps::getRepName(int ind) const
{
    return repArr[ind]->getName();
}

const string& Reps::getRepId(int ind) const
{
    return repArr[ind]->getId();
}

void Reps::addRepresentative(const Citizen* rep)
{
    if (lSize == phSize) {
        reSizeRepresentative();
    }
    repArr[lSize] = rep;
    lSize++;
}

void Reps::saveReps(ofstream& file)const
{
    int id= dis->getIdNum();
    int repIdNum;
    string repId;
    file.write(rcastcc(&id), sizeof(int));
    file.write(rcastcc(&lSize), sizeof(int));
    for (int i = 0; i < lSize; i++) {
        repId = repArr[i]->getId();
        repIdNum = repId.size();
        file.write(rcastcc(&repIdNum), sizeof(int));
        file.write(repId.c_str(), repIdNum);
    }
}

void Reps::reSizeRepresentative()
{
    phSize *= 2;
    const Citizen** temp = nullptr;
    try
    {
        temp = new const Citizen * [phSize];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
    }
    for (int i = 0; i < lSize; i++) {
        temp[i] = repArr[i];
        repArr[i] = nullptr;
    }
    delete[] repArr;
    repArr = temp; 
}

const Citizen& Reps::operator[](int i)
{
    return *repArr[i];
}

const Reps& Reps::operator=(const Reps& reps)
{
    this->dis = reps.dis;
    this->lSize = reps.lSize;
    this->phSize = reps.phSize;
    try
    {
         delete[]repArr;
        repArr = new const Citizen * [phSize];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    for (int i = 0; i < lSize; i++)
        this->repArr[i] = reps.repArr[i];
    
    return *this;
}