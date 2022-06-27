#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "store.h"
#include "entrydialog.h"


class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();

    protected:
    
		//	Callbacks for Toolbar
		void on_add_object_click();
		void on_remove_object_click();
		
		//	View Callbacks
        void on_view_peripheral_click();
		void on_view_desktop_click();
		void on_view_order_click();
		void on_view_customer_click();

		//	Insert Callbacks
		void on_insert_peripheral_click(int spec);
		void on_insert_desktop_click();
		void on_insert_order_click();
		void on_insert_customer_click();
		
		//Remove Callbacks
		void on_remove_customer_click();


		//	File I/O callbacks
		void on_new_store_click();
		void on_about_click();             // Display About dialog
		void on_quit_click();              // Exit the game
		void on_load_click();
		void on_save_click();
		void on_save_as_click();
		
		//	Helper Methods for insert
		void get_peripheral_info();
		void get_cpu_ram_disk_info(int spec);
		std::vector<int> create_desktop();

		
		//	Data varifiaation 
		std::string get_string(std::string prompt);
		double get_double(std::string prompt);
		int get_int(std::string prompt);
		bool regex_phone(std::string phone);
		bool regex_email(std::string email);
		bool name_peripherals(std::string name);

		//	Status and Data label 
		void set_data(std::string s);
		void set_msg(std::string s);
		
    private:
		Store* store;		
		Gtk::Label* data;
		Gtk::Label* msg;
		bool need_save_as;
		std::string filename;
};


#endif 

