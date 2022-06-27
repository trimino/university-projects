#include "coin.h"
#include <vector>

void print_menu();
void add_coin();
void list_all();
void delete_coin();


std::vector<Coin*> coins;

int main (){
       
    
    std::cout << "+--------------------------------+" << std::endl;
    std::cout << "|         CSE1325 COINS          |" << std::endl;
    std::cout << "+--------------------------------+" << std::endl;
    bool quit = false;
    char choice;

    print_menu();
    while (!quit){
        std::cout << coins.size() << " coins >> ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice){
            case 'A':
            case 'a':
                add_coin();
                break;

            case 'L':
            case 'l':
                list_all();
                break;

            case 'D':
            case 'd':
                delete_coin();
                break;

            case 'P':
            case 'p':
                print_menu();
                break;

            case 'Q':
            case 'q':
                quit = true;
                break;

            default:
                std::cout << "Invalid input. Enter p or P to see options" << std::endl;
                break;
        }
    }
}


void print_menu(){
    std::cout << "a) Add Coins"      << std::endl;
    std::cout << "l) List all coins" << std::endl;
    std::cout << "d) Delete a coin"  << std::endl;
    std::cout << "p) Print Menu "    << std::endl;
    std::cout << "q) Quit program"   << std::endl;
}

void add_coin(){
    Coin* ptr_coin = new Coin{};

    try{
        std::cout << "Coin (year size \\n notes): ";
        std::cin >> *ptr_coin;
    }catch(std::runtime_error e){
       std::cerr << "RUNTIME ERROR\n";
    }catch(std::out_of_range e){
        std::cerr << "Out of Range Error\n";
    }catch(std::exception e){
        std::cerr << "Something went wrong. Try again\n";
    }
    coins.push_back(ptr_coin);
}


void list_all(){
    try{
        if (coins.size() == 0){
            std::cout << "You have 0 coins" << std::endl;
        }else{   
            int i=0; 
            for (auto& a : coins){
                std::cout << i << ") " << *a << std::endl;
                ++i;
            }
        }
    }catch(std::runtime_error e){
        std::cerr << e.what() << '\n';
    }
}

void delete_coin(){
    list_all();
    try{
        int index;
        std::cout << "Enter the index of the coin you would like to delete: ";
        std::cin >> index;
        Coin* temp = coins.at(index);
        temp->~Coin();
        coins.erase(coins.begin()+index);
        delete temp;
    }
    catch(std::out_of_range e){
        std::cerr << e.what() << '\n';
    }catch(std::runtime_error e){
        std::cerr << e.what() << '\n';
    }catch(const std::exception& e){
        std::cerr << "ERROR\n";
    }  
    
}

