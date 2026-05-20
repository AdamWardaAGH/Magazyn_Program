#pragma once
#include"cargo.h"
#include"storage.h"
#include<string>
#include<vector>
using namespace std;
class Supply
{
    public:
    string ID;
    vector<Cargo> CargoIns;
    Supply(string ID_);
    void addSupply(Cargo cargo)const;
    void showSupply()const;
    void fillStorageWithSupply()const;
};