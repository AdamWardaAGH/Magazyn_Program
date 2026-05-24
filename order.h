#pragma once
#include<string>
#include<vector>
#include"item.h"
#include"storage.h"

class order {
public:

    std::vector<item> order_list;
    
    void addItems();
};
