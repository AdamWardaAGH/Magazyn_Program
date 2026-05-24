#include<iostream>
#include<vector>
#include"order.h"
#include"item.h"

void order::addItems(){
  order_list.clear();
  std::string in = "", buffer_1, buffer_2;
  double buffer_3;
  while(1){
    //name
    std::cout << "\nPodaj nazwę: " << std::endl;
    std::cin >> in;
    if(in == "exit"){break;}
    buffer_1 = in;
    //id
    std::cout << "\nPodaj id: " << std::endl;
    std::cin >> in;
    if(in == "exit"){break;}
    buffer_2 = in;
    //unit
    std::cout << "\nPodaj jednastkę: " << std::endl;
    std::cin >> in;
    if(in == "exit"){break;}
    buffer_3 = std::stod(in);

    item item_(buffer_1, buffer_2, buffer_3);
    order_list.push_back(item_);
  }  
}
