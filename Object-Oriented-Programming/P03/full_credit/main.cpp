#include "color.h"
#include <iostream>


int main(){

	Color red{255,0,2};
	Color green{0,255,2};
	Color purple{255,0,255};
	Color reset{};
	std::cout << green << "GREEN\t" << red << "RED\t" << purple << "PURPLE" 
		  << reset <<std::endl;

	Color color;	//default constructor called
	std::cout << "Enter color as (red,green,blue): ";
	std::cin >> color;
	std::cout << color << color.to_string() << std::endl;
	return 0;

}
