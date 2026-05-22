#include "App.h"

//konstruktor
App::App() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    window = SDL_CreateWindow("Magazyn", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    gl = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, gl);
    ImGui_ImplOpenGL3_Init("#version 130");
    createPolish();
}

//destruktor
App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//załączenie języka polskiego do interfejsu
void App::createPolish(){
    ImGuiIO& io = ImGui::GetIO();
    ImVector<ImWchar> ranges;
    ImFontGlyphRangesBuilder builder;
    builder.AddRanges(io.Fonts->GetGlyphRangesDefault());

    // Dodaj polskie znaki
    static const ImWchar polish[] = {
        0x0104, 0x0105, // Ą ą
        0x0106, 0x0107, // Ć ć
        0x0118, 0x0119, // Ę ę
        0x0141, 0x0142, // Ł ł
        0x0143, 0x0144, // Ń ń
        0x00D3, 0x00F3, // Ó ó
        0x015A, 0x015B, // Ś ś
        0x0179, 0x017C, // Ź ź Ż ż
        0,
    };
    builder.AddRanges(polish);
    builder.BuildRanges(&ranges);
    //font wybór jest tutaj
    io.Fonts->AddFontFromFileTTF("arial.ttf", 16.0f, nullptr, ranges.Data);
    io.Fonts->Build();
}

//główna pętla
void App::run() {
    while (running) {
        handleEvents();
        render();
    }
}

//zbieranie i zarządzanie eventami
void App::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_QUIT) running = false;
    }
    
}

//renderowanie
void App::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //okno 1
    ImGui::Begin("Magazyn");
    ImGui::Text("Działa!");
    //button 1
    if (ImGui::Button("Button")) 
        {
            but1 = !but1;
        }
    if(but1){
        ImGui::InputText("Etykieta", buf1, sizeof(buf1));
        ImGui::Text("Wpisano: %s", buf1);
    }
    ImGui::End();
    //koniec okna 1

    //okno 2
    ImGui::SetNextWindowPos(ImVec2(100, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Magazyn2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Działala!");
    //button 1
    if (ImGui::Button("Button")) 
        {
            but1 = !but1;
        }
    if(but1){
        ImGui::SetCursorPos(ImVec2(20, 60));
        ImGui::InputText("Etykieta", buf1, sizeof(buf1));
        ImGui::Text("Wpisano: %s", buf1);
    }
    ImGui::End();
    //koniec okna 2

    ImGui::Render();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}