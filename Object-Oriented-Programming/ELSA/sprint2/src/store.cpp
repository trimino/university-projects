#include "store.h"

/*
----------------------------------------------------------------------------------------------
Customer Object Methods
*/
//add customer to _customers vector
void Store::add_customer(Customer& customer){
    customers.push_back(customer);
}

//return the size for _customers vector
int Store::num_customers(){
    return customers.size();
}

//get Customer object at a specific index
Customer& Store::customer(int index){
    //at() throws out of range exception  
    return customers.at(index);
}

std::string Store::get_name(Customer customer){
	return customer.get_name();
}

/*
----------------------------------------------------------------------------------------------
Options Object Methods
*/

void Store::add_option(Options& opt){
    Options* ptr_opt = new Options{opt}; //copy assignment contructor called
    options.push_back(ptr_opt);
}

//return size of _options vector
int Store::num_options(){
    return options.size();
}

//is given the index of the option to add to the desktop at the provided index
void Store::add_option(int option, int desktop){
    Options* ptr_options = options.at(option);
    Desktop* desk = &(desktops.at(desktop));
    desk->add_option(*ptr_options);
}

//dereference object then return the address
Options& Store::option(int index){
    return *(options.at(index));
}

//added for mainwin to make code easier for user
std::string Store::option_name(Options& opt){
	return opt.get_name();
}

/*
----------------------------------------------------------------------------------------------
Desktop Object Methods
*/

//create a new Desktop object and push it the _desktops vector. Use push_back tehn return size -1 
int Store::new_desktop(){
    desktops.push_back(Desktop{});
    return desktops.size() - 1;
}

//return the size of the _desktops vector
int Store::num_desktops(){
    return desktops.size();
}

//get the Desktop object at specific index
Desktop& Store::desktop(int index){
    return desktops.at(index);
}

//given the index of desktop add it to an exisitng boject (Order)
void Store::add_desktop(int desktop, int order){
    Order* ord = &(orders.at(order));
    Desktop* desk = &(desktops.at(desktop));
    int ignor = ord->add_product(*desk); //add_product returns the index of this element 
}


/*
----------------------------------------------------------------------------------------------
Order Object Methods
*/

//create a new Order instance and push it on to the orders vector and return index
int Store::new_order(int customer){
    orders.push_back(Order{customers[customer]});
    return orders.size() - 1;
}

//return size of orders vector
int Store::num_orders(){
    return orders.size();
}

//return Order at specific index
Order& Store::order(int index){
    return orders.at(index);
}


