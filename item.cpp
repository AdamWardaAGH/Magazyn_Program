#include <string>
#include <array>
#include "item.h"
    
/*
Podstawowe inforamcje jakie przechowywuje przemiot
*/

    item::item(std::string name, std::string id_number, double weight):  
    name(name), id_number(id_number), weight(weight) {}

    std::string item::getInfo() { return name+" "+id_number; }
    double item::getWeight(){ return weight; }


