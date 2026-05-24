#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <clocale>
#include "item.h"
#include "coord.h"
#include "storage.h"
#include "supply.h"
#include "order.h"
#include "storeman.h"

// JEST TO "ROBOCZY" MAIN W KTÓRYM TESTUJEMY LOGIKĘ PROGRAMU KLASY, ICH METODY I ICH POLA
int main(){
SetConsoleCP(65001);        // input konsoli → UTF-8
SetConsoleOutputCP(65001);  // output konsoli → UTF-8
setlocale(LC_ALL,"pl_PL.UTF-8");
    
//wstępna kofiguracja
    storage warehouse(1, 10, 1, 20, 1, 15);
    storeman man;
    supply supplier;
    order orderer;

//podanie startowych wartości
    warehouse.id_list = {     
    {"SCR-001", "Śrubka"},
    {"KEY-002", "Klucz"},
    {"NUT-003", "Nakrętka"},
    {"BOL-004", "Bolt"},
    {"WAR-005", "Wkręt"},
    {"PLA-006", "Płytka"},
    {"SPR-007", "Sprężyna"},
    {"CAB-008", "Kabel"},
    {"TUB-009", "Rurka"},
    {"ROD-010", "Pręt"} 
    };

    warehouse.inventory = {
    {coord(0,0,0), item("Śrubka",  "SCR-001", 0.5)},
    {coord(0,0,1), item("Klucz",   "KEY-002", 1.2)},
    {coord(0,1,0), item("Nakrętka","NUT-003", 0.3)},
    {coord(0,1,1), item("Bolt",    "BOL-004", 0.8)},
    {coord(0,2,0), item("Wkręt",   "WAR-005", 0.4)},
    {coord(1,0,0), item("Płytka",  "PLA-006", 2.1)},
    {coord(1,0,1), item("Sprężyna","SPR-007", 0.6)},
    {coord(1,1,0), item("Kabel",   "CAB-008", 3.0)},
    {coord(1,1,1), item("Rurka",   "TUB-009", 1.5)},
    {coord(1,2,0), item("Pręt",    "ROD-010", 4.2)},
    {coord(1,2,1), item("Bolt",    "BOL-004", 0.2)},
    {coord(1,2,2), item("Sprężyna","SPR-007", 0.6)}
    };

 bool pentla = true;
 std::string s;
 std::string input;
    while(pentla){
    int w = 0;
    std::cout << "+++++MAGAZYN+++++" << "\n";
    std::cout << "1. Wyświetl magazyn" << "\n";
    std::cout << "2. Szukaj po id" << "\n";
    std::cout << "3. Szukaj po nazwie" << "\n";
    std::cout << "4. Szukaj po koordynatach" << "\n";
    std::cout << "5. Stwórz zamówienie od odbiorcy" << "\n";
    std::cout << "6. Stwórz zamówienie do dostawcy" << "\n";
    std::cout << "0. Wyjście" << "\n";
    std::cout << "Podaj numer czynności: ";
    std::cin >> w;
    switch(w){
        case 0:
            pentla = false;
            break;


        case 1: 
            s = warehouse.showallItems();
            std::cout << s << std::endl;
            break;


        case 2:
            std::cout << "Podaj id: ";
            std::cin >> input;
            std::cout << "\n";
            s = warehouse.findItems_by_id(input);
            std::cout << s << std::endl;
            break;


        case 3:
            std::cout << "Podaj nazwę: ";
            std::cin >> input;
            std::cout << "\n";
            s = warehouse.findItems_by_name(input);
            std::cout << s << std::endl;
            break;


        case 4:
            std::cout << "Podaj koordynaty(x,y,z): ";
            std::cin >> input;
            std::cout << "\n";     
            s = warehouse.findItems_by_coord(input);
            std::cout << s << std::endl;
            break;

        case 5:
            orderer.addItems();
            s = warehouse.orderRequest(orderer.order_list);
            std::cout << s << std::endl;
            s = man.executeOrder(s,warehouse);
            std::cout << s << std::endl;
            break;

        case 6:
            supplier.addItems();
            s = warehouse.supplyRequest(supplier.supply_list);
            std::cout << s << std::endl;
            s = man.executeSupply(s,warehouse);
            std::cout << s << std::endl;
            break;

        default:
        std::cout << "Zła wartość\n";
            break;


    }
    std::cout << "\n\n\n";
    }
    std::cout << "Zakończono działanie programu\n";

    return 0;
}