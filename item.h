#pragma once
#include <string>
#include <vector>
#include <array>
class item {
public:

    std::string name;
    std::string id_number;
    double weight;

    item(std::string name, std::string id_number, double weight);
    std::string getInfo();
    double getWeight();


};