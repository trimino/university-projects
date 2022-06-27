#include "mainwin.h"
#include <iostream> // for std::cerr logging


Mainwin::Mainwin() : store{new Store()} {

    /*==== GUI SETUP ====*/

    set_default_size(500, 500);
    set_title("ELSA");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

/*-----------------------------------------------------------------------------------------------------------------------------*/

    //	MENU
    //	Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    vbox->add(*menubar);

    //	FILE
    //	Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    
    //	SAVE
    //	Append a Save to the the File Menu
    Gtk::MenuItem* menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect([this] {this->on_save_click();});
    filemenu->append(*menuitem_save);		
    
    //	SAVE AS	
    //	Append a Save As to the File Menu
    Gtk::MenuItem* menuitem_save_as = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_save_as->signal_activate().connect([this] {this->on_save_as_click();});
    filemenu->append(*menuitem_save_as);
    
    //	Load
    //	Append a Load to the File Menu	
    Gtk::MenuItem* menuitem_load = Gtk::manage(new Gtk::MenuItem("_Load File", true));
    menuitem_load->signal_activate().connect([this] {this->on_load_click();});
    filemenu->append(*menuitem_load);


    //	QUIT
    //	Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);


/*-----------------------------------------------------------------------------------------------------------------------------*/


    //	INSERT 
    //	Create a Insert menu and add to the menu bar
    Gtk::MenuItem* menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu* insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);

    //	CUSTOMER (INSERT)
    //	Append Customer to the Insert Menu
    Gtk::MenuItem* menuitem_insert_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_insert_customer->signal_activate().connect([this] {this->on_insert_customer_click();});
    insertmenu->append(*menuitem_insert_customer);
   
    //	ORDER (INSERT)
    //	Append Order to the Insert Menu
    Gtk::MenuItem* menuitem_insert_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_insert_order->signal_activate().connect([this] {this->on_insert_order_click();});
    insertmenu->append(*menuitem_insert_order);

    //	PERIPHERAL (INSERT)
    //	Append Peripheral to the Insert Menu
    Gtk::MenuItem* menuitem_insert_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_insert_peripheral->signal_activate().connect([this] {this->on_insert_peripheral_click();});
    insertmenu->append(*menuitem_insert_peripheral);

    //	DESKTOP (INSERT)
    //	Append Desktop to the Insert Menu
    Gtk::MenuItem* menuitem_insert_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_insert_desktop->signal_activate().connect([this] {this->on_insert_desktop_click();});
    insertmenu->append(*menuitem_insert_desktop);


/*-----------------------------------------------------------------------------------------------------------------------------*/

    //	VIEW 
    //	Create a Veiw menu and add to the menubar
    Gtk::MenuItem* menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu* viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    //	CUSTOMER (VIEW)
    //	Append Customer to the View Menu
    Gtk::MenuItem* menuitem_view_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_view_customer->signal_activate().connect([this] {this->on_view_customer_click();});
    viewmenu->append(*menuitem_view_customer);

    //	ORDER (VIEW)
    //	Append Order to the View Menu
    Gtk::MenuItem* menuitem_view_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_view_order->signal_activate().connect([this] {this->on_view_order_click();});
    viewmenu->append(*menuitem_view_order);

    //	PERIPHERAL (VIEW)
    //	Append Peripheral to the View Menu
    Gtk::MenuItem* menuitem_view_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_view_peripheral->signal_activate().connect([this] {this->on_view_peripheral_click();});
    viewmenu->append(*menuitem_view_peripheral);

    //	DESKTOP (VIEW)
    //	Append Desktop to the View Menu
    Gtk::MenuItem* menuitem_view_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_view_desktop->signal_activate().connect([this] {this->on_view_desktop_click();});
    viewmenu->append(*menuitem_view_desktop);


/*-----------------------------------------------------------------------------------------------------------------------------*/

    //	HELP
    //	Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //	ABOUT
    //	Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);


	//	STATUS BAR
	msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);
    
    //	DATA	
    //	Add data to the vbox
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    vbox->add(*data);
    
    vbox->show_all();
}


    


Mainwin::~Mainwin() {/*DESTRUCTOR*/ }




/*==== CALLBACKS ====*/

void Mainwin::on_view_customer_click(){
	std::ostringstream oss;
	set_msg("Customers:\n");
	int size = store->num_customers();
	for(int i = 0 ; i < size;  ++i) 
		oss << i << ") " << store->customer(i) << "\n";
	set_data(oss.str());    
}

void Mainwin::on_view_order_click(){
	std::ostringstream oss;
	set_msg("Orders:\n");
	for(int i= 0; i < store->num_orders(); ++i) {
		oss << i << ") " << store->order(i) << "\n";
	}
	set_data(oss.str());
}

void Mainwin::on_view_peripheral_click(){
	std::ostringstream oss;
	set_msg("Peripherals:\n");
	for(int i= 0; i < store->num_options(); ++i) 
		oss << i << ") " << store->option(i) << "\n";
	set_data(oss.str());
}

void Mainwin::on_view_desktop_click(){
	std::ostringstream oss;
	set_msg("Desktops:\n");
	for(int i=0; i<store->num_desktops(); ++i) 
		oss << i << ") " << store->desktop(i) << "\n";
	set_data(oss.str());
}



void Mainwin::on_insert_customer_click(){
	std::vector<std::string> info = get_customer_info();
	if (info.at(0).size()){
		Customer customer{info.at(0), info.at(1), info.at(2)};
		store->add_customer(customer);
		set_msg("Added Customer !");
	}else{
		Gtk::MessageDialog{*this, "Customer was not added to our system :("}.run();
	}
}

void Mainwin::on_insert_order_click(){
	int customer = -1;
    int order    = -1;
    int desktop  = -1;
    try{
		std::vector<int> o = create_order();
		if(o.size()){
			customer = o.back();
			order = store->new_order(customer);
			store->add_desktop(o.at(0),order);
			set_msg("Order was place successfully!");
		}else{
			Gtk::MessageDialog{*this, "Order was not created :("}.run(); 
		}
	}catch(std::exception& e){
		Gtk::MessageDialog{*this, "Order was not created :("}.run();
	}
}

void Mainwin::on_insert_peripheral_click(){
	std::vector<std::string> info = get_peripheral_info();
	double cost = get_double(info.at(1));
	if(cost > 0 && info.at(0).size()){
		Options option{info.at(0),cost};
		store->add_option(option);
		set_msg("Added Peripheral !");
	}else{
		Gtk::MessageDialog {*this, "Peripheral was not added to our records :("}.run();
	}
}

void Mainwin::on_insert_desktop_click(){
	std::vector<int> choices = create_desktop();
	if(choices.size() && choices.at(0) != -1){
		int desktop = store->new_desktop();
		for(int x : choices){
			store->add_option(x, desktop);
		}
		set_msg("Peripherals added !");
	}else{
		Gtk::MessageDialog {*this, "No options added to desktop :("}.run();
	}
}


void Mainwin::on_save_click(){}
void Mainwin::on_save_as_click(){}
void Mainwin::on_load_click(){}

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("ELSA");
    auto logo = Gdk::Pixbuf::create_from_file("elsa_design.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 1.2.1");
    dialog.set_copyright("Copyright 2017-2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"David Trimino"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "Logo by freelogodesign.org, licensed for personal and commercial purposes with attribution https://www.ekomi.co.uk/review-freelogodesign.html"};
    dialog.set_artists(artists);
    dialog.run();
}



/* ==== UTILITIES ==== */

std::vector<std::string> Mainwin::get_customer_info(){
	std::vector<std::string> info;
	//Create a Dialog
	Gtk::Dialog dialog{"Customer's Info", *this};
	
	//Create a 2x3 grid
	Gtk::Grid grid;
	
	//Create labels for propmts
	Gtk::Label name{"Name: "};
	Gtk::Label phone{"Phone (xxx-xxx-xxxx): "};
	Gtk::Label email{"Email (xxx@domain.com: "};
	
	//Attach labels to the grid 
	grid.attach(name,0,0,1,1);
	grid.attach(phone,0,1,1,1);
	grid.attach(email,0,2,1,1);
	
	//Make an entry to user information
	Gtk::Entry e_name;
	Gtk::Entry e_phone;
	Gtk::Entry e_email;
	
	//Attach the Entry's on the grid
	grid.attach(e_name,1,0,1,1);
	grid.attach(e_phone,1,1,1,1);
	grid.attach(e_email,1,2,1,1);
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add an _Ok and _Cancel button
	dialog.add_button("_Ok", 1);
	dialog.add_button("_Cancel",0);
	
	//show the dialog to the user
	dialog.show_all(); 
	dialog.run();

	info.push_back(e_name.get_text());
	info.push_back(e_phone.get_text());
	info.push_back(e_email.get_text());
	
	return info;
}


std::vector<int> Mainwin::create_order(){
	//the first element is for the Customer indexes 
	std::vector<int> o;
	
	//Create Dialog, Grid, 2 Label, and 2 ComboBoxText
	Gtk::Dialog dialog{"Create a New Order", *this};
	Gtk::Grid grid;
	Gtk::Label customr{"Which Customer ?"};
	Gtk::Label desktop{"Which Desktop ?"};
	Gtk::ComboBoxText c_customr;
	Gtk::ComboBoxText c_desktop;
	
	//Assign positon in grid
	grid.attach(customr,0,0,1,1);
	grid.attach(c_customr,1,0,1,1);
	grid.attach(desktop,0,1,1,1);
	grid.attach(c_desktop,1,1,1,1);
	
	//Populate the comboboxtext
	int cust = store->num_customers();
	int desk = store->num_desktops(); 
	
	for(int i=0; i<cust; ++i){
		Customer customer = store->customer(i);
		c_customr.append(store->get_name(customer));
	}
	for(int i=0; i<desk; ++i)
		c_desktop.append(std::to_string(i));
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add Select and Cancel button
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);		
	
	//Display to user
	dialog.show_all();
	dialog.run();
	
	o.push_back(c_desktop.get_active_row_number());
	o.push_back(c_customr.get_active_row_number());
	return o;
	int result,c,d;
}

std::vector<std::string> Mainwin::get_peripheral_info(){
	
	std::vector<std::string> info;
	
	//Create a Dialog
	Gtk::Dialog dialog{"Peripheral Info", *this};
	
	//Create a Grid
	Gtk::Grid grid;
	
	//Create Labels and Entry to go on the grid
	Gtk::Label name{"Name: "};
	Gtk::Label price{"Price (US dollars): $"};
	Gtk::Entry e_name;
	Gtk::Entry e_price;
	
	//Attach the labels and entry's to the grid
	grid.attach(name,0,0,1,1);
	grid.attach(price,0,1,1,1);
	grid.attach(e_name,1,0,1,1);
	grid.attach(e_price,1,1,1,1);
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add an Ok and Cancel button to the dialog
	dialog.add_button("_Ok", 1);
	dialog.add_button("_Cancel", 0);
	
	//Display to user
	dialog.show_all();
	dialog.run();
	
	info.push_back(e_name.get_text());
	info.push_back(e_price.get_text());
	
	return info;	
}


std::vector<int> Mainwin::create_desktop(){
	
	//Keeps track of the indexes 
	std::vector<int> choice;
	
	//Create a Dialog
	Gtk::Dialog dialog{"Create Your Desktop", *this};
	
	//Create a grid
	Gtk::Grid grid;
	
	//Create Label
	Gtk::Label pick{"Pick Peripheral"};
	Gtk::ComboBoxText c_peripheral;	
	
	//Attach label and combox to grid
	grid.attach(pick,0,0,1,1);
	grid.attach(c_peripheral,1,0,1,1);
		
	//Add to combotext (rows start at 0 in combo box)
	int num_peripheral = store->num_options();
	for(int i=0; i<num_peripheral; ++i){
		Options opt = store->option(i);
		std::string name = opt.get_name();
		c_peripheral.append(name);
	}
	
	//Attach grid to dialog
	dialog.get_content_area()->add(grid);
	
	//Add Select and Cancel button
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	
	//Display to user
	dialog.show_all();
	int result;
	while((result = dialog.run()) == Gtk::RESPONSE_OK){
		choice.push_back(c_peripheral.get_active_row_number());
	}

	return choice;
}

double Mainwin::get_double(std::string prompt){
    double num;
    try{
    	num = std::stod(prompt);
    }catch(std::exception& e){
		num = -1.0;
    }
    return num;
}

int Mainwin::get_int(std::string prompt){
	
	int num;
	try{	
		num = std::stoi(prompt);
	}catch(std::exception& e){
		num = -1;
	}
	return num;
}


void Mainwin::set_data(std::string s){
	data->set_text(s);
	data->set_alignment(0.0,0.0);
}

void Mainwin::set_msg(std::string s){
	msg->set_markup("<b>"+s+"</b>");
	msg->set_alignment(0.0,0.0);
}


