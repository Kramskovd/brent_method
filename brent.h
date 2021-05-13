#ifndef _BRENT_H_
#define _BRENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.7182818284590452354
#endif

#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif

typedef struct{
    int st;
    double x;
    double fx;
    int n;
    int pn;
    int gn;
} res_t;

typedef double(*func_t)(double);
void print (res_t res);
void printtable(void);
void printtr(void);
void brent(func_t f, double a, double b, double e, int N, int tr, res_t *p);
void golden(func_t f, double a, double b, double e, int N, int tr, res_t *p);
void printerr (const char *s);
int toInt(const char *str, int *res);
int toDouble(const char *str, double *res);

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);
double f6(double x);
double f7(double x);
double f8(double x);
double f9(double x);
double f10(double x);
double f11(double x);
double f12(double x);
double f13(double x);
double f14(double x);
double f15(double x);
double f16(double x);
double g(double x);

#endif