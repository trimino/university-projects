#ifndef __STORE_H
#define __STORE_H

#include <vector>
#include "order.h"
#include "desktop.h"
#include "options.h"
#include "customer.h"

class Store{
    public:
        void add_customer(Customer& customer); 
        int num_customers();                    
        Customer& customer(int index);
		std::string get_name(Customer customer); //not in model added by us

        void add_option(Options& opt);
        void add_option(int option, int desktop);
        int num_options();
        Options& option(int index);
        std::string option_name(Options& opt); //not in model added by us

        int new_desktop();
        int num_desktops();
        Desktop& desktop(int index);
        void add_desktop(int desktop, int order);

        int new_order(int customer);
        int num_orders();
        Order& order(int index);
        

    private:
        std::vector<Customer> customers;
        std::vector<Options*> options;
        std::vector<Desktop> desktops;
        std::vector<Order> orders;
};

#endif
