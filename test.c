#include "brent.h"

double g(double x){
    if(x > 0)
        return x;
    else 
        return 0;
}

double f1(double x){
    return x*(x-2);
}

double f2(double x){
    return fabs(x*(x-2));
}

double f3(double x){
    return g(x*(x-2));
}

double f4(double x){
    return fabs(x*x*x);
}

double f5(double x){
    return x*(x-2)*(x-3);
}
double f6(double x){
    return fabs(x*(x-2)*(x-3));
}
double f7(double x){
    double res = x*(x-2)*(x-3);

    return g(res);

}
double f8(double x){
    return fabs(sin(x*x));
}
double f9(double x){
    return g(sin(x*x));
}

double f10(double x){
    return fabs(exp(0.1*x)*sin(x));
}
double f11(double x){
    return g(exp(0.1*x)*sin(x));
}
double f12(double x){
    double res;
    double px;
    px = x*x;
    res = 1 - 2*x + 11*px;
    px *= x;
    res += -12*px;
    px *= x;
    res += 4*px - 5*px*x;

    return res;
}

double f13(double x){
    return -pow(log(x-2), 2) + pow(log(10-x), 2) - pow(x, 0.2);
}

double f14(double x){
    return -3*x*sin(0.75*x) + exp(-2*x);
}

double f15(double x){
    return exp(3*x) + 5*exp(-2*x);
}

double f16(double x){
    return 0.2*x*log(x) + pow(x-2.3, 2);
}