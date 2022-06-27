#include "taxed.h"

double Taxed::_tax;

Taxed::Taxed(std::string name, double cost): Product(name,cost){}

Taxed::~Taxed(){};

void Taxed::set_tax_rate(double tax){
    Taxed::_tax  = tax;
}

double Taxed::price()const {
    
   return round( (_quantity * _cost * (1 + Taxed::_tax))* 100)/100 ;
}
