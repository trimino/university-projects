#ifndef __COLOR_H
#define __COLOR_H
#include <string>
#include <cmath> 
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>

class Color{
     public:
	Color(int red, int green, int blue);
	Color();
	std::string to_string();
	int magnitude() const;
	int compare(const Color& rhs);
	friend std::ostream& operator<<(std::ostream& ost, const Color color);
	friend std::istream& operator>>(std::istream& ist, Color& color);

     private:
	int _red;
	int _green;
	int _blue;
	bool _reset;
};
#endif
