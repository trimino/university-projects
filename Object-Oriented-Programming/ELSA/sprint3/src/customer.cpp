#include "customer.h"
#include <iostream>

Customer::Customer(std::istream& ist){
	getline(ist,_name);
	getline(ist,_phone);
	getline(ist,_email);
}

Customer::Customer(std::string name, std::string phone, std::string email): _name{name}, _phone{phone}, _email{email}{ /*constructor for Cusotmer Class*/}

std::ostream& operator<<(std::ostream& ost, const Customer& customer){
    ost << customer._name << "(" << customer._phone << " - " << customer._email << ")";
    return ost;
}   

std::string Customer::get_name(){
	return _name;
}

void Customer::save(std::ostream& ost){
	ost << _name << std::endl;
	ost << _phone << std::endl;
	ost << _email << std::endl;
}
