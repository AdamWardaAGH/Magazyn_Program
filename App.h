#pragma once
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL_opengl.h>

class App {
public:
    App();
    ~App();
    void run();

private:
    void handleEvents();
    void render();

    SDL_Window* window;
    SDL_GLContext gl;
    bool running = true;
};