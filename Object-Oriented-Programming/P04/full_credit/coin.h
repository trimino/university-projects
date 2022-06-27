/*
Created by David Trimino
Sat, Feb 15 2020
*/

#ifndef __COIN_H
#define __COIN_H

#include "logger.h"
#include <string>
#include <iostream>
#include <map>

typedef int Year;

enum Coin_size{
        PENNY,  // 0
        NICKEL, // 1
        DIME,   // 2
        QUARTER // 3
};

class Coin{
    public:
        Coin(Coin_size size, Year year);    //default constructor
        Coin(const Coin& rhs);              //copy constructor
        Coin& operator=(const Coin& rhs);   //copy assignment constructor
        ~Coin();                            //destructor 

        void add_note(std::string s);
        friend std::ostream& operator<<(std::ostream& ost, const Coin& c);
        friend std::istream& operator>>(std::istream& ist, Coin& c);

    private:
        Coin_size _size; 
        Year _year;
        std::string* _notes;
};


#endif