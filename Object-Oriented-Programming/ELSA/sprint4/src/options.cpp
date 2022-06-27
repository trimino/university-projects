#include "options.h"

Options::Options(std::string name, double cost): _name{name}, _cost{cost}{
    if (_cost <= 0){
        throw std::runtime_error{"Cost can not be below or equal to zero"};
        _cost = 0;
    }  
}

Options::Options(std::istream& ist){
	getline(ist, _name);
	ist >> _cost;
	ist.ignore(32767,'\n');	
}

Options::~Options(){/* destructor for options*/}

double Options::cost(){
    return _cost;
}

std::string Options::to_string() const{
    return "CUSTOM: " + _name + " ($" + std::to_string(_cost) + ')'; 
}


Options* Options::clone(){
	return new Options{*this};
}

std::ostream& operator<<(std::ostream& ost, const Options& opt){    
    ost << opt.to_string();
    return ost; 
}

std::string Options::get_name(){ return _name; }

void Options::save(std::ostream& ost){
	ost << _name << std::endl;
	ost << _cost << std::endl;
}


