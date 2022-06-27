#ifndef __CPU_H
#define __CPU_H

#include "options.h"
#include <iostream>


class CPU: public Options{
	public:
		CPU(std::string name, double cost, int gb);
		CPU(std::istream& ist);
		~CPU();
		
		std::string get_name() override;
		std::string to_string() const override; //does not hurt to put virtual but is helpful
		CPU* clone() override;
		void save(std::ostream& ost) override;
		
	protected:
		int _freq;
};

#endif

