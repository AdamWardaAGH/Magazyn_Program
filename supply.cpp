#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
#include"supply.h"

/*
Klasa odpowiedzialna za dostawy, czyli generowanie listy obiektów potrzebnych do dostarczenia do magazynu
*/

void supply::addItems(){
        supply_list.clear();
        std::string in = "", buffer_1, buffer_2;
        double buffer_3;
        while(1){
            //name
            std::cin >> in;
            if(in == "exit"){break;}
            buffer_1 = in;
            //id
            std::cin >> in;
            if(in == "exit"){break;}
            buffer_2 = in;
            //unit
            std::cin >> in;
            if(in == "exit"){break;}
            buffer_3 = std::stod(in);

            item item_(buffer_1, buffer_2, buffer_3);
            supply_list.push_back(item_);
        }  
    }
