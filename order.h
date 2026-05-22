#pragma once
#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
using namespace std;
class order
{
    public:
    string ID, destination;
    vector<item> cargoOuts;

    order(string ID_,  string destination);
    void addItem(item cargo)const;
    void showOrder()const;
    void showDestination()const;
    bool isOrderPossible()const;
};