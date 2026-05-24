#pragma once
#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
class supply{
    public:

    std::vector<item> supply_list;
    
    void addItems();
    
};