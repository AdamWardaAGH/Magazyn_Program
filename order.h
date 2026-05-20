#pragma once
#include"cargo.h"
#include"storage.h"
#include<string>
#include<vector>
using namespace std;
class Order
{
    public:
    string ID, destination;
    vector<Cargo> cargoOuts;
    order(string ID_,  string destination);
    void addCargo(Cargo cargo)const;
    void showOrder()const;
    void showDestination()const;
    bool isOrderPossible()const;
};