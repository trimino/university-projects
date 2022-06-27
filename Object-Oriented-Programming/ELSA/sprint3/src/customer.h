#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <string>

class Customer{
    public:
		Customer(std::istream& ist);
        Customer(std::string name, std::string phone, std::string email);
        std::string get_name();	//this was not in the model but makes code easier
        friend std::ostream& operator<<(std::ostream& ost, const Customer& customer);
        void save(std::ostream& ost);
        
    private:
        std::string _name;
        std::string _phone;
        std::string _email;
};

#endif
