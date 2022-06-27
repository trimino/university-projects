
/*
Created by David Trimino on Feb 15 2020
UTA - CSE1325

A copy constructor is used to initialize a previously uninitialized object from some 
    other object's data.

An assignment operator is used to replace the data of a previously initialized object with some 
    other object's data.
*/

#include "coin.h"

const std::map<Coin_size,std::string> translate ={
    {PENNY, "penny"}, {NICKEL, "nickel" },
    {DIME , "dime" }, {QUARTER, "quarter"}
};

const std::map<std::string,Coin_size> reverse_trans ={
    {"penny" ,PENNY},
    {"nickel",NICKEL},
    {"dime"  ,DIME},
    {"quarter", QUARTER}
};


//empty constructor 
Coin::Coin(): _size{Coin_size::PENNY}, _year{1752}, _notes{nullptr}{};

//class contructor 
Coin::Coin(Coin_size size, Year year): _size{size}, _year{year}, _notes{nullptr}{
    LOG("Coin::Coin");
} 

//copy constructor 
Coin::Coin(const Coin& rhs): _year{rhs._year},_size{rhs._size},
  _notes{new std::string{*rhs._notes}}{
      LOG("Coin::Coin Copy Constructor");
  }

//copy assignment constructor 
Coin& Coin::operator=(const Coin& rhs){
    LOG("Coin::operator=");
    if (this == &rhs) {return *this;}
    
    _year = rhs._year;
    _size = rhs._size;  
    _notes = new std::string{*rhs._notes};
    return *this;    
}

//destructor
Coin::~Coin(){
    LOG("Coin::~Coin");
    delete[] _notes;
}

void Coin::add_note(std::string s){
    if (!_notes){
        _notes = new std::string[s.length()];
        *_notes = s;
    }else{    
        std::string strng = *(_notes) + s;
        _notes = new std::string[strng.length()];
        *_notes = strng;
    }   
}

std::ostream& operator<<(std::ostream& ost, const Coin& c){
    if (translate.count(c._size)){
        ost << c._year << " " << translate.at(c._size) << '\n' << *(c._notes);
    }else{
        throw std::runtime_error{"Unexpected value for size"};
    }
    return ost;   
}

std::istream& operator>>(std::istream& ist, Coin& c){
    std::string siz;
    std::string note;
    int year;

    ist >> year;
    ist >> siz;
    ist.ignore(); //ignore the newline
    getline(ist,note);

    std::transform(siz.begin(),siz.end(),siz.begin(), ::tolower);
    year < 1752 ? throw std::runtime_error{"First coin was made in 1752"} : c._year = year;
    reverse_trans.count(siz) == 0 ? throw std::out_of_range{"Size not found"} : c._size = reverse_trans.at(siz);

    c._notes = new std::string[note.length()];
    *c._notes = note;   
    return ist;
}





