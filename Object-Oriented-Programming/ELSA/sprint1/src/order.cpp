#include "order.h"

Order::Order(Customer& customer): _customer{customer}{/*constructor for order class*/}
Order::~Order(){/*destructor for order*/}

int Order::add_product(Desktop& desktop){
    _products.push_back(&desktop);
    return _products.size() - 1;
}

double Order::price()const{
    double sum = 0.0;
    if (!_products.empty()){
        for (Desktop* price : _products){
            sum += price->price();
        }
    }
    return sum;
}

std::ostream& operator<<(std::ostream& ost, const Order& order){
    ost << "Customer: " << order._customer;
    for(auto p : order._products) ost << "\n  " << *p;
    ost << "\nTotal price: $" << order.price();
    return ost;
}
    