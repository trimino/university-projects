#include "item.h"
#include "cart.h"
#include <iostream>

int main(){
    Cart cart{"Trimino's Shop :-]"};
    Item item{"", 0};

    std::string str;
    std::cout << "Enter product names and price  (e.g., English peas 0.79 ):" << std::endl;

    try{
       while (std::cin >> item){
           cart.add_item(item);
       }
    } catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cin.ignore();
    }
    

    std::cout << "Register Receipt\n";

    for(Item* i : cart)
        std::cout << *i;
    std::cout << "\n---------------------------------\n";
    std::cout <<  "$\t"  << std::fixed << std::setprecision(2) << cart.cost() << " Total Cost" << std::endl;

    return EXIT_SUCCESS;
}