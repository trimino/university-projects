#include "desktop.h"
#include <iostream>

void Desktop::add_option(Options& option){
  _options.push_back(&option);
}

double Desktop::price(){
    double sum = 0.0;
    if (!_options.empty()){
        for(Options* opt : _options){
            sum += opt->cost();
        }
    }
    return sum;
}

std::ostream& operator<<(std::ostream& ost, const Desktop& desk){
    ost << "Desktop Includes: \n";
    for (Options* ptr_opt : desk._options)
        ost << '\t' << *(ptr_opt) << '\n';
    return ost;
}
