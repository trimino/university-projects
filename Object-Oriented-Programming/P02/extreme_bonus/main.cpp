#include "color.h"
#include <iostream>


int main(){
	
	//three instances 
	Color c1{93,23,37};
	Color c2{0,100,177};
	Color c3{245,128,38};
	
	//create a vector<Color> and store instaces of Color
	std::vector<Color>colors{c1,c2,c3};
	
	//create a lambda expression for comparing
	auto dimmest = [](auto lhs, auto rhs)->bool{
		
		if (lhs.compare(rhs))
			return false;
		else
			return true; 
	};

	//lets sort colors using Color::compare as criteria
	std::sort(colors.begin(),colors.end(),dimmest);
	
	//print contents of colors
	for(Color c:colors){
		std::string text = c.to_string();
		std::cout<<c.colorize(text)<<'\n';
	}
	return 0;

}
