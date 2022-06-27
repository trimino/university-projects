#include "color.h"
#include <iostream>
#include <random>
#include <ctime>

int main(){
	std::mt19937 generator;
	generator.seed(std::time(0));
	std::uniform_int_distribution<uint32_t> ran_num(0,255);
	std::vector<Color>colors;
	int ran;
	for(int i =0; i<64;i++){
		ran = ran_num(generator);
		int red = ran;
		ran = ran_num(generator);
		int blue = ran;
		ran = ran_num(generator);
		int green = ran_num(generator);	
		Color color{red,green,blue};
		colors.push_back(color);
	}
	sort(colors.begin(),colors.end());
	for(auto c : colors)
		std::cout << c << c.to_string() << std::endl;
	return 0;

}
