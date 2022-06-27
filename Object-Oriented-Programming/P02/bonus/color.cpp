#include "color.h"
#include <iostream>

Color::Color (int red, int green, int blue): _red{red}, _green{green}, _blue{blue}{
	//constructor made and initialized private var
}



std::string Color::to_string(){
	//(red,green,blue:magnitude) magnitude
	return "("   +std::to_string(_red)+"," 			     +std::to_string(_green)+","
		     +std::to_string(_blue) +":"
		     +std::to_string(magnitude())+
		") "
		+std::to_string(magnitude());	
}


int Color::magnitude()const{
   return round((_red*0.21) + (_green*0.72) + (_blue*0.07));
}

int Color::compare(const Color& rhs){
	if(this->magnitude() > rhs.magnitude()){
		return 1;
	}
	else if (this->magnitude() < rhs.magnitude()){
		return -1;
	}
	else{
		return 0;
	}
}


std::string Color::colorize(std::string text){
	//"\033[38;2;red;green;bluemtext\033[0m"

	return "\033[38;2;"+std::to_string(_red)+";"
			   +std::to_string(_green)+";"
			   +std::to_string(_blue)+"m"
			   +text
			   +"\033[0m";
}





