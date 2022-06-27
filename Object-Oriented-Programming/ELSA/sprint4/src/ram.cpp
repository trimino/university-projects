#include "ram.h"

Ram::Ram(std::string name, double cost, int gb): Options(name, cost), _gb{gb} {/*Constructor*/}

Ram::Ram(std::istream& ist): Options(ist){
	ist >> _gb;
	ist.ignore(32767, '\n'); 	
}

Ram::~Ram(){/*Destructor*/}

std::string Ram::to_string() const{
	return "RAM: " +_name + " ( $" + std::to_string(_cost) + " " + std::to_string(_gb)  + "GB )"; 
}

std::string Ram::get_name(){ return _name; }

void Ram::save(std::ostream& ost){
	ost << "#" << std::endl;
	Options::save(ost);
	ost << _gb << std::endl;
}

Ram* Ram::clone(){
	return new Ram{*this};
}




