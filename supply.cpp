#include"cargo.h"
#include"storage.h"
#include<string>
#include<vector>
using namespace std;
Supply::Supply(string ID_) : ID(ID_) {}
void Supply::addSupply(Cargo cargo)const
{
    CargoIns.push_back(cargo);
}
void Supply::showSupply()const
{
    cout<<"Dostawa ID: "<<ID<<endl;
    if(CargoIns.empty())
    {
        cout<<"Brak towarów w dostawie."<<endl;
    }
    else
    {
        cout<<"Towary w dostawie:"<<endl;
        for(size_t i=0; i<CargoIns.size(); i++)
        {
            cout<<"- "<<CargoIns[i].nazwa<<", Ilość: "<<CargoIns[i].ilosc<<endl;
        }
    }
}
void Supply::fillStorageWithSupply()const
{
    //Dodawanie towarów z dostawy do magazynu
}