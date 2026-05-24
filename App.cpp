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

    /*
    //color customization
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg]        = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // tło okna
    style.Colors[ImGuiCol_Button]          = ImVec4(0.2f, 0.4f, 0.8f, 1.0f); // przycisk
    style.Colors[ImGuiCol_ButtonHovered]   = ImVec4(0.3f, 0.5f, 0.9f, 1.0f); // przycisk hover
    style.Colors[ImGuiCol_ButtonActive]    = ImVec4(0.1f, 0.3f, 0.7f, 1.0f); // przycisk kliknięty
    style.Colors[ImGuiCol_FrameBg]         = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // tło inputa
    style.Colors[ImGuiCol_TitleBg]         = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // pasek tytułu
    style.Colors[ImGuiCol_TitleBgActive]   = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // pasek tytułu aktywny
    */
   ImGui::StyleColorsDark();
    ImGuiStyle& s = ImGui::GetStyle();
    s.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.09f, 0.09f, 1.0f);
    s.Colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.11f, 0.12f, 1.0f);
    s.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05f, 0.07f, 0.09f, 1.0f);
    s.Colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
    s.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.44f, 0.71f, 1.0f);
    s.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.54f, 0.87f, 1.0f);
    s.Colors[ImGuiCol_ButtonActive] = ImVec4(0.05f, 0.27f, 0.49f, 1.0f);
    s.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.13f, 0.15f, 1.0f);
    s.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.18f, 0.21f, 1.0f);
    s.Colors[ImGuiCol_Header] = ImVec4(0.09f, 0.37f, 0.65f, 1.0f);
    s.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.22f, 0.54f, 0.87f, 1.0f);
    s.Colors[ImGuiCol_Separator] = ImVec4(0.16f, 0.18f, 0.20f, 1.0f);
    s.Colors[ImGuiCol_CheckMark] = ImVec4(0.22f, 0.54f, 0.87f, 1.0f);
    s.Colors[ImGuiCol_SliderGrab] = ImVec4(0.22f, 0.54f, 0.87f, 1.0f);
    s.Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.11f, 0.13f, 1.0f);
    s.Colors[ImGuiCol_TabHovered] = ImVec4(0.22f, 0.54f, 0.87f, 1.0f);
    s.Colors[ImGuiCol_TabActive] = ImVec4(0.09f, 0.37f, 0.65f, 1.0f);
    
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
    //okno
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(440, 600), ImGuiCond_Always);
    ImGui::Begin("Główne okno", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    time(&timestamp);
    ImGui::Text("%s", ctime(&timestamp));
    ImGui::Text("\nWitaj w systemie magazynowym! Co dzisiaj robimy przyjacielu?");
    //if niedobory
    //ImGui::Text("Wykryto niedobory w magazynie! Chcesz zamówić?");
    //if (ImGui::Button("Zamów")) 
    //    {
    //        but[1] = !but[1];
    //    }


    //item
    ImGui::Text("Przedmioty");
    //add item
    if (ImGui::Button("Dodaj item")) 
        {
            but[0]=!but[0];
        }
    //show item
    if (ImGui::Button("Pokaż item")) 
        {
            but[1] = !but[1];
            //make sure others are not active
            but[13]=false;
            but[14]=false;
        }
    if(but[1]){
        ImGui::Text("Jaki sposób wyszukiwania?");
        if (ImGui::Button("Koordynaty")) 
        {
            but[2]=true;
            but[1] = false;
            //make sure others are not active
            but[3] = false;
            but[4] = false;
        }
        if (ImGui::Button("Nazwa")) 
        {
            but[3]=true;
            but[1] = false;
            //make sure others are not active
            but[2] = false;
            but[4] = false;
        }
        if (ImGui::Button("ID")) 
        {
            but[4]=true;
            but[1] = false;
            //make sure others are not active
            but[2] = false;
            but[3] = false;
        }
    }
    if(but[2]||but[3]||but[4])
    {
        if(but[2])ImGui::InputText("Koordynaty", searchbuf, sizeof(searchbuf));
        else if(but[3])ImGui::InputText("Nazwa", searchbuf, sizeof(searchbuf));
        else if(but[4])ImGui::InputText("ID", searchbuf, sizeof(searchbuf));
        if (ImGui::Button("Szukaj")) 
        {
            but[6] = true;
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

    //orders and supplies
    ImGui::Text("Zamówienia");
    if (ImGui::Button("Pokaż zamówienie")) 
        {
            but[13]=!but[13];
            //make sure others are not active
            but[1] =false;
            but[2] =false;
            but[3] =false;
            but[4] =false;
            but[14]=false;
        }
    if (but[13]){
        ImGui::Text("");
        std::string id;//fhuef
            ImGui::InputText("Id", searchbuf, sizeof(searchbuf));
        if (ImGui::Button("Szukaj")) 
        {
            but[8] = !but[8];
        }
    }
    //show item
    if (ImGui::Button("Dodaj zamówienie")) 
        {
            but[8] = !but[8];
        }
    ImGui::Text("Uzupełnianie braków");
    if (ImGui::Button("Pokaż zamówienie do magazynu")) 
        {
            but[14]=!but[14];
            //make sure others are not active
            but[1] =false;
            but[2] =false;
            but[3] =false;
            but[4] =false;
            but[13]=false;
            
        }
    if(but[14]){
        ImGui::Text("");
        std::string id;//fefu
            ImGui::InputText("Id", searchbuf, sizeof(searchbuf));
        if (ImGui::Button("Szukaj")) 
        {
            but[9] = !but[9];
        }
    }
        
    //show item
    if (ImGui::Button("Dodaj zamówienie do magazynu")) 
        {
            but[10] = !but[10];
        }
    //zależne od funkcjonalności magazyniera
    /*if (ImGui::Button("Pokaż magazyniera")) 
        {
            but[11]=!but[11];
        }
    //show item
    if (ImGui::Button("Dodaj magazyniera")) 
        {
            but[12] = !but[12];
        }
            */

    ImGui::Text("");
    if (ImGui::Button("Wyjdź")) 
        {
            running=false;
        }
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
    if(but[7]){
        wOrderShow();
    }
    if(but[8]){
        wOrderAdd();
    }
    if(but[9]){
        wSupplyshow();
    }
    if(but[10]){
        wSupplyAdd();
    }
    if(but[11]){
        wAgentShow();
    }
    if(but[12]){
        wAgentAdd();
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
            but[6]=false;
        }
    //if 
    ImGui::Text("Nazwa: ");
    ImGui::Text("Id: ");
    ImGui::Text("Waga: ");
    ImGui::End();
}

//do wypełnienia o poprawność i podłączenie
void App::wItemAdd(){
    ImGui::Begin("Dodawanie przedmiotu");;
    if (ImGui::Button("Wyjdź")) 
        {
            but[0]=false;
        }
    ImGui::Text("Nazwa: ");
    ImGui::InputText("##name", buf0, sizeof(buf0));
    ImGui::Text("Id: ");
    ImGui::InputText("##id", buf1, sizeof(buf1));
    ImGui::Text("Ilość: ");
    ImGui::InputText("##count", buf2, sizeof(buf2));
    //button 1
    if (ImGui::Button("Potwierdź")) 
        {
            //funckja sprawdzania poprawności zmiennych

            //storage.addItem();

            but[0]=false;
        }
    ImGui::End();
}

//do wypełnienia o wywołanie funkcji
void App::wListItems(){
    ImGui::Begin("Lista Item");
    if (ImGui::Button("Wyjdź")) 
        {
            but[5]=false;
        }
    /*
    Storage.showallItems()
    for(){
    }
    */
    ImGui::End();
}

//do wypełnienia o wszystko pretty much
void App::wOrderShow(){
    ImGui::Begin("Pokazanie zamówienia");
    if (ImGui::Button("Wyjdź")) 
        {
            but[7]=false;
        }
    //funckjonalność
    //showOrder(activeOrder);
    ImGui::End();
}
void App::wOrderAdd(){
    ImGui::Begin("Dodanie zamówienia");
    if (ImGui::Button("Wyjdź")) 
        {
            but[8]=false;
        }
    //funckjonalność
    ImGui::Text("Id: ");
    ImGui::InputText("##idOrder", buf0, sizeof(buf0));
    ImGui::Text("Cel docelowy: ");
    ImGui::InputText("##destinationOrder", buf1, sizeof(buf1));
    //for(items in newOrderItems)
    /*
    //wymyśleć rozwiązanie na 50000 różnych inputext
    ImGui::Text("Nazwa: ");
    ImGui::InputText("##name", buf0, sizeof(buf0));
    ImGui::Text("Id: ");
    ImGui::InputText("##id", buf1, sizeof(buf1));
    ImGui::Text("Ilość: ");
    ImGui::InputText("##count", buf2, sizeof(buf2));
    */
    if (ImGui::Button("Dodaj item")) 
        {
            //newOrderItems.pushback
    
        }
    
    //button 1
    if (ImGui::Button("Potwierdź")) 
        {
            //funckja sprawdzania poprawności zmiennych

            //Storage.addOrder();

            but[8]=false;
        }
    ImGui::End();
}
void App::wSupplyshow(){
    ImGui::Begin("Pokazanie zamówienia do magazynu");
    if (ImGui::Button("Wyjdź")) 
        {
            but[9]=false;
        }
    //funckjonalność
    ImGui::Text("Zamówienie jest takie i t\nkie");
    ImGui::End();
}
void App::wSupplyAdd(){
    ImGui::Begin("Dodanie zamówienia do magazynu");
    if (ImGui::Button("Wyjdź")) 
        {
            but[10]=false;
        }
    //funckjonalność
    ImGui::End();
}

void App::wAgentShow(){
    ImGui::Begin("Pokazanie magazyniera");
    if (ImGui::Button("Wyjdź")) 
        {
            but[11]=false;
        }
    //funckjonalność
    ImGui::End();
}
void App::wAgentAdd(){
    ImGui::Begin("Dodanie magazyniera");
    if (ImGui::Button("Wyjdź")) 
        {
            but[12]=false;
        }
    //funckjonalność
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