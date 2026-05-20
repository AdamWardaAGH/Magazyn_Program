#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "commodity.h"
class depot {
public:

    int row;
    int column;
    // 3D wketor opisujący co jest gdzie: wiersz/kolmuna/wykość półki
    std::vector<std::vector<std::vector<commodity>>> layout;

    depot(int row, int column);
    std::vector<int> getSize();




};