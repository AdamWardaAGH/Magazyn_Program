
#include<clocale>
//graphics app import
#include "App.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"polish"); //linijka niepotrzebna, 
    //bo język polski inaczej robimy, ale zostawiam na wszelki 
    //jeśli ma wpływ na czytanie inputów
    App app;
    app.run();
    return 0;
}