#include "order.h"

Order::Order(Customer& customer): _customer{&customer}{/*constructor for order class*/}

Order::Order(std::istream& ist, std::vector<Desktop>& desktops, std::vector<Customer>& customers){
	int customer_index, product_size, desktop_index;
	ist >> customer_index >> product_size;
	ist.ignore(32767, '\n');
	_customer = &(customers.at(customer_index));
	for(int i = 0; i < product_size; ++i){
		int index;
		ist >> index;
		Desktop* ptr_d = &(desktops.at(index));
		_products.push_back(ptr_d);
		if(!ist) throw std::runtime_error{"ERROR IN ORDER CONSTRUCTOR :(\n"};
	}
}

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
 ost << "Customer: " << order._customer->get_name();
    for(auto p : order._products) ost << "\n  " << *p;
    ost << "\nTotal price: $" << order.price();
    return ost;
}


void Order::save(std::ostream& ost, std::vector<Desktop>& desktops, std::vector<Customer>& customer){
	int customer_index;
	std::vector<int> desktop_index;
	
	/* Get the index where the _customer is located in Store::customers vector*/
	for(int i = 0; i < customer.size(); ++i){
		Customer* ptr = &(customer.at(i));
		if( ptr == _customer ){
			customer_index = i;
			break;
		}
	}
	
	/*Get the indexes where each of the _product elements are in Store::desktops*/
	for(int i = 0; i < desktops.size(); ++i){
		Desktop* ptr_desktop = &(desktops.at(i));
		for(Desktop* ptr_product : _products){
			if( ptr_desktop == ptr_product ){
				desktop_index.push_back(i);
				break;
			}
		}
	}
	
	/*write the index where this customer is in Store::customers and write the index where each desktop is in Store::desktops*/
	ost << customer_index << std::endl;
	ost << desktop_index.size() << std::endl;
	for(int i : desktop_index)
		ost << i << std::endl;
}
