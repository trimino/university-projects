#include "desktop.h"
#include <iostream>

Desktop::Desktop(){}

/*The size variable is the size of the _options vector*/
Desktop::Desktop(std::istream& ist, std::vector<Options*>& options ){
	int size;
	if(ist.eof()) size = 0;
	else{
		ist >> size;
		ist.ignore(32767, '\n');
		if(!ist) throw std::runtime_error{"Invalid type for size Options\n"};
	}
	for(int i = 0; i < size; ++i){
		int index;
		ist >> index;
		Options* ptr = options.at(index);
		_options.push_back(ptr);
	}
}

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

void Desktop::save(std::ostream& ost, std::vector<Options*>& options){
	
	std::vector<int> indexes;
	
	/*Get the index where each of the _options elements in the Store::options vector*/
	for(int i = 0; i < options.size(); ++i){
		Options* ptr_sopt = options.at(i);
		for(int j = 0; j < _options.size(); ++j){
			if( ptr_sopt == _options.at(j) ){
				indexes.push_back(i);
				break;
			}
		}
	}
	
	ost << indexes.size() << std::endl;
	for(int i : indexes)
		ost << i << std::endl;
}
