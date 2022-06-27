#ifndef __TAX_H
#define __TAX_H
#include "product.h"

class Taxed : public Product{
    public:
        Taxed(std::string name, double cost);
        virtual double price() const override;
        virtual ~Taxed();
        static void set_tax_rate(double tax);
    private:
		static double _tax;
};

#endif
