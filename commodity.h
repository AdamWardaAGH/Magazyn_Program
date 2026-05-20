#pragma once
#include <iostream>
#include <string>
#include <vector>
class commodity {
public:

    std::string name;
    std::string id_number;
    double weight;
    int row;
    int column;

    commodity(std::string name, std::string id_number, double weight, int row, int column);
    std::string getInfo();
    double getWeight();
    std::vector<int> getPosision();




};