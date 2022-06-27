#include "color.h"
#include <iostream>
#include <random>
#include <ctime>


void print_background();
void add_sub();
void add_sub_int();
void pre_post_inc();
void pre_post_dec();



int main(){
	
	print_background();
	add_sub();
	add_sub_int();
	pre_post_inc();
	pre_post_dec();	
	return 0;

}

//use post and pre decrement on Color object 
void pre_post_dec(){
	Color reset;
	Color x{0,10,2};
	Color a;
	a = --x;
	std::cout << "**Pre-Decrement**\n";
	std::cout << a << "a = " << a.to_string() << std::endl;
	std::cout << x << "x = " << x.to_string() << std::endl;
	std::cout << reset << std::endl;
	
	Color z{255,254,0};
	Color b;
	b = z--;
	std::cout << "**Post-Decrement**\n";
	std::cout << b << "b = " << b.to_string() << std::endl;
	std::cout << z << "z = " << z.to_string() << std::endl;
	std::cout << reset << std::endl;
}

//use post and pre increment on Color object 
void pre_post_inc(){
	Color reset;
	Color x{255,254,100};
	Color a;
	a = ++x;
	std::cout << "**Pre-Increment**\n";
	std::cout << a << "a = " << a.to_string() << std::endl;
	std::cout << x << "x = " << x.to_string() << std::endl; 
	std::cout << reset << std::endl;

	Color z{254,12,33};
	Color b;
	b = z++;
	std::cout << "***Post-Increment**\n";
	std::cout << b << "b = " << b.to_string() << std::endl;
	std::cout << z << "z = " << z.to_string() << std::endl;
	std::cout << reset << std::endl;
}

//add and subtract a color object with an integer  
void add_sub_int(){
	Color c{202,22,102};
	Color d = d + 150;
	std::cout << d << "ADD INTEGER: " << d.to_string() << std::endl;
	Color e = c - 122;
	std:: cout << e << "SUBTRACT INTEGER: " << e.to_string() << std::endl;
}

//add and subtract two color objects together
void add_sub(){
	Color a{200,230,10};
	Color b{255,23,4};	
	Color add = a + b;
	Color sub = a - b;
		
	std::cout << add << "ADDITION OF RED + BLUE = " << add.to_string() << '\n';
	std::cout << sub << "SUBTRACT OF RED - BLUE = " << sub.to_string() << '\n';
}


//prints background color of text
void print_background(){

	std::mt19937 generator;
	generator.seed(std::time(0));
	std::uniform_int_distribution<uint32_t> ran_num(0,255);
	std::vector<Color> background;
	int red,gre,blu,ran;
	for(int i = 0; i<213; ++i){
		ran = ran_num(generator);
		red = ran;
		ran = ran_num(generator);
		gre = ran_num(generator);
		ran = ran_num(generator);
		blu = ran;
		Color c{red,gre,blu,true};	
		background.push_back(c);
	}
	

	Color r{255,0,0};
	Color g{0,255,0};
	Color b{0,0,255};
	Color reset;	
	for(auto a : background){
		std::cout << r << a << r.to_string() << std::endl;
		std::cout << g << a << g.to_string() << std::endl;
		std::cout << b << a << b.to_string() << std::endl;	
		std::cout << reset << "RESET CALLED";
		
	}
	std::cout << '\n' << std::endl;

}

