#include "cpu.h"

CPU::CPU(std::string name, double cost, int f): Options(name, cost), _freq{f} {/*Constructor*/}

CPU::CPU(std::istream& ist): Options(ist){
	ist >> _freq;
	ist.ignore(32767, '\n'); 	
}

CPU::~CPU(){/*Destructor*/}

std::string CPU::to_string() const{
	return "CPU: " + _name + " ( $" + std::to_string(_cost) + ", " + std::to_string(_freq)  + "freq )"; 
}

std::string CPU::get_name(){ return _name; }

void CPU::save(std::ostream& ost){
	ost << "@" << std::endl;
	Options::save(ost);
	ost << _freq << std::endl;
}

CPU* CPU::clone(){
	return new CPU{*this};
}


