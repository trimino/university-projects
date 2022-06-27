#include<iostream>

int main(){

   std::string name="";

   //lets ask the user for their name
   std::cout << "Enter your name: ";

   //enter input in name variable (>> extraction operator)
   getline(std::cin,name);

   //print Hello {name}
   std::cout << "Hello " << (name.empty() ? "":name) << std::endl;
}
