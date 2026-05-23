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
    

// Wyświetlanie 
    storage::storage(int row_min, int row_max, int column_min, int column_max, int rack_min, int rack_max) : 
        row_min(row_min), row_max(row_max),
        column_min(column_min), column_max(column_max),
        rack_min(rack_min), rack_max(rack_max) {}

    std::vector<int> storage::getSize(){ return {1+row_max-row_min, 1+column_max-column_min, 1+rack_max-rack_min}; }

//DO MODYFIKACJI
    std::string storage::showallItems(){
        std::string item_list;
        for(auto& i : inventory){
            auto [x, y, z] = i.first.coordinates;
            item_list = "Koordynaty: " +std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+
            "  Numer id: "+i.second.id_number+"  Nazwa: "+i.second.name+"  Ilość: "+std::to_string(i.second.unit)+"\n";
        } 
    };

//DO DOKOŃCENIA
    std::string findItems_by_id(std::string input){

    };


    std::string findItems_by_name(std::string input){

    };


    std::string findItems_by_coord(std::string input){

    };






// Logika
    //sprawdza czy przedmiot wogóle jest na liście
    std::string storage::checkItem_list(item item_){ 
        for(auto& i : id_list){
            if(item_.id_number == i.first ){
                if(item_.name == i.second){ return; }
            return "Id w zamówieni nie pasuje do listy katalogowej";
            }
        } 
        id_list.insert({item_.id_number, item_.name});
    }


    void storage::findItems(item item_) {
    findItems_buffer.clear();
    std::string id = item_.id_number;
        for (auto& [key, val] : inventory) {
            if (val.id_number == id) {
                findItems_buffer.push_back({key, val});
            }
        }
    }


    std::string storage::checkItems(item item_) {
    pick_buffer.clear();
    std::string id = item_.id_number;
    double left = item_.unit;
    findItems(item_);  // wypełnia findAll_buffer

        for (auto& [loc, item] : findItems_buffer) {
            if (left <= 0) break;

            double take = item.unit;
            pick_buffer.push_back({loc, take});
            left -= take;
            if (left < 0){ 
                pick_buffer.pop_back();
                pick_buffer.push_back({loc, left+take});
            }
        }

        if (left > 0) { return "Nie znaleziono dostatecznej ilości produktów"; }
        return "Znaleziono dostateczną ilość produktów";
    }


    std::string storage::makeRequest(std::vector<item> list){
        request.clear();
        for(auto& i : list){
            std::string id_check = storage::checkItem_list(i);
            if(id_check == "Złe przypisane id"){ return id_check; }  //ZWRACA BŁĄD
            std::string item_check = storage::checkItem_list(i);
            if(item_check == "Nie znaleziono dostatecznej ilości produktów"){ return item_check; }  //ZWRACA BŁĄD
            
            request.insert(request.end(), pick_buffer.begin(), pick_buffer.end());
        }
        return "Załadowa ";
    } 














