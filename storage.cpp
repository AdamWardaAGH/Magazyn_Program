#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "storage.h"

/*
Ma posiadać podstawowe info odnośnie wielokości magazynu, jaka jest początkowy i końcowy numer danej półki

storage przechowuje dane o tym co gdzie jest w std::map
szybszy od std::vector lista gdzie elementy mają unikatowy koordynat
*/
    
    storage::storage(int row_min, int row_max, int column_min, int column_max, int rack_min, int rack_max) : 
        row_min(row_min), row_max(row_max),
        column_min(column_min), column_max(column_max),
        rack_min(rack_min), rack_max(rack_max) {}

    std::vector<int> storage::getSize(){ return {1+row_max-row_min, 1+column_max-column_min, 1+rack_max-rack_min}; }





