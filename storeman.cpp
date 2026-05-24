#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "storeman.h"
#include "storage.h"
#include "order.h"
#include "item.h"

/*
Przyjmuje order_request i supply_request i zmienia magazyn na podstawie instrukcji
*/
storeman::storeman(){}

storeman::storeman(std::string name_):name(name_){}

std::string storeman::executeOrder(std::string activation,storage& warehouse){
    if(activation == "Zaakceptowano"){
        for(auto& i : warehouse.order_request){
            warehouse.inventory.at(i.first).unit -= i.second;
            if(warehouse.inventory.at(i.first).unit <= 0){ warehouse.inventory.erase(i.first); }
        }
        return "Przedmioty przeniesione do zamówienia";
    }
    return "Nie przeniesiono do zamówienia";
}


std::string storeman::executeSupply(std::string activation,storage& warehouse){
    if(activation == "Zaakceptowano"){
        for(auto& i : warehouse.supply_request){
            warehouse.inventory.emplace(i.first, i.second);
        }
        return "Przedmioty przeniesione do magazynu";
    }
    return "Nie przeniesiono do zamówienia";
}