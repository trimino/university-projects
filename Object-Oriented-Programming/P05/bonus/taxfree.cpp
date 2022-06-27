#include "taxfree.h"

Taxfree::Taxfree(std::string name, double cost): Product(name,cost){}

Taxfree::~Taxfree(){}

double Taxfree::price() const {
    return round(_quantity * _cost * 100)/100;
}