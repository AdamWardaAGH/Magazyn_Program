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
    initPolish();
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
void App::initPolish(){
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

    //okno 1 - z pierwszych testów interfejsu
    /*
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
    ImGui::End();*/
    //koniec okna 1

    //okno 2
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_Always);
    ImGui::Begin("Magazyn2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Witaj w systemie magazynowym! Co dzisiaj robimy cwelu?");


    //item
    ImGui::Text("");
    //add item
    if (ImGui::Button("Dodaj item")) 
        {
            but[0]=!but[0];
        }
    //show item
    if (ImGui::Button("Pokaż item")) 
        {
            but[1] = !but[1];
        }
    if(but[1]){
        ImGui::Text("Jaki sposób wyszukiwania?");
        if (ImGui::Button("Koordynaty")) 
        {
            but[2]=!but[2];
            but[1] = false;
            //make sure others are not active
            but[3] = false;
            but[4] = false;
        }
        if (ImGui::Button("Nazwa")) 
        {
            but[3]=!but[3];
            but[1] = false;
            //make sure others are not active
            but[2] = false;
            but[4] = false;
        }
        if (ImGui::Button("ID")) 
        {
            but[4]=!but[4];
            but[1] = false;
            //make sure others are not active
            but[2] = false;
            but[3] = false;
        }
    }
    if(but[2]||but[3]||but[4])
    {
        ImGui::InputText("##search", buf2, sizeof(buf2));
        if (ImGui::Button("Szukaj")) 
        {
            but[6] = !but[6];
            //if but else if but else if but
            //findItem_by_coord(); 
            //findItem_by_name(); 
            //findItem_by_id(); 
        }
    }
    //show all items
    if (ImGui::Button("Wyświetl listę item")) 
        {
            but[5] = !but[5];
        }
    
    //items end
    ImGui::End();
    //koniec okna 2

    //====window drawing====
    if(but[0]){
        wItemAdd(); //
    }
    if(but[6]){
        //if active item empty
        //ImGui::Text("Could not find the item, try again");
        //else
        wItemShow();
    }
    if(but[5]){
        wListItems();
    }

    ImGui::Render();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

//=====WINDOW SECTION=====

//do wypełnienia o branie i wyświetlanie itemu
void App::wItemShow(){
    ImGui::Begin("Przedmiot");
    if (ImGui::Button("Wyjdź")) 
        {
            for (int i=2;i<5;i++)but[i]=false;
        }
    //if 
    ImGui::Text("Nazwa: ");
    ImGui::Text("Id: ");
    ImGui::Text("Waga: ");
    ImGui::End();
}

//do wypełnienia o poprawność i podłączenie
void App::wItemAdd(){
    ImGui::Begin("Dodawanie przedmiotu");
    if (ImGui::Button("Wyjdź")) 
        {
            but[0]=false;
        }
    ImGui::Text("Nazwa: ");
    ImGui::InputText("##nazwa", buf0, sizeof(buf0));
    ImGui::Text("Id: ");
    ImGui::InputText("##id", buf1, sizeof(buf1));
    ImGui::Text("Waga: ");
    ImGui::InputText("##waga", buf2, sizeof(buf2));
    //button 1
    if (ImGui::Button("Potwierdź")) 
        {
            //funckja sprawdzania poprawności zmiennych

            //storage.addItem();

            but[0]=false;
        }
    ImGui::End();
}

void App::wListItems(){
    ImGui::Begin("Lista Item");
    if (ImGui::Button("Wyjdź")) 
        {
            but[5]=false;
        }
    /*
    wyświetlamy każdy item po kolei
    for(){
    }
    */
    ImGui::End();
}

//inne

void App::clearBuf(){
    buf0[0] = '\0';
    buf1[0] = '\0';
    buf2[0] = '\0';
}

void App::clearBut(){
    for(int i = 0; i < 256; i++) but[i] = false;
}