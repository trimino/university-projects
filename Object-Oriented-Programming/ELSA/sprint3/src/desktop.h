#ifndef __DESKTOP_H
#define __DESKTOP_H

#include <vector>
#include "options.h"

class Desktop{
    public:
		Desktop();
		Desktop(std::istream& ist, std::vector<Options*>& options);
        void add_option(Options& option);
        double price();
        friend std::ostream& operator<<(std::ostream& ost, const Desktop& desk);
		void save(std::ostream& ost, std::vector<Options*>& options);
		
    private:
        std::vector<Options*> _options;
};

#endif
