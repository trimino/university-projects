#include "cart.h"

Cart::Cart(std::string customer): _customer{customer} {/*constructor body*/}

Cart::~Cart(){ for(Item* i: _items) delete i; }

Cart::Cart(const Cart& cart): _customer{cart._customer}{
    for(Item* i : cart._items)
        _items.push_back ( new Item{*i} );
}


Cart& Cart::operator=(const Cart& cart){
    if (this == &cart) return *this;

    this->~Cart();
    _customer = cart._customer;
    for(Item* i : cart._items)
        _items.push_back( new Item{*i} );

    return *this;
}


void Cart::add_item(Item& item){ _items.push_back( new Item{item} ); }


double Cart::cost(){ 
    double sum = 0;
    for(Item* i : _items) 
        sum+= i->cost();

    return sum;
}


/*  Return base address of array    */
std::vector<Item*>::iterator Cart::begin(){ return _items.begin(); }

/*  Return base address of array + size of array    */
std::vector<Item*>::iterator Cart::end(){ return _items.end() ;}
