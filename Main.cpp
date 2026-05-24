#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <clocale>
#include "App.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"polish"); //linijka niepotrzebna, 
    //bo język polski inaczej robimy w imgui, ale zostawiam na wszelki 
    //jeśli ma wpływ na czytanie inputów
    App app;
    app.run();

    return 0;
}