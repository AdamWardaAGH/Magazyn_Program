#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
#include"supply.h"

/*
Klasa odpowiedzialna za dostawy, czyli generowanie listy obiektów potrzebnych do dostarczenia do magazynu
*/

void supply::addItem(std::string buffer_1,std::string buffer_2,std::string bufr_3){
        double buffer_3=std::stod(bufr_3);
            item item_(buffer_1, buffer_2, buffer_3);
            supply_list.push_back(item_);
    }
