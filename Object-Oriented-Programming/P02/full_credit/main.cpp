#include "color.h"
#include <iostream>


int main(){

	Color c1{255,0,0};
	Color c2{0,255,0};
	Color c3{177,233,9};

	std::cout<<c1.colorize("UTA")<<"  ";
	std::cout<<c2.colorize("HELLO")<<" ";
	std::cout<<c3.colorize("EXAMPLE")<<'\n';
	
	int red,green,blue;
	std::cout << "Enter red, green, and blue ints: ";
	std::cin >> red; 
	std::cin >> green;
	std::cin >> blue;
	
	Color color{red,green,blue};
	std::string text = color.to_string();
	std::cout << color.colorize(text) << std::endl;
	return 0;

}
