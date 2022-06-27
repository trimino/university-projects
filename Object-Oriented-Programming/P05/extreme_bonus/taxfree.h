#ifndef __TAXFREE_H
#define __TAXFREE_H
#include "product.h"


class Taxfree: public Product{
    public:
        Taxfree(std::string name, double cost);
        virtual ~Taxfree();
        virtual double price()const override;
        virtual Product* clone() override;
};

#endif