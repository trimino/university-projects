#include "options.h"

Options::Options(std::string name, double cost): _name{name}, _cost{cost}{
    if (_cost <= 0){
        throw std::runtime_error{"Cost can not be below or equal to zero"};
        _cost = 0;
    }  
}

Options::~Options(){/* destructor for options*/}

double Options::cost(){
    return _cost;
}

std::string Options::to_string() const{
    return _name + " ($" + std::to_string(_cost) + ')'; 
}


std::ostream& operator<<(std::ostream& ost, const Options& opt){    
    ost << opt.to_string();
    return ost; 
}

std::string Options::get_name(){
	return _name;
}
