#ifndef INTEGRATOR_H
#define INTEGRATOR_H 

#include <QPair>
#include <math.h>

class Integrator
{
     double evaluate(QPair<double> interval){
         return sin(interval.first) * (interval.second - interval.first);
     }

     double sum(double )

public:
    Integrator();
};

#endif // INTEGRATOR_H
