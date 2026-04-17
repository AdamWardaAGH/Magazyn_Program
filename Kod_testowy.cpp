#include<iostream>
#include<clocale>
// aby było koszernie to możmy nie używać stdnamespace by nie było haosu

int main(){
setlocale(LC_ALL, "pl_PL.UTF-8");
    std::cout << "Kod testowy\nUsunąć kiedy repozytorium będzie już miało zawartość" <<std::endl;
    std::cout << "Zmodyfikowałem code i jestem cool ~ JW\n";

    return 0;
}