#include "taxfree.h"
#include "taxed.h"
#include <iostream>
#include <vector> 

int main(){

    Taxed::set_tax_rate(0.0825);
    Taxed beer{"Revovler Blood & Honey 12 Pack",9.85};
    Taxed wine{"Yellow Tail", 8.87};
    Taxed liquor{"Fireball Cinnamon Whiskey 1.75L",28.69};

    Taxfree coffee{"Starbucks Mocha with Almond Milk",6.99};
    Taxfree cold{"Cold Remedies", 6.55};
    Taxfree nutrition{"Multi-Vitamins",10.99};
    
    std::vector<Product*> cart;
    double total = 0;
    bool quit = false;
    int quan,index;
    char choice;
    const std::string menu = {
        "+-----------------------+\n"
        "|WELCOME TO MR. T's SHOP|\n"
        "+-----------------------+\n"
    };

    do{
        std::cout << menu << "0) " << liquor << '\n'
                          << "1) " << coffee << '\n'
                          << "2) " << beer   << '\n'
                          << "3) " << nutrition << '\n'
                          << "4) " << wine << '\n'
                          << "5) " << cold << '\n';
        try{        
            std::cout << '\n';
            std::cout << "Enter quantity (0 to exit) and product index: ";
            std::cin >> quan;
            std::cin >> choice;
            if (quan == 0){
                quit = true;
                break;
            }
            if (std::isdigit(quan) == 0){
                throw std::runtime_error{"Quantity is not an integer"};
            }
        }catch(const std::exception& e){
            std::cerr << "Invalid input: " << e.what() << '\n';
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(32767,'\n');
            }
            
        }     
        
        switch (choice){
            case '0':
                liquor.set_quantity(quan);
                cart.push_back(liquor.clone());              
                break;
            case '1':
                coffee.set_quantity(quan);
                cart.push_back(coffee.clone());
                break;
            case '2':
                beer.set_quantity(quan);
                cart.push_back(beer.clone());
                break;
            case '3':
                nutrition.set_quantity(quan);
                cart.push_back(nutrition.clone());
                break;
            case '4':
                wine.set_quantity(quan);
                cart.push_back(wine.clone());
                break;
            case '5':
                cold.set_quantity(quan);
                cart.push_back(cold.clone());
                break;
            default:
                std::cerr << "###Invalid input for index : " << choice << "###" << std::endl;
                break;
        }

        std::cout << std::endl;
        std::cout << "Current Order\n";
        std::cout << "- - - - - - - -\n";
        for (auto& a : cart){
            std::cout << *a << std::endl;
            total = total + a->price();
        }
        std::cout << "Total Price: $" << total << std::endl;
        std::cout << std::endl;
     
    } while (!quit);
    
  
    return EXIT_SUCCESS;
     
}
