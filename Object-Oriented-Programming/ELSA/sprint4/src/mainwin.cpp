#include "mainwin.h"
#include <iostream> // for std::cerr logging


Mainwin::Mainwin() : store{new Store()} {

    /*==== GUI SETUP ====*/
    set_default_size(800, 800);
    set_title("ELSA");
	
    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

/*-----------------------------------------------------------------------------------------------------------------------------*/

    //	MENU
    //	Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    //vbox->add(*menubar);

    //	FILE
    //	Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    
    //	NEW GAME
    //	Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] {this->on_new_store_click();});
    filemenu->append(*menuitem_new);
    
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
    
    //	OPEN FILE
    //	Append a Load to the File Menu	
    Gtk::MenuItem* menuitem_load = Gtk::manage(new Gtk::MenuItem("_Open File", true));
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
    //	Append Peripheral to the Insert Menu and Also put a menu in Peripheral
    Gtk::MenuItem* menuitem_insert_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    Gtk::Menu* menu_option = Gtk::manage(new Gtk::Menu());
    menuitem_insert_peripheral->set_submenu(*menu_option);
    insertmenu->append(*menuitem_insert_peripheral);
    
    
    //	CUSTOM (PERIPHERAL)
    //	Append a Custom to Peripheral menu for a generic Peripheral 
    Gtk::MenuItem* custom_per = Gtk::manage(new Gtk::MenuItem("_Custom", true));
    custom_per->signal_activate().connect([this] {this->on_insert_peripheral_click(0);});
    menu_option->append(*custom_per);
    
    //	RAM (PERIPHERAL)
    //	Append RAM to Peripheral menu
    Gtk::MenuItem* ram_per = Gtk::manage(new Gtk::MenuItem("_RAM", true));
    ram_per->signal_activate().connect([this] {this->on_insert_peripheral_click(1);});
    menu_option->append(*ram_per);
    
    //	CPU (PERIPHERAL)
    //	Apend CPU to Periphearl menu
    Gtk::MenuItem* cpu_per = Gtk::manage(new Gtk::MenuItem("_CPU", true));
    cpu_per->signal_activate().connect([this] {this->on_insert_peripheral_click(2);});
    menu_option->append(*cpu_per);
    
    //	DISK (PERIPHERAL)
    //	Append DISK to Peripheral menu
    Gtk::MenuItem* disk_per = Gtk::manage(new Gtk::MenuItem("_DISK", true));
    disk_per->signal_activate().connect([this] {this->on_insert_peripheral_click(3);});
    menu_option->append(*disk_per);
    
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

	//	REMOVE
	//	Create a remove menu and add it to menu bar
	Gtk::MenuItem* menuitem_remove = Gtk::manage(new Gtk::MenuItem("_Remove", true));
	menubar->append(*menuitem_remove);
	Gtk::Menu* remove_menu = Gtk::manage(new Gtk::Menu());
	menuitem_remove->set_submenu(*remove_menu);

	//	CUSTOMER (REMOVE)
	//	Append Customer to Remove Menu
	Gtk::MenuItem* menuitem_remove_customer = Gtk::manage(new Gtk::MenuItem("_CUSTOMER", true));
	menuitem_remove_customer->signal_activate().connect([this] {this->on_remove_customer_click();});
	remove_menu->append(*menuitem_remove_customer);
	
	
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


/*-----------------------------------------------------------------------------------------------------------------------------*/


	//	TOOLBAR
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);
    
    //	OPEN
    Gtk::ToolButton* file_open_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::OPEN));
    file_open_button->set_tooltip_markup("Open File");
    file_open_button->signal_clicked().connect([this] {this->on_load_click();});
    file_open_button->set_expand(true);
    toolbar->append(*file_open_button);

    //	SAVE
	Gtk::ToolButton* save_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
	save_button->set_tooltip_markup("Save Any Progress Made");
	save_button->signal_clicked().connect([this] {this->on_save_click();});
	save_button->set_expand(true);
	toolbar->append(*save_button);

    //	ADD 
    Gtk::ToolButton* add_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::ADD));
    add_button->set_tooltip_markup("Insert Customer, Order, and more");
    add_button->signal_clicked().connect([this] {this->on_add_object_click();});
    add_button->set_expand(true);
    toolbar->append(*add_button);
    
    //	REMOVE
    Gtk::ToolButton* remove_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::REMOVE));
    remove_button->set_tooltip_markup("Remove Customer ");
    remove_button->signal_clicked().connect([this] {this->on_remove_customer_click();});
    remove_button->set_expand(true);
    toolbar->append(*remove_button);

	//	QUIT
    //	Add a icon for quitting
	Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
	quit_button->set_tooltip_markup("Exit game");
	quit_button->signal_clicked().connect([this] {this->on_quit_click();});
	Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
	sep->set_expand(true);  // The expanding sep forces the Quit button to the right
	toolbar->append(*sep);
	toolbar->append(*quit_button);


/*-----------------------------------------------------------------------------------------------------------------------------*/


	//	STATUS BAR
	msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);
    
    //	DATA	
    //	Add data to the vbox
	data = Gtk::manage(new Gtk::Label{"", Gtk::ALIGN_START, Gtk::ALIGN_START});
    data->set_hexpand();
    
	//	Making the data scrollable (vertically and horizontally)
	Glib::RefPtr<Gtk::Adjustment> v_adjustment = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1, 10, 0);	
	Glib::RefPtr<Gtk::Adjustment> h_adjustmnet = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1, 10, 0);
    Gtk::ScrolledWindow* scroll_window = Gtk::manage(new Gtk::ScrolledWindow);
    scroll_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    scroll_window->set_placement(Gtk::CORNER_TOP_LEFT);
    scroll_window->set_vadjustment(v_adjustment);
    scroll_window->set_hadjustment(h_adjustmnet);
    //	Add a child to ScrollWindow
    scroll_window->add(*data);
    
    //	A Gtk::Label is intrinsically transparent - it's background color cannot be set
    //	Therefore, we add it to a Gtk::EventBox with background color overridden to white
    Gtk::EventBox *eb = Gtk::manage(new Gtk::EventBox);
    eb->set_hexpand();
    eb->set_vexpand();
    eb->override_background_color(Gdk::RGBA("white"));
    
    //	Add the Widget(ScrollWindow) to the Box(EventBox)
	eb->add(*scroll_window);
    
    // PACK_EXPAND_WIDGET tells VBox this widget should be as big as possible
    vbox->pack_start(*eb, Gtk::PACK_EXPAND_WIDGET, 0);
	
    vbox->show_all();
    on_new_store_click();
}


Mainwin::~Mainwin() {/*DESTRUCTOR*/ }





/*==== CALLBACKS ====*/


void Mainwin::on_add_object_click(){
	Gtk::Dialog dialog{"CLICK TO INSERT", *this};
	dialog.set_transient_for(*this);
	Gtk::Toolbar toolbar = Gtk::Toolbar();

    
    //	ToolButton for Customer
    Gtk::Image customer_image = Gtk::Image{"customer.png"};
    Gtk::ToolButton customer_button = Gtk::ToolButton(customer_image);
    customer_button.set_tooltip_markup("Insert new Customer");
    customer_button.signal_clicked().connect([this] {this->on_insert_customer_click();} );
    customer_button.set_expand(true);
	toolbar.append(customer_button);
    
    //	ToolButton for Order
    Gtk::Image order_image = Gtk::Image{"orders.png"};
    Gtk::ToolButton order_button = Gtk::ToolButton(order_image);
    order_button.set_tooltip_markup("Insert new Order");
    order_button.signal_clicked().connect([this] {this->on_insert_order_click();} );
    order_button.set_expand(true);  
	toolbar.append(order_button);
    
    //	ToolButton for Peripheral
    Gtk::Image peripheral_image = Gtk::Image{"options.png"};
    Gtk::ToolButton peripheral_button = Gtk::ToolButton(peripheral_image);
    peripheral_button.set_tooltip_markup("Insert new Peripheral");
    peripheral_button.signal_clicked().connect([this] {this->on_insert_peripheral_click(0);} );
    peripheral_button.set_expand(true); 
	toolbar.append(peripheral_button);
   
    //	ToolButton for Desktop
    Gtk::Image desktop_image = Gtk::Image{"desktop.png"};
    Gtk::ToolButton desktop_button = Gtk::ToolButton(desktop_image);
    desktop_button.set_tooltip_markup("Insert new Desktop");
    desktop_button.signal_clicked().connect([this] {this->on_insert_desktop_click();} );
    desktop_button.set_expand(true);
    toolbar.append(desktop_button);
    
    dialog.get_content_area()->add(toolbar);
    dialog.set_default_size(400,100);
    dialog.show_all();
	dialog.run();
}

void Mainwin::on_new_store_click() {
	need_save_as = true;
    delete store;
    store = new Store;
    filename = "untitled.elsa";
    set_data("");
    set_msg("New store created");
}

void Mainwin::on_view_customer_click(){
	std::ostringstream oss;
	oss << "<big><b>Customers</b></big><tt>\n\n";
	if(store != nullptr)
		for(int i = 0 ; i < store->num_customers();  ++i) 
			oss << i+1 << ") " << store->customer(i) << "\n";
	oss<<"</tt>";
	set_data(oss.str());
	set_msg("");
}


void Mainwin::on_view_order_click(){
	std::ostringstream oss;
	oss << "<big><b>Orders</b></big><tt>\n\n";
	if(store != nullptr){
		for(int i= 0; i < store->num_orders(); ++i) 
			oss << i+1 << ") " << store->order(i) << "\n";
	}
	oss<<"</tt>";
	set_data(oss.str());
	set_msg("");
}


void Mainwin::on_view_peripheral_click(){
	std::ostringstream oss;
	oss << "<big><b>Peripherals</b></big><tt>\n\n";
	if(store != nullptr)
		for(int i= 0; i < store->num_options(); ++i) 
			oss << i+1 << ") " << store->option(i) << "\n";
	oss<<"</tt>";
	set_data(oss.str());
	set_msg("");
}


void Mainwin::on_view_desktop_click(){
	std::ostringstream oss;
	oss << "<big><b>Desktops</b></big><tt>\n\n";
	if(store != nullptr)
		for(int i=0; i<store->num_desktops(); ++i) 
			oss << i+1 << ") " << store->desktop(i) << "\n";
	oss<<"</tt>";
	set_data(oss.str());
	set_msg("");
}


/* ==> INSERT MENU BAR <== */
void Mainwin::on_insert_customer_click(){
	
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
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Done",Gtk::RESPONSE_CANCEL);
	
	//show the dialog to the user
	dialog.show_all(); 
	int result;
	std::string c_name, c_phone, c_email;
	
	while( (result = dialog.run()) == Gtk::RESPONSE_OK ){
		c_name = e_name.get_text();
		c_phone = e_phone.get_text();
		c_email = e_email.get_text();
		bool email_test = regex_email(c_email);
		bool phone_test = regex_phone(c_phone);
		
		if( c_name.size() != 0 && email_test && phone_test ){
			Customer customer{c_name, c_phone, c_email};
			store->add_customer(customer);
			set_msg("Added Customer !");
			on_view_customer_click();
		}else{
			Gtk::MessageDialog {*this, "Customer was not added to our records\n Enter data in appropiate format "}.run();
			if (c_name.size() == 0 ) e_name.set_text("*name*"); 
			if( !email_test ) e_email.set_text("xyz@domain.com");
			if( !phone_test ) e_phone.set_text("xxx-xxx-xxxx");
		}
	}
}


void Mainwin::on_insert_order_click(){
	on_view_desktop_click();
	
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
	for(int i=0; i < store->num_customers(); ++i){
		Customer customer = store->customer(i);
		c_customr.append(store->get_name(customer));
	}
	
	for(int i=0; i < store->num_desktops(); ++i)
		c_desktop.append(std::to_string(i + 1));
	
	c_customr.set_active(0);
	c_desktop.set_active(0);
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add Select and Cancel button
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Done", Gtk::RESPONSE_CANCEL);		
	
	//Display to user
	dialog.show_all();
	int result;
	int customer = 0, order;
	for(int i = 0; (result = dialog.run()) == Gtk::RESPONSE_OK; ++i){
		if(i == 0) {
			customer = c_customr.get_active_row_number();
			c_customr.remove_all();
			order = store->new_order(customer);
		}
		store->add_desktop(c_desktop.get_active_row_number(), order);
		set_msg("Order Added !");
	}
	
	on_view_order_click();
}


void Mainwin::on_insert_peripheral_click(int spec){
	if( spec == 0) 	 get_peripheral_info(); 
	else get_cpu_ram_disk_info(spec);
}


void Mainwin::on_insert_desktop_click(){
	std::vector<int> choices = create_desktop();
	if(choices.size() && choices.at(0) != -1){
		int desktop = store->new_desktop();
		for(int x : choices){
			store->add_option(x, desktop);
		}
		on_view_desktop_click();
		set_msg("Peripherals added !");
	}else{
		Gtk::MessageDialog {*this, "No options added to desktop :("}.run();
	}
}


void Mainwin::on_save_click(){
	if(need_save_as) on_save_as_click();
	try{
		std::ofstream ofs{filename};
		store->save(ofs);
		if(!ofs) throw std::runtime_error("Error writing to file");
		set_msg("Saved " + filename);
	}catch(std::exception& e){
		std::string err = "Unable to save store to " + filename;
        set_msg("<b>ERROR:</b> " + err);
        Gtk::MessageDialog{*this, err, false, Gtk::MESSAGE_WARNING}.run();
	}
}


void Mainwin::on_save_as_click(){
	need_save_as = false;
	Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_elsa = Gtk::FileFilter::create();
    filter_elsa->set_name("ELSA files");
    filter_elsa->add_pattern("*.elsa");
    dialog.add_filter(filter_elsa);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename(filename);
	
    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);

    int result = dialog.run();
    if (result == 1) {
        filename = dialog.get_filename();
        on_save_click();
    }
}


void Mainwin::on_load_click(){
	need_save_as = false;
	Gtk::FileChooserDialog dialog{"Please choose a file",
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN};
	dialog.set_transient_for(*this);
	
	auto filter_elsa = Gtk::FileFilter::create();
	filter_elsa->set_name("ELSA files");
	filter_elsa->add_pattern("*.elsa");
	dialog.add_filter(filter_elsa);
	
	auto filter_anything = Gtk::FileFilter::create();
	filter_anything->set_name("Any files");
	filter_anything->add_pattern("*");
	dialog.add_filter(filter_anything);
	
	dialog.set_filename(filename);	
	
	dialog.add_button("_Cancel", 0);
	dialog.add_button("_Open", 1);
	
	int result = dialog.run();
	if( result == 1 ){
		try{
			delete store;
			store = nullptr;
			filename = dialog.get_filename();
			std::ifstream ifs{filename};
			store = new Store{ifs};
			if(!ifs) throw std::runtime_error("File contents bad");
			on_view_customer_click();
			set_msg("<b>LOADED FILE</b>");
		}catch(std::exception& e){
			std::string err = "Unable to open store from " + filename + " (" + e.what() + " )";
            on_new_store_click();
            set_msg("<b>ERROR:</b>: " + err);
            Gtk::MessageDialog{*this, err, false, Gtk::MESSAGE_WARNING}.run();
        }
	}
}


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

void Mainwin::get_peripheral_info(){
	
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
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Done", Gtk::RESPONSE_CANCEL);
	
	//Display to user
	dialog.show_all();
	int result;
	double custom_price;
	std::string custom_name;
	
	while( (result = dialog.run()) == Gtk::RESPONSE_OK ){
		custom_name = e_name.get_text();
		custom_price = get_double( e_price.get_text() );
		bool name_test = name_peripherals(custom_name);
		
		if( custom_name.size() != 0 && custom_price > 0 && !name_test){
			Options opt{custom_name, custom_price};
			store->add_option(opt);
			set_msg("Added Peripheral !");
			on_view_peripheral_click();
		}else{
			Gtk::MessageDialog {*this, "Peripheral was not added to our records\nInvalid Characters: %, #, &, @"}.run();
			if (custom_name.size() == 0 ) { e_name.set_text("*name*"); continue; }
			if(name_test) { e_name.set_text("Invalid characters: #, @, &, and %"); continue; }
			if(custom_price == -1) { e_price.set_text("Enter number"); continue; }
		}
	}
}


/* Dialog for CPU, RAM, DISK */
void Mainwin::get_cpu_ram_disk_info(int spec){

	//Create a Dialog
	Gtk::Dialog dialog{"Peripheral Info", *this};
	
	//Create a Grid
	Gtk::Grid grid;
	
	//Create Labels and Entry to go on the grid
	Gtk::Label name{"Name: "};
	Gtk::Label price{"Price (US dollars): $"};
	Gtk::Label mem{"Memory/Frequency: "};
	Gtk::Entry e_mem;
	Gtk::Entry e_name;
	Gtk::Entry e_price;
	
	//Attach the labels and entry's to the grid
	grid.attach(name,0,0,1,1);
	grid.attach(price,0,1,1,1);
	grid.attach(mem,0,2,1,1);
	grid.attach(e_name,1,0,1,1);
	grid.attach(e_price,1,1,1,1);
	grid.attach(e_mem,1,2,1,1);
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add an Ok and Cancel button to the dialog
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Done", Gtk::RESPONSE_CANCEL);
	
	//Display to user
	dialog.show_all();
	int result, prod_memory;
	double prod_price;
	std::string prod_name;
	
	while( (result = dialog.run()) == Gtk::RESPONSE_OK ){
		prod_name = e_name.get_text();
		prod_price = get_double( e_price.get_text() );
		prod_memory = get_int( e_mem.get_text() );
		bool name_test = name_peripherals(prod_name);
			  
		
		if( prod_name.size() != 0 && prod_price != -1.0 && prod_memory > 0 && !name_test ){
			if( spec == 1 ) {
				Ram ram{prod_name, prod_price, prod_memory};
				store->add_option(ram);
				set_msg("Added RAM !");
			}else if( spec == 2) {
				CPU cpu{prod_name, prod_price, prod_memory};
				store->add_option(cpu);
				set_msg("Added CPU !");
			}else{
				Disk disk{prod_name, prod_price, prod_memory};
				store->add_option(disk);
				set_msg("Added DISK !");
			}
			on_view_peripheral_click();
			
		}else{
			Gtk::MessageDialog {*this, "Peripheral was not added to our records\n\nInvalid Characters: %, #, &, @"}.run();
			if (prod_name.size() == 0 ) { e_name.set_text("*name*"); continue; }
			if (name_test) { e_name.set_text("Invalid characters: #, @, &, and %"); continue; }
			if (prod_memory == -1) { e_mem.set_text("Enter Whole Number"); continue; }
			if (prod_price == -1.0) { e_price.set_text("NAN"); continue; }
		
		}
	}
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
	
	c_peripheral.set_active(0);
	//Attach grid to dialog
	dialog.get_content_area()->add(grid);
	
	//Add Select and Cancel button
	dialog.add_button("_Select", Gtk::RESPONSE_OK);
	dialog.add_button("_Done", Gtk::RESPONSE_CANCEL);
	
	//Display to user
	dialog.show_all();
	int result;
	while((result = dialog.run()) == Gtk::RESPONSE_OK){
		choice.push_back(c_peripheral.get_active_row_number());
	}

	return choice;
}





/*-------------------REMOVE DIALOGS---------------------*/



void Mainwin::on_remove_customer_click(){
	on_view_customer_click();
//Create a Dialog
	Gtk::Dialog dialog{"Remove Customer", *this};
	
	//Create a 2x3 grid
	Gtk::Grid grid;
	
	//Create labels for propmts
	Gtk::Label name{"Name: "};
	Gtk::Label phone{"Phone (xxx-xxx-xxxx): "};
	
	//Attach labels to the grid 
	grid.attach(name,0,0,1,1);
	grid.attach(phone,0,1,1,1);
	
	//Make an entry to user information
	Gtk::Entry e_name;
	Gtk::Entry e_phone;
	
	//Attach the Entry's on the grid
	grid.attach(e_name,1,0,1,1);
	grid.attach(e_phone,1,1,1,1);
	
	//Now add the grid to the dialog box
	dialog.get_content_area()->add(grid);
	
	//Add an _Ok and _Cancel button
	dialog.add_button("_ok", Gtk::RESPONSE_OK);
	dialog.add_button("_Cancel",Gtk::RESPONSE_CANCEL);
	
	//show the dialog to the user
	dialog.show_all(); 
	std::string c_name, c_phone;
	int result;
	bool found = false;
	
	while(!found && (result = dialog.run()) == Gtk::RESPONSE_OK ){
		c_name = e_name.get_text();
		c_phone = e_phone.get_text();
		if( c_name == "Quit" || c_name == "quit" ) break;
		if( store->remove_customer(c_name, c_phone) ){ set_msg("Customer was deleted"); break;}
		e_name.set_text("delete unsuccessful ");
		e_phone.set_text("xxx-xxx-xxxx");
	}
	on_view_customer_click();
}


/* -----------DATA VALIDATION--------------*/

double Mainwin::get_double(std::string prompt){
    double num;
    try{
		std::regex a{"\\d+(\\.\\d+)?"};
		if(std::regex_match(prompt, a)) num = std::stod(prompt);
		else throw std::runtime_error{"NAN\n"};
    }catch(std::exception& e){
		num = -1.0;
    }
    return num;
}


int Mainwin::get_int(std::string prompt){
	
	int num;
	try{	
		std::regex a{"\\d+"};
		if(std::regex_match(prompt, a)) num = std::stoi(prompt);
		else throw std::runtime_error{"NAN\n"};
	}catch(std::exception& e){
		num = -1;
	}
	return num;
}


bool Mainwin::regex_email(std::string email){
	std::regex a{"\\w*@\\w+\\.com"};
	if( std::regex_match(email, a) ) return true;
	return false;
}


bool Mainwin::regex_phone(std::string phone){
	std::regex a{"\\+?1?\\d{3}-\\d{3}-\\d{4}"};
	if( std::regex_match(phone, a) ) return true;
	return false;
}

bool Mainwin::name_peripherals(std::string name){
	char first = name.at(0);
	if(first == '#' || first =='&' || first == '@') { return true; }
	return false;
}


/*-----------------DISPLAY------------------*/

void Mainwin::set_data(std::string s){data->set_markup(s); }
void Mainwin::set_msg(std::string s){ msg->set_markup("<b>"+s+"</b>"); } 


