#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
using namespace std; 
supply::supply(string ID_) : ID(ID_) {}
void Supply::addSupply(item item)const
{
    itemIns.push_back(item);
}
void Supply::showSupply()const
{
    cout<<"Dostawa ID: "<<ID<<endl;
    if(itemIns.empty())
    {
        cout<<"Brak towarów w dostawie."<<endl;
    }
    else
    {
        cout<<"Towary w dostawie:"<<endl;
        for(size_t i=0; i<itemIns.size(); i++)
        {
            cout<<"- "<<itemIns[i].nazwa<<", Ilość: "<<itemIns[i].ilosc<<endl;
        }
    }
}
void Supply::fillStorageWithSupply()const
{
    //Dodawanie towarów z dostawy do magazynu
}