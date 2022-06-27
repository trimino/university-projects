#include "disk.h"

Disk::Disk(std::string name, double cost, int f): Options(name, cost), _tb{f} {/*Constructor*/}

Disk::Disk(std::istream& ist): Options(ist){
	ist >> _tb;
	ist.ignore(32767, '\n'); 	
}

Disk::~Disk(){/*Destructor*/}

std::string Disk::to_string() const{
	return "DISK: " + _name + " ( $" + std::to_string(_cost) + ", " + std::to_string(_tb)  + "TB DISK )"; 
}

std::string Disk::get_name(){ return _name; }

void Disk::save(std::ostream& ost){
	ost << "&" << std::endl;
	Options::save(ost);
	ost << _tb << std::endl;
}

Disk* Disk::clone(){
	return new Disk{*this};
}



