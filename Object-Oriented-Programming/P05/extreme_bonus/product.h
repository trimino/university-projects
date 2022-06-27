#ifndef __PRODUCT_H
#define __PRODUCT_H
#include <string>
#include <iostream>
#include <cmath>

class Product{
    public:
        Product(std::string name, double cost);
        void set_quantity(int quantity);
        virtual ~Product();
        virtual double price() const = 0;
        virtual Product* clone() = 0;
        friend std::ostream& operator<<(std::ostream& ost, const Product& product);
    
    protected:
        std::string _name;
        double _cost;
        int _quantity;
};
#endif