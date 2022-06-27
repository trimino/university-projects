#ifndef __DISK_H
#define __DISK_H

#include "options.h"
#include <iostream>


class Disk: public Options{
	public:
		Disk(std::string name, double cost, int gb);
		Disk(std::istream& ist);
		~Disk();
		
		std::string get_name();
		std::string to_string() const override; 
		Disk* clone() override;
		void save(std::ostream& ost) override;
		
	protected:
		int _tb;
};

#endif
