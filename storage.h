#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "item.h"
#include "coord.h"

class storage {
public:

    int row_min, row_max;
    int column_min, column_max;
    int rack_min, rack_max;
    std::map <coord,item> inventory;
    std::map <std::string,std::string> list;

    storage(int row_min, int row_max,
        int column_min, int column_max,
        int rack_min, int rack_max);
    
    std::vector<int> getSize();
    void addItem(item item_);
    void findItem_by_coord();
    void findItem_by_name();
    void findItem_by_id();

};