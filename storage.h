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
    std::vector<std::pair<coord, item>> findItems_buffer;   
    std::vector<std::pair<coord, double>> pick_buffer;      

    //wyświetlanie danych
    std::string getSize();
    std::string showallItems();
    std::string findItems_by_id(std::string input);
    std::string findItems_by_name(std::string input);
    std::string findItems_by_coord(std::string input);


    //odbieranie instrukcji do zamówienia
    std::string checkItem_list(item item_);
    void findItems(item item_);
    std::string checkItems(item item_);
    std::string orderRequest(std::vector<item> list);

    //podawanie instrukcji do dostawcy
    void addItems();
    std::string supplyRequest(std::vector<item> list);
    std::string assignStorage(item item_);

    std::vector<std::pair<coord, double>> order_request;
    std::vector<std::pair<coord, item>> supply_request;

    storage(int row_min, int row_max,
        int column_min, int column_max,
        int rack_min, int rack_max);
};