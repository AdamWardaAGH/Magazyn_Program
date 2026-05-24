#include <string>
#include <array>
#include "item.h"
    
/*
Podstawowe inforamcje jakie przechowywuje przemiot
Unit opisuje podstawową jednostkę ilości, kikogramy, sztuki itd.
*/

    item::item(std::string name, std::string id_number, double unit):  
    name(name), id_number(id_number), unit(unit) {}
    item::item() : item( "item_name","0",1){}

    // dać add item
    std::string item::getInfo() { return name+" "+id_number; }
    double item::getUnit(){ return unit; }


