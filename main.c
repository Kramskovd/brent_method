#include "brent.h"

void printerr(const char *s){
    printf("Usage: %s fn a b e N [trace]\n", s);
    printf("1.  x(x-2)\n");
    printf("2.  |f1(x)|\n");
    printf("3.  g(f1(x))\n");
    printf("4.  |x^3|\n");
    printf("5.  x(x-2)(x-3)\n");
    printf("6.  |f5(x)|\n");
    printf("7.  g(f5(x))\n");
    printf("8.  |sin(x^2)|\n");
    printf("9.  g(sin(x^2))\n");
    printf("10. |e^(0.1x) * sin(x)|\n");
    printf("11. g(e^(0.1x) * sin(x))\n");
    printf("12. -x^5 + 4x^4 - 12x^3 + 11x^2 - 2x + 1\n");
    printf("13. -ln^2(x-2) + ln^2(10-x) - x^0.2\n");
    printf("14. -3x*sin(0.75x) + e^(-2x)");
    printf("15. e^(3x) + 5e^(-2x)\n");
    printf("16. 0.2x*ln(x) + (x - 2.3)^2\n");
    printf("g(x) = x if x > 0 else 0 \n");
}

int main(int argc, char* argv[]){
    int fn, N;
    double a, b, e;

    func_t fs[] = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16};
    int trace = 0;
    res_t res;

    if(argc != 6 && argc != 7){
        printf("Incorrect data input\n");
        printerr(argv[0]);
        return -1;
    }

    if(toInt(argv[1], &fn) == -1 || fn < 1 || fn > 16){
        printf("Status: -1\nIncorrect fn\n");
        return -1;
    }

    if(toDouble(argv[2], &a) == -1){
        printf("Status: -1\nIncorrect a\n");
        return -1;
    }

    if(toDouble(argv[3], &b) == -1){
        printf("Status: -1\nIncorrect b\n");
        return -1;
    }

    if(b < a){
        printf("Status: -1\nIncorrect data: a > b\n");
        return -1;
    }

    if(toDouble(argv[4], &e) == -1 || e <= 0){
        printf("Status: -1\nIncorrect e\n");
        return -1;
    }
    if(toInt(argv[5], &N) == -1){
        printf("Status: -1\nIncorrect N\n");
        return -1;
    }
    if(argc == 7 && strcmp(argv[6], "trace") == 0){
        trace = 1;
    }else{
        printf("Status: -1\nIncorrect 'trace'\n");
        return -1;
    }

    brent(fs[fn-1], a, b, e, N, trace, &res);
    print(res);
}

void print(res_t res){
    printf("status                  : %d\n", res.st);
    printf("xmin                    : %e\n",res.x);
    printf("f(xmin)                 : %e\n",res.fx);
    printf("n                       : %d\n", res.n);
    printf("pn                      : %d\n", res.pn);
    printf("gn                      : %d\n", res.gn);
    printf("|xmin - sqrt(Pi)|       : %e\n", fabs(res.x - sqrt(M_PI)));
    printf("|xmin - sqrt(2*Pi)|     : %e\n", fabs(res.x - sqrt(2*M_PI)));
    printf("|xmin - Pi|             : %e\n", fabs(res.x - M_PI));
    printf("|xmin - 2*Pi|           : %e\n", fabs(res.x - 2*M_PI));
}

int toInt(const char *str, int *res){
    long l;
    char *e;

    errno = 0;
    l = strtol(str, &e, 10);

    if(!errno && *e == '\0'){
        if(INT_MIN <= l && l <= INT_MAX){
            *res = (int)l;
            return 0;
        }
    }

    return -1;
}

int toDouble(const char *str, double *res){
    double d;
    char *e;

    errno = 0;
    d = strtod(str, &e);

    if(!errno && *e == '\0'){
        *res = d;
        return 0;       
    }

    return -1;
}


