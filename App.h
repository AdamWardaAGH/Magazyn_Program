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
    void createPolish();

    SDL_Window* window;
    SDL_GLContext gl;
    bool running = true;

    bool but1=false;
    char buf1[256] = "";
public:
    App();
    ~App();
    void run();
};

/*cheatsheet: http://imgui.net/api/ImGui.GUI.html
komendy do terminala do buildowania

cmake -B build -G "MinGW Makefiles"
cmake --build build


git - wstawianie rzeczy
git commit -m 'kommento'
git push

*/