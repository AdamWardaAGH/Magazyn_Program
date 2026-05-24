#pragma once
#include <string>
#include <vector>
#include <array>
#include <tuple>
class coord {
public:


    std::tuple<int, int, int> coordinates;

    coord(int row, int column, int rack);
    std::tuple<int,int,int> getLocation();

    bool operator<(const coord& other) const {
        return coordinates < other.coordinates;
    }



};