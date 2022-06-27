#include "product.h"

Product::Product(const std::string name, const double cost): _name{name}, _cost{cost},
_quantity{0}{
         if (cost < 0){
             throw std::runtime_error{"Cost can not be negative"};
         }
     }

Product::~Product(){}

void Product::set_quantity(int quantity){
    _quantity = quantity;
}

std::ostream& operator<<(std::ostream& ost, const Product& product){
        if (product._quantity == 0){
            ost << product._name << "( $" << product._cost << " )"; 
        }else{
            ost << product._name << "( " << product._quantity << " @ " << product._cost << " )";
        }
        return ost;
}


