#include "color.h"
#include <iostream>

Color::Color (int red, int green, int blue): _red{red}, _green{green}, _blue{blue}{
	//constructor made and initialized private var
}



std::string Color::to_string(){
	return "(" + std::to_string(_red)+" " 			     +std::to_string(_green)+" "
		     +std::to_string(_blue) +
		")";	
}


std::string Color::colorize(std::string text){
	//"\033[38;2;red;green;bluemtext\033[0m"

	return "\033[38;2;"+std::to_string(_red)+";"
			   +std::to_string(_green)+";"
			   +std::to_string(_blue)+"m"
			   +text
			   +"\033[0m";
}





