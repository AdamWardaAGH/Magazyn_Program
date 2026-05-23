#pragma once
#include <string>
#include <vector>
#include <array>
class item {
public:

    std::string name;
    std::string id_number;
    double unit;

    item(std::string name, std::string id_number, double unit);
    std::string getInfo();
    double getUnit();


};