#include"Order.h"
#include"cargo.h"
#include<iostream>
#include<vector>
using namespace std;
Order::Order(string ID_,  string destination): ID(ID_), destination(destination) {}
void Order::addCargo(Cargo cargo)
{
    cargoOuts.push_back(cargo);
}
void Order::showOrder()const
{
    cout<<"Zamówienie ID: "<<ID<<", Destynacja: "<<destination<<endl;
    if(towary.empty())
    {
        cout<<"Brak towarów w zamówieniu."<<endl;
    }
    else
    {
        cout<<"Towary w zamówieniu:"<<endl;
        for(size_t i=0; i<towary.size(); i++)
        {
            cout<<"- "<<towary[i].nazwa<<", Ilość: "<<towary[i].ilosc<<endl;
        }
    }
}
void Order::showDestination()const
{
    cout<<"Destynacja zamówienia ID "<<ID<<": "<<destination<<endl;
}
bool Order::isOrderPossible()const
{
    //Przeszukiwanie magazynu
}