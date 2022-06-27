#include "store.h"

Store::Store(){}
Store::Store(std::istream& ist){
	
	/*Insert Customers*/
	int size;
	ist >> size;
	ist.ignore(32767, '\n');
	if(!ist) throw std::runtime_error{"Invalid type for size (Customers)\n"};
	for(int i = 0; i < size; ++i){
		Customer customer{ist};
		customers.push_back(customer);
		if(!ist) throw std::runtime_error{"Something went worng for customers\n"};
	}
	
	
	
	/*Insert Options/Peripherals*/
	if(ist.eof()) size = 0;
	else{
		ist >> size;
		ist.ignore(32767, '\n');
		if(!ist) throw std::runtime_error{"Invalid type for size Options\n"};
	}
	for(int i = 0; i < size; ++i){
		char s = ist.peek();
		if ( s == '#'){
			std::string temp;
			ist >> temp;	//get rid of the # line
			ist.ignore(32767,'\n');	
			Ram* ptr = new Ram{ist};
			options.push_back(ptr);
			if(!ist) throw std::runtime_error{"Something went wrong for options\n"};
			
		}else if( s == '@'){
			std::string temp;
			ist >> temp;	//get rid of the @ line
			ist.ignore(32767, '\n');
			CPU* ptr = new CPU{ist};
			options.push_back(ptr);
			if(!ist) throw std::runtime_error{"Something went wrong for options\n"};
			
		}else if( s == '&'){
			std::string temp;
			ist >> temp;	//get rid of the & line
			ist.ignore(32767, '\n');
			Disk* ptr = new Disk{ist};
			options.push_back(ptr);
			if(!ist) throw std::runtime_error{"Something went wrong for options\n"};
			
		}else {
			Options* ptr = new Options{ist};
			options.push_back(ptr);
			if(!ist) throw std::runtime_error{"Something went wrong for options\n"};
		}
	}
	
	
	
	
	/*Insert Desktops*/
	if(ist.eof()) size = 0;
	else{
		ist >> size;
		ist.ignore(32767, '\n');
		if(!ist) throw std::runtime_error{"Invalid type for size Options\n"};
	}
	for(int i = 0; i < size; ++i){
		Desktop d{ist, options};
		desktops.push_back(d);
		if(!ist) throw std::runtime_error{"Something went wrong for desktops\n"};
	}
	
	
	/*Insert Orders*/
	if(ist.eof()) size = 0;
	else{
		ist >> size;
		ist.ignore(32767, '\n');
		if(!ist) throw std::runtime_error{"Invalid type for size Options\n"};
	}
	for(int i = 0; i < size; ++i){
		Order order{ist, desktops, customers};
		orders.push_back(order);
		if(!ist) throw std::runtime_error{"Something went wrong for orders\n"};
	}
}


void Store::save(std::ostream& ost){
	ost << customers.size() << std::endl;
	for(int i = 0; i < customers.size() ; ++i)
		customers.at(i).save(ost);
	
	ost << options.size() << std::endl;
	for(int i = 0; i < options.size() ; ++i)
		options.at(i)->save(ost);
	
	ost << desktops.size() << std::endl;
	for(int i = 0; i < desktops.size(); ++i)
		desktops.at(i).save(ost, options);
	
	ost << orders.size() << std::endl;
	for(int i = 0; i < orders.size(); ++i)
		orders.at(i).save(ost, desktops, customers);	
}

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

void Store::add_option(Options& opt){ options.push_back(opt.clone()); }

//return size of _options vector
int Store::num_options(){
    return options.size();
}

//is given the index of the option to add to the desktop at the provided index
void Store::add_option(int option, int desktop){ desktops[desktop].add_option(*options[option]); }

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
	orders[order].add_product(desktops[desktop]);
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
    return orders[index];
}



/*
----------------------------------------------------------------------------------------------
Remove Methods
*/


bool Store::remove_customer(std::string name, std::string phone){
	
	int index = find_customer(name, phone);
		 
	//Special Case
	if(customers.size() == 0 || index < 0) return false;
	
	//Get Address of Customer that wants to be deleted
	Customer* ptr_customer = &customers.at(index );
	
	//Delete Customer from customers vector
	customers.erase( customers.begin()+index );


	//Loop through all Orders to make sure that all orders placed by that Customer is erased 
	for(int i = 0; i < orders.size(); ++i){
		Customer* o = orders.at(i).get_customer();
		if( o == ptr_customer) {
			orders.at(i).erase_vector();
			orders.erase(orders.begin() + i );
		}
	}
	return true;
}


int Store::find_customer(std::string name, std::string phone){
	//verify phone number is in proper form 
	if( !regex_phone_test(phone) ) return -1;
	if (name.size() == 0 ) return -1;
	
	//convert the name to lower case
	to_lower(name);
	
	//iterate through customers vectors
	for(int i = 0; i < customers.size(); ++i){
		std::string customers_name = customers.at(i).get_name();
		std::string customers_phone = customers.at(i).get_phone();
		to_lower(customers_name);
		if( name == customers_name && phone == customers_phone ) return i;		
	}
	return -2;
}


void Store::to_lower(std::string& str){
	for(char& c : str){
		c = ::tolower(c);
	}
}


bool Store::regex_phone_test(std::string phone){
	std::regex a("\\+?1?\\d{3}-\\d{3}-\\d{4}");
	if(std::regex_match(phone, a) ) return true;
	return false;
}





