#include <iostream>
#include <string>
#include <vector>
#include "commodity.h"

    //definiuje fukcje które będą metodami z odwołaniem klasa::metoda 
    

    commodity::commodity(std::string name, std::string id_number, double weight, int row, int column):  
    name(name), id_number(id_number), weight(weight), row(row), column(column) {}
    std::string getInfo(){ return ;}

    std::string commodity::getInfo() { return name+" "+id_number;}
    double commodity::getWeight(){ return weight;}
    std::vector<int> commodity::getPosision(){ return {row, column};}


