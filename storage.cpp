#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "storage.h"
#include "coord.h"
#include "supply.h"
#include "order.h"

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


// Wyświetlanie, wszystkie poza getSize wyświetlają item_list która jest "Odpowiedzią" metody, zarówno błędu jaki i wyniku

    std::string storage::getSize(){ return std::to_string(1+row_max-row_min)+" "+std::to_string(1+column_max-column_min)+" "+std::to_string(1+rack_max-rack_min); }

    std::string storage::showallItems(){  //Jeden duży string odgradzany /n 
        std::string item_list = "";
        for(auto& i : inventory){
            auto [x, y, z] = i.first.coordinates;
            item_list += "Koordynaty: " +std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+
            "  Numer id: "+i.second.id_number+"  Nazwa: "+i.second.name+"  Ilość: "+std::to_string(i.second.unit)+"\n";
        } 
        return item_list;
    }

    std::string storage::findItems_by_id(std::string input){
        std::string item_list = "";
        for(auto& i : inventory){
            if(input==i.second.id_number){
            auto [x, y, z] = i.first.coordinates;
            item_list += "Koordynaty: " +std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+
            "  Numer id: "+i.second.id_number+"  Nazwa: "+i.second.name+"  Ilość: "+std::to_string(i.second.unit)+"\n";
            }
        } 
        if(item_list == ""){item_list = "Nieznaleniono, żadnych przedmiotów";};
        return item_list;
    }


    std::string storage::findItems_by_name(std::string input){
        std::string item_list = "";
        for(auto& i : inventory){
            if(input==i.second.name){
            auto [x, y, z] = i.first.coordinates;
            item_list += "Koordynaty: " +std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+
            "  Numer id: "+i.second.id_number+"  Nazwa: "+i.second.name+"  Ilość: "+std::to_string(i.second.unit)+"\n";
            }
        }
        if(item_list == ""){item_list = "Nieznaleniono, żadnych przedmiotów";};
        return item_list;
    }


    std::string storage::findItems_by_coord(std::string input){     //Uznajmy że input to: x,y,z funkcja rozkłąda przecinki, można uprościć
            std::string item_list = "";
            std::stringstream ss(input);
            int x, y, z;
            char comma;
            ss >> x >> comma >> y >> comma >> z;
            try {
                item& i = inventory.at({x,y,z});
                item_list = "Koordynaty: " +std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+
                "  Numer id: "+i.id_number+"  Nazwa: "+i.name+"  Ilość: "+std::to_string(i.unit)+"\n";
            } catch (std::out_of_range& e) {
                item_list = "Nieznaleniono, żadnych przedmiotów";
            }
            return item_list;

    }






// Logika
    //Większość wyjść to std::string aby dawać feedback dla warunków, czy coś zadzaiałało czy nie, dla wyświetlania stanu
    //sprawdza czy przedmiot wogóle jest na liście
    std::string storage::checkItem_list(item item_){ 
        for(auto& i : id_list){
            if(item_.id_number == i.first ){
                if(item_.name == i.second){ return "Znaleziono id"; }
            return "Złe przypisane id";
            }
        } 
        id_list.insert({item_.id_number, item_.name});
        return "";
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
    findItems(item_);
    if (findItems_buffer.empty()) { return "Nie znaleziono żadnych przedmiotów"; }

        for (auto& [loc, item_p] : findItems_buffer) {
            if (left <= 0) break;

            double take = std::min(item_p.unit,left);
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


    std::string storage::assignStorage(item item_){
        for (int row = row_min; row <= row_max; row++) {
            for (int column = column_min; column <= column_max; column++) {
                for (int rack = rack_min; rack <= rack_max; rack++) {
                    coord c(row, column, rack);
                    if (inventory.find(c) == inventory.end()) {
                        coord loc(row, column, rack);
                        supply_request.push_back({loc,item_});
                        return "Znaleziono miejsce";  // pierwsze wolne miejsce
                    }
                }
            }
        }
    return "Brak wolnego miejsca";
    }


    std::string storage::orderRequest(std::vector<item> list){
        order_request.clear();
        for(auto& i : list){
            std::string id_check = storage::checkItem_list(i);
            if(id_check == "Złe przypisane id"){ return id_check; }  //ZWRACA BŁĄD
            std::string item_check = storage::checkItems(i);
            if(item_check == "Nie znaleziono dostatecznej ilości produktów" || item_check == "Nie znaleziono żadnych przedmiotów"){ return item_check; }  //ZWRACA BŁĄD
            
            order_request.insert(order_request.end(), pick_buffer.begin(), pick_buffer.end());
        }
        return "Zaakceptowano";
    } 


    std::string storage::supplyRequest(std::vector<item> list){
        supply_request.clear();
        for(auto& i : list){
            std::string id_check = storage::checkItem_list(i);
            if(id_check == "Złe przypisane id"){ return id_check; }  //ZWRACA BŁĄD
            std::string item_check = storage::assignStorage(i);
            if(item_check == "Brak wolnego miejsca"){ return item_check; }  //ZWRACA BŁĄD
        }
        return "Zaakceptowano";
    }

    















