#include "App.h"

//konstruktor
App::App() : warehouse(0, 10, 0, 20, 0, 15){
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
    
    //debugging
    storeInit();
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

//funkcja do władowania testowego magazynu
void App::storeInit(){
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

    Agents.push_back(storeman("Admin"));
    activeAgent=0;
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
    wMain();
    wMan();
    wMap();

    //====other windows drawing====
    
    if(but[6]){
        //if active item empty
        //ImGui::Text("Could not find the item, try again");
        //else
        wItemShow();
    }
    if(but[5]){
        wListItems();
    }
    if(but[8]){
        wOrderAdd();
    }
    wOrderShow();
    
    if(but[10]){
        wSupplyAdd();
    }
    wSupplyshow();
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

//main window
void App::wMain(){
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
    //show item
    if (ImGui::Button("Pokaż przedmiot")) 
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
        if(but[2])ImGui::InputText("Koordynaty (oddzielone przecinkiem)##Input", searchbuf, sizeof(searchbuf));
        else if(but[3])ImGui::InputText("Nazwa##Input", searchbuf, sizeof(searchbuf));
        else if(but[4])ImGui::InputText("ID##Input", searchbuf, sizeof(searchbuf));
        if (ImGui::Button("Szukaj")) 
        {
            if(but[2])activeItem = warehouse.findItems_by_coord(searchbuf);
            else if(but[3])activeItem = warehouse.findItems_by_name(searchbuf);
            else if(but[4])activeItem = warehouse.findItems_by_id(searchbuf);
            but[6] = true;
            //if but else if but else if but
            //findItem_by_coord(); 
            //findItem_by_name(); 
            //findItem_by_id(); 
        }
    }
    //show all items
    if (ImGui::Button("Wyświetl listę przedmiotów")) 
        {
            but[5] = !but[5];
        }
    
    //items end

    //order
    //show order
    ImGui::Text("Zamówienia");
    /*if (ImGui::Button("Pokaż zamówienie")) 
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
            but[7] = !but[7];
        }
    }*/
    //add order
    if (ImGui::Button("Dodaj zamówienie")) 
        {
            but[8] = !but[8];
        }
    //supply
    //show supply
    ImGui::Text("Uzupełnianie braków");
    /*if (ImGui::Button("Pokaż zamówienie do magazynu")) 
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
            but[] = !but[];
        }
    }*/
        
    //add supply
    if (ImGui::Button("Dodaj zamówienie do magazynu")) 
        {
            but[10] = !but[10];
        }
    //storeman
    ImGui::Text("Pracownicy");
    if (ImGui::Button("Zarządzaj magazynierami")) 
        {
            but[11]=!but[11];
        }
    //show item
    if (ImGui::Button("Dodaj magazyniera")) 
        {
            but[12] = !but[12];
        }
        

    ImGui::Text("");
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    if (ImGui::Button("Wyjdź")) 
        {
            running=false;
        }
    ImGui::PopStyleColor();
    ImGui::End();
}

void App::wMan(){
    ImGui::SetNextWindowPos(ImVec2(490, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiCond_Always);
    ImGui::Begin("Aktywny pracownik", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    // w render():
    const char* tempp = Agents.at(activeAgent).name.c_str();

    if (ImGui::BeginCombo("##pracownik", tempp)) {
        for (int i = 0; i < Agents.size(); i++) {
            bool selected = (activeAgent == i);
            if (ImGui::Selectable(Agents.at(i).name.c_str(), selected)) {
                activeAgent = i;
            }
            if (selected)
                ImGui::SetItemDefaultFocus(); // highlight the current one
        }
    ImGui::EndCombo();
    }
    ImGui::End();
}

void App::wMap(){
    ImGui::SetNextWindowPos(ImVec2(690, 50), ImGuiCond_Always);
    ImGui::Begin("Mapa", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::SliderInt("Piętro", &curRack, 0, warehouse.rack_max);
    ImGui::BeginChild("##map_scroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (int y = 0; y < warehouse.row_max; y++) {
        for (int x = 0; x < warehouse.column_max; x++) {
            if (x > 0) ImGui::SameLine(); 
            ImVec4 kolor;
            char temp[256];
            snprintf(temp, sizeof(temp), "%i,%i,%i",
                    x, y, curRack);
            string tileP = temp;
            ImGui::BeginDisabled(warehouse.findItems_by_coord(tileP)=="Nie znaleniono, żadnych przedmiotów");
            std::string id = "##tile" + std::to_string(x) + "_" + std::to_string(y);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.5f, 0.2f, 1.0f));
            if (ImGui::Button(id.c_str(), ImVec2(tileSize, tileSize))) {
                activeItem=warehouse.findItems_by_coord(tileP);
                but[6] = true;
            }
            ImGui::EndDisabled();
            ImGui::PopStyleColor();
        }
    }
    ImGui::EndChild();
    ImGui::End();
}

//do wypełnienia o branie i wyświetlanie itemu
void App::wItemShow(){
    ImGui::Begin("Przedmiot");
    if (ImGui::Button("Anuluj")) 
        {
            for (int i=2;i<5;i++)but[i]=false;
            but[6]=false;
        }
    ImGui::Text(activeItem.c_str());
    /*ImGui::Text("Nazwa: ");
    ImGui::Text("Id: ");
    ImGui::Text("Waga: ");*/
    ImGui::End();
}



//do wypełnienia o wywołanie funkcji
void App::wListItems(){
    ImGui::Begin("Lista Item");
    if (ImGui::Button("Wyjdź")) 
        {
            but[5]=false;
        }
    ImGui::Text(warehouse.showallItems().c_str());
    ImGui::End();
}

//do wypełnienia o wszystko pretty much
void App::wOrderShow(){
    if(!warehouse.order_request.empty())
    {
        ImGui::Begin("Pokazanie zamówienia");
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
        if (ImGui::Button("Anuluj zamówienie")) 
            {
                warehouse.order_request.clear();
            }
        ImGui::PopStyleColor();
        for(int i=0;i< orderer.order_list.size();i++){
            ImGui::Text("Nazwa: ");
            ImGui::SameLine(); 
            //auto na=orderer.order_list.at(i).name.c_str();
            std::string& s = orderer.order_list.at(i).name;
            ImGui::Text( s.c_str());
            

            ImGui::Text("Id: ");
            ImGui::SameLine(); 
            std::string& s2 = orderer.order_list.at(i).id_number;
            ImGui::Text( s2.c_str());

            ImGui::Text("Ilość: ");
            ImGui::SameLine(); 
            double& s3 = orderer.order_list.at(i).unit;
            char temp3[128];
            snprintf(temp3, sizeof(temp3), "%.2f", s3);
            ImGui::Text( temp3);
            ImGui::Text("");

        }
        if (ImGui::Button("Wykonaj")) 
            {
                s = Agents.at(activeAgent).executeOrder("Zaakceptowano",warehouse);
                if(s=="Przedmioty przeniesione do zamówienia"){
                    but[7]=true;
                    orderer.order_list.clear();
                    warehouse.order_request.clear();
                    s="";
                }
            }
        ImGui::End();
    }
    if(but[7])
    {
        ImGui::Begin("Pokazanie zamówienia");
        ImGui::Text("Poprawnie zakończono zamówienie");
        if (ImGui::Button("Zakończ")) 
            {
                but[7]=false;
            }
        ImGui::End();
    }
}
void App::wOrderAdd(){
    ImGui::Begin("Dodanie zamówienia");
    if (ImGui::Button("Anuluj")) 
        {
            orderer.order_list.clear();
            but[8]=false;
        }
    //funckjonalność
    //ImGui::Text("Id: ");
    //ImGui::InputText("##idOrder", buf0, sizeof(buf0));
    //ImGui::Text("Cel docelowy: ");
    //ImGui::InputText("##destinationOrder", buf1, sizeof(buf1));
    for(int i=0;i< orderer.order_list.size();i++){
        ImGui::Text("Nazwa: ");
        string name="##name"+std::to_string(i);
        //auto na=orderer.order_list.at(i).name.c_str();
        std::string& s = orderer.order_list.at(i).name;
        char temp[128];
        strncpy(temp, s.c_str(), sizeof(temp));
        if(ImGui::InputText(name.c_str(), temp, sizeof(temp)))//InputText return true on change
        s=temp;

        ImGui::Text("Id: ");
        string name2="##id"+std::to_string(i);
        //auto d=orderer.order_list.at(i).id_number.c_str();
        std::string& s2 = orderer.order_list.at(i).id_number;
        char temp2[128];
        strncpy(temp2, s2.c_str(), sizeof(temp2));
        if(ImGui::InputText(name2.c_str(), temp2, sizeof(temp2)))
        s2=temp2;

        ImGui::Text("Ilość: ");
        string name3="##count"+std::to_string(i);
        //auto co=orderer.order_list.at(i).unit.c_str();
        double& s3 = orderer.order_list.at(i).unit;
        char temp3[128];
        snprintf(temp3, sizeof(temp3), "%.2f", s3);
        if(ImGui::InputText(name3.c_str(), temp3, sizeof(temp3), ImGuiInputTextFlags_CharsDecimal))
        s3 = std::stod(temp3);
        
        std::string label = "Usuń przedmiot##" + std::to_string(i);
        if (ImGui::Button(label.c_str())) 
        {
            orderer.order_list.erase(orderer.order_list.begin()+i);
        }
        ImGui::Text("");

    }
    if (ImGui::Button("Dodaj przedmiot")) 
        {
            orderer.addItem("","","1");
        }
    
    //button 1
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::Text(s.c_str());
    ImGui::PopStyleColor();
    if (ImGui::Button("Potwierdź")) 
        {
            s = warehouse.orderRequest(orderer.order_list);
            if(s=="Zaakceptowano"){
                //orderer.order_list.clear();
                s="";
                but[8]=false;
            }
        }
    ImGui::End();
}
void App::wSupplyshow(){
    
    if(!warehouse.supply_request.empty())
    {
        ImGui::Begin("Pokazanie zamówienia do magazynu");
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
        if (ImGui::Button("Anuluj zamówienie")) 
            {
                warehouse.supply_request.clear();
            }
        ImGui::PopStyleColor();
        for(int i=0;i< supplier.supply_list.size();i++){
            ImGui::Text("Nazwa: ");
            ImGui::SameLine(); 
            std::string& s = supplier.supply_list.at(i).name;
            ImGui::Text( s.c_str());
            

            ImGui::Text("Id: ");
            ImGui::SameLine(); 
            std::string& s2 = supplier.supply_list.at(i).id_number;
            ImGui::Text( s2.c_str());

            ImGui::Text("Ilość: ");
            ImGui::SameLine(); 
            double& s3 = supplier.supply_list.at(i).unit;
            char temp3[128];
            snprintf(temp3, sizeof(temp3), "%.2f", s3);
            ImGui::Text( temp3);
            ImGui::Text("");

        }
        if (ImGui::Button("Wykonaj")) 
            {
                s = Agents.at(activeAgent).executeSupply("Zaakceptowano",warehouse);
                if(s=="Przedmioty przeniesione do magazynu"){
                    but[9]=true;
                    supplier.supply_list.clear();
                    warehouse.supply_request.clear();
                    s="";
                }
            }
        ImGui::End();
    }
    if(but[9])
    {
        ImGui::Begin("Pokazanie zamówienia do magazynu");
        ImGui::Text("Poprawnie zakończono zamówienie");
        if (ImGui::Button("Zakończ")) 
            {
                but[9]=false;
            }
        ImGui::End();
    }
}
void App::wSupplyAdd(){
    ImGui::Begin("Dodawanie zamówienia do magazynu");
    if (ImGui::Button("Anuluj")) 
        {
            supplier.supply_list.clear();
            but[10]=false;
        }
    //funckjonalność
    //ImGui::Text("Id: ");
    //ImGui::InputText("##idOrder", buf0, sizeof(buf0));
    //ImGui::Text("Cel docelowy: ");
    //ImGui::InputText("##destinationOrder", buf1, sizeof(buf1));
    for(int i=0;i< supplier.supply_list.size();i++){
        ImGui::Text("Nazwa: ");
        string name="##name"+std::to_string(i);
        //auto na=orderer.order_list.at(i).name.c_str();
        std::string& s = supplier.supply_list.at(i).name;
        char temp[128];
        strncpy(temp, s.c_str(), sizeof(temp));
        if(ImGui::InputText(name.c_str(), temp, sizeof(temp)))//InputText return true on change
        s=temp;

        ImGui::Text("Id: ");
        string name2="##id"+std::to_string(i);
        //auto d=orderer.order_list.at(i).id_number.c_str();
        std::string& s2 = supplier.supply_list.at(i).id_number;
        char temp2[128];
        strncpy(temp2, s2.c_str(), sizeof(temp2));
        if(ImGui::InputText(name2.c_str(), temp2, sizeof(temp2)))
        s2=temp2;

        ImGui::Text("Ilość: ");
        string name3="##count"+std::to_string(i);
        //auto co=orderer.order_list.at(i).unit.c_str();
        double& s3 = supplier.supply_list.at(i).unit;
        char temp3[128];
        snprintf(temp3, sizeof(temp3), "%.2f", s3);
        if(ImGui::InputText(name3.c_str(), temp3, sizeof(temp3), ImGuiInputTextFlags_CharsDecimal))
        s3 = std::stod(temp3);
        
        std::string label = "Usuń przedmiot##" + std::to_string(i);
        if (ImGui::Button(label.c_str())) 
        {
            supplier.supply_list.erase(supplier.supply_list.begin()+i);
        }
        ImGui::Text("");

    }
    if (ImGui::Button("Dodaj przedmiot")) 
        {
            supplier.addItem("","","1");
        }
    
    //button 1
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::Text(s.c_str());
    ImGui::PopStyleColor();
    if (ImGui::Button("Potwierdź")) 
        {
            s = warehouse.supplyRequest(supplier.supply_list);
            if(s=="Zaakceptowano"){
                s="";
                but[10]=false;
            }
        }
    ImGui::End();
}

void App::wAgentShow(){
    ImGui::Begin("Pokazanie magazynierów");
    if (ImGui::Button("Anuluj")) 
        {
            but[11]=false;
        }
    //funckjonalność
    for(int i=0;i< Agents.size();i++){
        ImGui::Text("Imie: ");
        string name="##WorkerName"+std::to_string(i);
        std::string& s = Agents.at(i).name;
        char temp[128];
        strncpy(temp, s.c_str(), sizeof(temp));
        if(ImGui::InputText(name.c_str(), temp, sizeof(temp)))//InputText return true on change
        s=temp;
        if(i>=1){
            std::string label = "Usuń pracownika##" + std::to_string(i);
            if (ImGui::Button(label.c_str())) 
            {
                if(i>=activeAgent)activeAgent=0;
                Agents.erase(Agents.begin()+i);
            }
        }
        
        ImGui::Text("");

    }
    ImGui::End();
}
void App::wAgentAdd(){
    ImGui::Begin("Dodanie magazyniera");
    if (ImGui::Button("Anuluj")) 
        {
            clearBuf();
            but[12]=false;
        }
    //funckjonalność
    ImGui::Text("Imie: ");
    ImGui::InputText("##agentName", buf0, sizeof(buf0));
    //button 1
    if (ImGui::Button("Potwierdź")) 
        {
            //funckja sprawdzania poprawności zmiennych
            Agents.push_back(storeman(buf0));
            clearBuf();
            but[12]=false;
        }
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