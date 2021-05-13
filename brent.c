#include "brent.h"


void golden(func_t f, double a, double b, double e, int N, int tr, res_t *p){
    int i;
    double r;
    double ai, bi, c, d, l, fc, fd;
    
    i = 0;

    if(tr == 1)
        printf("1\n");
    
    ai = a;
    bi = b;
    l = bi - ai;
    r = (3-sqrt(5))/2;
    c = ai + r*l;
    d = bi - r*l; 
        
    fc = f(c);
    fd = f(d);

    while(i <= N){
       

        if(l < 2*e){
            (*p).st = 0;
            p->x = (ai + bi)/2;
            p->fx = f(p->x);
            p->n = i;
            p->pn = i;
            p->gn = 0;
            return;
        }

        if(!(ai < c && c < d && d < bi)){
            (*p).st = -2;
            p->x = (ai + bi)/2;
            p->fx = f(p->x);
            p->n = i;
            p->pn = i;
            p->gn = 0;
            return;
        }

        if(fc < fd){
            bi = d;
            d = c;
            l = bi - ai;
            c = ai + r*l;
            fd = fc;
            fc = f(c);
        }else{
            ai = c;
            c = d;
            l = bi - ai;
            d = bi - r*l; 
            fc = fd;
            fd = f(d);

        }
        i++;
        
    }
    (*p).st = -1;
    p->x = (ai + bi)/2;
    p->fx = f(p->x);
    p->n = i;
    p->pn = i;
    p->gn = 0;

}

void printtable(void){
    printf("%3c %1c %12s %12c %12s %12c %12s\n", 'n', '|', "xm", '|', "dx", '|', "df");
}

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
