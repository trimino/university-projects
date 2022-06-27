#include "color.h"
#include <iostream>


Color::Color (int red, int green, int blue): _red{red}, _green{green}, _blue{blue}, _reset{false}{/*body of constructor wiht color arguments*/}


//when given no parameters the complier will call this function to make _reset=true
Color::Color():_reset{true}{/*body of reset ANSI code constructor*/}


//returns a string with the format of (red,green,blue:magnitude) magnitude
std::string Color::to_string(){
	return "("   +std::to_string(_red)+","
		     +std::to_string(_green)+","
		     +std::to_string(_blue) +":"
		     +std::to_string(magnitude())+
		") "
		     +std::to_string(magnitude());	
}


//calculates the maginitude of the color (21% red, 72% green, 7% blue)
int Color::magnitude()const{
   return static_cast <int>(
		0.21 * (double)_red 
		+ 0.72 * (double)_green
		+ 0.07 * (double)_blue
   );
}


//compares the magnitude's of each Color object 
int Color::compare(const Color& rhs){
	if(magnitude() > rhs.magnitude()) return 1;
	if(magnitude() < rhs.magnitude()) return -1;
	return 0;
}



//will stream out ANSI escape codes if reset is false else it will stream default
std::ostream& operator<<(std::ostream& ost, const Color color){

	if(color._reset == false){
		ost << "\033[38;2;"
				+std::to_string(color._red)  +";"	
				+std::to_string(color._green)+";"
				+std::to_string(color._blue) +"m";
	}
	else {
	    ost << "\033[0m";
	}

	return ost;
	
}



//will read a color using the (red,green,blue) format.
//first int is red, second is green, and third is blue
std::istream& operator>>(std::istream& ist, Color& color){	
	
	int tmp;
	std::string str,temp;
	getline(ist,str);

	std::stringstream ss(str);
	std::vector<int> colors;
	while(std::getline(ss,temp,',')){

		size_t found_front = temp.find('(');
		size_t found_back = temp.find(')');

		if(found_front != std::string::npos){
		     temp = temp.substr(found_front+1,temp.length());	
		}else if (found_back != std::string::npos){
		     temp = temp.substr(0,found_back);		
		}
		colors.push_back(stoi(temp));
	}
	
	color = Color{colors.at(0),colors.at(1),colors.at(2)};
	return ist;
}





