#ifndef __RAM_H
#define __RAM_H

#include "options.h"
#include <iostream>


class Ram: public Options{
	public:
		Ram(std::string name, double cost, int gb);
		Ram(std::istream& ist);
		~Ram();
		
		std::string get_name() override;
		std::string to_string() const override; //does not hurt to put virtual but is helpful
		Ram* clone() override;
		void save(std::ostream& ost) override;
		
	protected:
		int _gb;
};

#endif
