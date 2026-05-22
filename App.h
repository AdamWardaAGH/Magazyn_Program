#pragma once
//basic imports
//UWAGA - KAŻDY PLIK TRZEBA DODAĆ DO CMAKELISTS

//graphics import
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL_opengl.h>

class App {
private:
    void handleEvents();
    void render();
    void initPolish();

    SDL_Window* window;
    SDL_GLContext gl;
    bool running = true;

    bool but[256] = {};
    char buf0[256] = "";
    char buf1[256] = "";
    char buf2[256] = "";

    void wItemShow();
    void wItemAdd();
    void wListItems();
    void clearBuf();
    void clearBut();
public:
    App();
    ~App();
    void run();
};

/*
Buttons:
    main menu
    item
0 - add item
1 - show item
2 - coordinates
3 - item name
4 - item ID
5 - showItemList
6 - display/search

*/

/*cheatsheet: http://imgui.net/api/ImGui.GUI.html
komendy do terminala do buildowania

cmake -B build -G "MinGW Makefiles"
cmake --build build

po buildzie trzeba obok exe dać SDL2.dll i plik czcionki - wtedy działą

git - wstawianie rzeczy
git commit -am 'kommento'
git push

*/