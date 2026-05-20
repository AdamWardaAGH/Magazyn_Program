#include <iostream>
#include <string>
#include <vector>
#include "depot.h"

    //definiuje fukcje które będą metodami z odwołaniem klasa::metoda 
    

    depot::depot(int row, int column):  
    row(row), column(column) {}
    std::vector<int> depot::getSize(){ return {row, column};}



