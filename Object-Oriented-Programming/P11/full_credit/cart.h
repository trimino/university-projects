#ifndef __CART_H
#define __CART_h


#include <iostream>
#include <vector>
#include "item.h"

class Cart{
    
    public:
        Cart(std::string customer);
        ~Cart();
        Cart(const Cart& cart);

        Cart& operator=(const Cart& cart);
        void add_item(Item& item);
        double cost();


        std::vector<Item*>::iterator begin();
        std::vector<Item*>::iterator end();

    private:
        std::string _customer;
        std::vector<Item*> _items;
        

};

#endif