#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "item.h"
#include "coord.h"

class storage {
public:
    //wartości z danymi
    int row_min, row_max;
    int column_min, column_max;
    int rack_min, rack_max;
    std::map <coord,item> inventory;
    std::map <std::string,std::string> id_list;

    //bufory
    coord buffer;
    std::vector<coord> request;

    storage(int row_min, int row_max,
        int column_min, int column_max,
        int rack_min, int rack_max);
    
    std::vector<int> getSize();

    //dodwanie do listy
    //czyste wyszukiwanie na bazie id,nazyw koordynatów

    std::string checkItem_list(item item_);
    std::string findItem(item item_);
    std::string makeRequest(std::vector<item> list);
    

};