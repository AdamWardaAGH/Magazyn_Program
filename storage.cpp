#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "storage.h"
#include "coord.h"

/*
Ma posiadać podstawowe info odnośnie wielokości magazynu, jaka jest początkowy i końcowy numer danej półki

list w std::map przechowuje id jako klucza (list.first) i przypisane nazwy produktów jako wartość (list.second)
storage w std::map przechowuje dane o tym co gdzie jest
szybszy od std::vector lista gdzie elementy mają unikatowy koordynat
*/
    
    storage::storage(int row_min, int row_max, int column_min, int column_max, int rack_min, int rack_max) : 
        row_min(row_min), row_max(row_max),
        column_min(column_min), column_max(column_max),
        rack_min(rack_min), rack_max(rack_max) {}

    std::vector<int> storage::getSize(){ return {1+row_max-row_min, 1+column_max-column_min, 1+rack_max-rack_min}; }

    //sprawdza czy przedmiot wogóle jest
    std::string storage::checkItem_list(item item_){ 
        for(auto& i : id_list){
            if(item_.id_number == i.first ){
                if(item_.name == i.second){ return; }
            return "Złe przypisane id";
            }
        } 
        id_list.insert({item_.id_number, item_.name});
    }

    //sprawdza czy przedmot jest i ilość jest wystarczająca
    std::string storage::findItem(item item_){

        auto it = std::find_if(inventory.begin(), inventory.end(),
        [&](const std::pair<coord, item>& para) {
        return para.second.id_number == item_.id_number && para.second.unit <= item_.unit;
        });

        if (it != inventory.end()) { //ostani element poza inventory
        buffer = it->first; //obiekt z wskażnikiem na koordynaty
        }else{
            return "Nie ma wystarczającej ilości";
        }
    }


    std::string storage::makeRequest(std::vector<item> list){
            for(auto& i : list){
            std::string id_check = storage::checkItem_list(i);
            if(id_check == "Złe przypisane id"){ return id_check; }  //ZWRACA BŁĄD
            std::string item_check = storage::findItem(i);
            if(item_check == "Nie ma wystarczającej ilości"){ return item_check; }
            request.push_back(buffer);
        }
        return "Załadowa ";
    } 














