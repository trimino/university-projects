#ifndef __OPTIONS_H
#define __OPTIONS_H

#include <string>
#include <iostream>
#include <fstream>

class Options{
    public:
        Options(std::string name, double cost);
        Options(std::istream& ist);
        ~Options();
        double cost();
        friend std::ostream& operator<<(std::ostream& ost, const Options& opt);
        
        virtual std::string get_name();
        virtual Options* clone();
        virtual std::string to_string() const;
        virtual void save(std::ostream& ost);

    protected:
        std::string _name;
        double _cost;
};

#endif
