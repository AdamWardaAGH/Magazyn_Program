#include<iostream>
#include<vector>
#include"order.h"
#include"item.h"

void order::addItem(std::string buffer_1,std::string buffer_2,std::string bufr_3){
        double buffer_3=std::stod(bufr_3);
            item item_(buffer_1, buffer_2, buffer_3);
            order_list.push_back(item_);
    }
