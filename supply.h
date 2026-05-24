#pragma once
#include<string>
#include<vector>
#include"item.h"
#include"storage.h"
class supply{
    public:

    std::vector<item> supply_list;
    
    void addItem(std::string buffer_1,std::string buffer_2,std::string bufr_3);
};