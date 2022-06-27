#include "taxed.h"
#include "taxfree.h"
#include <iostream>
using namespace std;


int main(){
    /*
    instance a Taxfree and Taxed product, and verify that each of its attributes
    (both inherited and local) were properly constructed and that 
    operator<< (Product's friend) works with it.
    */

    Taxfree non_tax{"Bannana", 5.99};
    non_tax.set_quantity(2);
    if (non_tax.price() != 11.98){
        cerr << "###ERROR ### incorrect value for non_tax price\n";
        cerr << non_tax;
    }
    
    Taxed::set_tax_rate(0.0825);
    Taxed taxed{"Shiner Bock", 6.89};
    taxed.set_quantity(1);   
    if (taxed.price() != 7.46){
         cerr << "###ERROR ### incorrect value for tax price\n";
         cerr << taxed << endl;
         cerr << taxed.price();
    }
    

}