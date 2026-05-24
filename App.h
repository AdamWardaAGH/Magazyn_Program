#pragma once
//basic imports
//UWAGA - KAŻDY PLIK TRZEBA DODAĆ DO CMAKELISTS
#include <ctime>
#include <iostream>
#include "storage.h"
#include "order.h"
#include "supply.h"
#include "storeman.h"

//graphics import
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL_opengl.h>

using namespace std;

class App {
private:
    void handleEvents();
    void render();
    void initPolish();
    void storeInit();//debug in

    SDL_Window* window;
    SDL_GLContext gl;
    bool running = true;

    bool but[256] = {};
    char buf0[256] = "";
    char buf1[256] = "";
    char buf2[256] = "";
    char searchbuf[256]="";
    time_t timestamp;

    void wMain();
    void wMan();
    void wItemShow();
    void wListItems();

    void wOrderShow();
    void wOrderAdd();
    void wSupplyshow();
    void wSupplyAdd();

    void wAgentShow();
    void wAgentAdd();


    void clearBuf();
    void clearBut();

    storage warehouse;
    supply supplier;
    order orderer;
    //zmienne do wyświetlania
    string activeItem;
    order activeOrder;
    supply activeSupply;
    vector<storeman>Agents;
    int activeAgent;
    string s;
public:
    App();
    ~App();
    void run();
};

/*
Buttons:
    main menu
    item
0 - 
1 - show item
2 - coordinates
3 - item name
4 - item ID
5 - showItemList
6 - display/search
    order
7 - wOrderShow
8 - wOrderAdd
9 - wSupplyshow
10- wSupplyAdd
11- wAgentShow
12- wAgentAdd
13- logic of OrderShow
14- logic of SupplyShow

*/

/*
komendy do terminala do buildowania
cmake -B build -G "MinGW Makefiles"
cmake --build build

po buildzie trzeba obok exe dać SDL2.dll i plik czcionki - wtedy działą

git - wstawianie rzeczy
git commit -am 'kommento'
git push origin frontend

komendy do branch integracja
git commit -am "preparing for integration"
git push origin frontend
git fetch
git checkout backend
git pull
git checkout frontend
git checkout -b integracja
git merge backend
*/