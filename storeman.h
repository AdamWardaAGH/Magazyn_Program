#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "storage.h"

/*
Klasa jest odpowiedzialna za edytowanie magazynu (std::map storage) dlatego jest pochodną aby mieć dostęp i móc zmieniać
*/

class storeman {
public:
    
    std::string name;
    storeman();
    storeman(std::string name_);
    std::string executeOrder(std::string activation,storage& warehouse);
    std::string executeSupply(std::string activation,storage& warehouse);
};

