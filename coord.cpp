#include <string>
#include <array>
#include <tuple>
#include <map>
#include "coord.h"
    
/*
Koordynaty mogę się zmieniać w zależności od struktury i organizacji magazynu
Więc dobrze mieć okno na możliwie dobudowanie koordynatów np. dodatkowe wartości wewnątrz półki itd.
*/
    coord::coord(int row, int column, int rack){
    coordinates = std::make_tuple(row,column,rack);
    }

    std::tuple<int,int,int> coord::getLocation(){ return coordinates; } 


