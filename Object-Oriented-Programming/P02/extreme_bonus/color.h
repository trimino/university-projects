#ifndef __COLOR_H
#define __COLOR_H
#include <string>
#include <cmath> 
#include <vector>
#include <algorithm>

class Color{
     public:
	Color(int red, int green, int blue);
	std::string to_string();
	std::string colorize(std::string text);
	int magnitude() const;
	int compare(const Color& rhs);

     private:
	int _red;
	int _green;
	int _blue;
};

#endif
