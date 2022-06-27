#ifndef __DESKTOP_H
#define __DESKTOP_H

#include <vector>
#include "options.h"

class Desktop{
    public:
        void add_option(Options& option);
        double price();
        friend std::ostream& operator<<(std::ostream& ost, const Desktop& desk);

    private:
        std::vector<Options*> _options;
};

#endif