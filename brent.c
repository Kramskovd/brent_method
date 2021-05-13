#include "brent.h"

void brent(func_t f, double a, double b, double e, int N, int tr, res_t *res){
    double x, r, w, v, u, dcur, dprv, g;
    double fx, fw, fv, fu, df1, df2, dx1, dx2;

    double dm;

    res->n = 0;
    r = (3-sqrt(5))/2;
    x = w = v = a + r*(b-a);
    dcur = dprv = b - a;
    
    if(tr == 1){
        printtable();
    }

    while( res->n < N){
        if(tr == 1)
            printtr(res->n, x, b-a, fabs(f(b)-f(a)) );
        
        if(fmax(x-a, b-x) < e){   
            res->st = 0;
            res->x = x;
            res->fx = f(x);
            return;
        }

        g = dprv / 2; 
        dprv = dcur;
        
        fx = f(x);
        fw = f(w);
        fv = f(v);

        dx1 = w - x;
        dx2 = w - v;
        df1 = fw - fx;
        df2 = fw - fv;

        dm = dx1*df2 - dx2*df1;
        if(fabs(dm) >0 ){
            u = w - (dx1*dx1*df2 - dx2*dx2*df1)*0.5/dm;
        }

        if(!(fabs(dm) > 0) || (u < a || u > b) || fabs(u-x) > g){
            if(x < (a+b)/2){
                u = x + r*(b-x);
                dprv = b - x;
            }else{
                u = x - r*(x - a);
                dprv = x - a;
            }
            res->gn++;
        }else
            res->pn++;
        
        dcur = fabs(u-x);
        fu = f(u);

        if(fu > fx){
            if(u < x)
                a = u;
            else 
                b = u;
            
            if(fu <= fw || w == x){
                v = w;
                w = u;
            }else{
                if(fu <= fv || v == x || v == w)
                    v = u;
            }
        }else{
            if(u < x)
                b = x;
            else
                a = x;
            
            v = w;
            w = x;
            x = u;
        }
        res->n++;
    }
    res->st = -2;
}

void printtable(void){
    printf("%3c %1c %12s %11c %11s %11c %12s\n", 'n', '|', "xm", '|', "dx", '|', "df");
}

void printtr(int n, double xm, double dx,double df){
    printf("%3d | %21.14e  | %21.14e | %21.14e\n", n, xm, dx, df);
}