#include "color.h"
#include <iostream>



int main(){

	Color c1{234,56,32};
	Color c2{234,23,244};
	Color c3{234,22,2};
	
	std::string mag_one = std::to_string(c1.magnitude());
	std::string mag_two = std::to_string(c2.magnitude());
	std::string mag_three = 			std::to_string(c3.magnitude());


	std::cout<<c1.colorize("trimino")<<" "		  <<c1.colorize(mag_one) <<"  ";

	std::cout<<c2.colorize("COLOR")<<" "
<<c2.colorize(mag_two) <<"  ";

	std::cout<<c3.colorize("UTACOLOR")<<" "
<<c3.colorize(mag_three);	

	std::cout << std::endl;


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
