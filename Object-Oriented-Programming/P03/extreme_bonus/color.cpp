#include "color.h"
#include <iostream>


const Color Color::RED{255,0,0};
const Color Color::BLUE{0,0,255};
const Color Color::PURPLE{255,0,255};
const Color Color::GREEN{0,255,0};

Color::Color (int red, int green, int blue): _red{red}, _green{green}, _blue{blue}, _reset{false}, _background{false}{/*body of constructor with color arguments*/}

Color::Color(int red, int green, int blue, bool back):_red{red}, _green{green}, _blue{blue}, _background{back}, _reset{false}{/*body of background constructor*/}

Color::Color():_reset{true}, _background{false}{/*body of reset ANSI code constructor*/}


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
		ost << "\033[" << (color._background==false ? "38":"48") << ";2;"
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

//add two color objects together. If any of the colors (red,green,blue) are > 255 then set sum to 0
Color operator+(const Color& lhs, const Color& rhs){
	int r = (lhs._red+rhs._red     > 255)? 0 : lhs._red+rhs._red;
	int g = (lhs._green+rhs._green > 255)? 0 : lhs._green+rhs._green;
	int b = (lhs._blue+rhs._blue   > 255)? 0 : lhs._blue + rhs._blue;
	Color c{r,g,b};
	return c;
}

//subtract two color objects together. If any of the colors (red,green,blue) are < 0 then reset to 255
Color operator-(const Color& lhs, const Color& rhs){
	int r = (lhs._red-rhs._red     < 0) ? 255 : lhs._red - rhs._red;
	int g = (lhs._green-rhs._green < 0) ? 255 : lhs._green - rhs._green;
	int b = (lhs._blue-rhs._blue   < 0) ? 255 : lhs._blue - rhs._blue;	
	Color c{r,g,b};
	return c;
}

//supports lightening colors by adding the same num to each color(red,green,blue)
Color Color::operator+(int num){
	int r = this->_red + num;
	int g = this->_green + num;
	int b = this->_blue + num;
	Color c{
		(r>255) ? 0 : r, 
		(g>255) ? 0 : g, 
		(b>255) ? 0 : b
	};
	return c;
}


//supports darkening colors by subtracting the same num to each color(red,green,blue)
Color Color::operator-(int num){
	int r = this->_red - num;
	int g = this->_green - num;
	int b = this->_blue - num;
	Color c{
		(r<0) ? 255 : r, 
		(g<0) ? 255 : g, 
		(b<0) ? 255 : b
	};
	return c;
}

//pre-increment operator 
Color& Color::operator++(){
	(_red == 255)  ? _red = 0 : ++_red;
	(_blue == 255) ? _blue=0  : ++_blue;
	(_green == 255)?_green=0  : ++_green;
	return *this;
}

//pre-decrement operator
Color& Color::operator--(){
	(_red == 0)  ? _red = 255 : --_red;
	(_blue == 0) ? _blue=255  : --_blue;
	(_green == 0)?_green=255  : --_green;
	return *this;
}


//post increment
Color Color::operator++(int p){
	Color c{this->_red, this->_green, this->_blue};
	++(*this);
	return c;
}

//post decrement
Color Color::operator--(int p){
	Color c{this->_red, this->_green, this->_blue};
	--(*this);
	return c;
}



//blending and unblending

Color operator*(const Color& lhs, const Color& rhs) {
    return Color{(lhs._red   + rhs._red)/2,
                 (lhs._green + rhs._green)/2,
                 (lhs._blue  + rhs._blue)/2};
}

Color operator/(const Color& lhs, const Color& rhs) {
    return Color{2*lhs._red   - rhs._red,
                 2*lhs._green - rhs._green,
                 2*lhs._blue  + rhs._blue};
}

Color& Color::operator*=(const Color& rhs) {
    _red   = (_red   + rhs._red)/2;
    _green = (_green + rhs._green)/2;
    _blue  = (_blue  + rhs._blue)/2;
    return *this;
}

Color& Color::operator/=(const Color& rhs) {
    _red   = 2*_red   - rhs._red;
    _green = 2*_green + rhs._green;
    _blue  = 2*_blue  + rhs._blue;
    return *this;
}





