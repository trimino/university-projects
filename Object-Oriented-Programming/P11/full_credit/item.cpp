#include "item.h"


Item::Item(std::string name, double price): _name{name}, _price{price} {/*constructor body*/}

double Item::cost(){ return _price;}

std::ostream& operator<<(std::ostream& ost, const Item& item){
    ost << "$\t"  << std::fixed << std::setprecision(2) << item._price << "  " << item._name << std::endl;;
    return ost;
}


std::istream& operator>>(std::istream& ist, Item& item){
    std::string line;
    std::getline(ist, line);  
    if(line.length() == 0) throw std::runtime_error{"*** ERROR: Can not have empty string ***\n"};

    std::string str;
    std::istringstream iss(line);

    std::regex dec_regex{"\\d*\\.\\d+"};
    std::regex str_regex{"[A-Za-z]+"};

    bool str_b = false;
    bool dec_b = false;
    
    while (iss >> str){

        if( std::regex_match(str, str_regex) ){ 
            item._name = item._name + " " + str;
            str_b = true;
        }

        else if( std::regex_match(str, dec_regex) ){
            item._price = std::stod(str);   
            dec_b = true;
        }
    }

    if(str_b == false) throw std::runtime_error{"\nInvalid name\n"};
    if(dec_b == false) throw std::runtime_error{"\nInvalid price\n"};
    
    return ist;
}