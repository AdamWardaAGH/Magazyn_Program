#pragma once
#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
using namespace std;
class supply
{
    public:
    string ID;
    vector<item> CargoIns;
    supply(string ID_);
    void addSupply(item cargo)const;
    void showSupply()const;
    void fillStorageWithSupply()const;
};