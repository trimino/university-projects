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

		const static Color RED;
		const static Color BLUE;
		const static Color GREEN;
		const static Color PURPLE;

		Color(int red, int green, int blue);
		Color(int red, int green, int blue, bool background);
		Color();

		std::string to_string();
		int magnitude() const;

		friend std::ostream& operator<<(std::ostream& ost, const Color color);
		friend std::istream& operator>>(std::istream& ist, Color& color);
		friend Color operator+(const Color& lhs, const Color& rhs);
		friend Color operator-(const Color& lhs, const Color& rhs);
		friend Color operator*(const Color& lhs, const Color& rhs);
		friend Color operator/(const Color& lhs, const Color& rhs);
		
		
		inline bool operator==(const Color& rhs) {return (compare(rhs) == 0);}
		inline bool operator!=(const Color& rhs) {return (compare(rhs) != 0);}
		inline bool operator>=(const Color& rhs) {return (compare(rhs) >= 0);}
		inline bool operator<=(const Color& rhs) {return (compare(rhs) <= 0);}
		inline bool operator>(const Color& rhs)  {return (compare(rhs)  > 0);}
		inline bool operator<(const Color& rhs)	 {return (compare(rhs)  < 0);}

		Color operator+(int num);
		Color operator-(int num);

		Color& operator++();
		Color& operator--();

		Color operator++(int p);
		Color operator--(int p);

		
		Color& operator*=(const Color& rhs);
		Color& operator/=(const Color& rhs);


     private:
		int _red;
		int _green;
		int _blue;
		bool _reset;
		bool _background;
		int compare(const Color& rhs);
	};

#endif
