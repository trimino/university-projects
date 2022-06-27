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
	friend std::ostream& operator<<(std::ostream& ost, const Color color);
	friend std::istream& operator>>(std::istream& ist, Color& color);
	
	inline bool operator==(const Color& rhs) {return (compare(rhs) == 0);}
	inline bool operator!=(const Color& rhs) {return (compare(rhs) != 0);}
	inline bool operator>=(const Color& rhs) {return (compare(rhs) >= 0);}
	inline bool operator<=(const Color& rhs) {return (compare(rhs) <= 0);}
	inline bool operator>(const Color& rhs)  {return (compare(rhs)  > 0);}
	inline bool operator<(const Color& rhs)	 {return (compare(rhs)  < 0);}
	
	

     private:
	int _red;
	int _green;
	int _blue;
	bool _reset;
	int compare(const Color& rhs);
};
#endif
