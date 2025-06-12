#include <stdio.h>
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);
double test1(double x);
double test2(double x);
double test3(double x);


typedef double afunc(double);
static long long unsigned iterations;

static double F(afunc *f, afunc *g, double x) {
    return f(x) - g(x);
}

double root(afunc *f, afunc *g, double a, double b, double eps1) {
    double Fa = F(f, g, a);
    double Fb = F(f, g, b);
    double c, Fc;
    
    iterations = 0;	
    int positive = 0;
	int increasing = 0;
	int upper = 0;

    if (Fa < 0){
      	increasing = 1;
   	}
   	if (F(f, g, (a+b)/2) > (F(f, g, a) + F(f, g, b)/2)){
      	upper = 1;
   	}
   	if ((upper == !increasing)) {
      	positive = 1;
   	}

    while(1) {
        c = (a * Fb - b * Fa) / (Fb - Fa);
        Fc = F(f, g, c);

        if (positive) {
            double temp = F(f, g, c+eps1);
            if (Fc*temp < 0) break;
            if (Fc * Fa < 0) b = c; else a = c;
        } 
        else {
            double temp = F(f, g, c-eps1);
            if (Fc*temp < 0) break;
            if (Fc * Fb < 0) a = c; else b = c;
        }
        
        Fa = F(f, g, a);
        Fb = F(f, g, b);
        
    }

    return c;

}

double integral(afunc *f, double a, double b, double eps2);


double f(double x) { return x*x -4; }
double g(double x) { return 0; }

int main() {
    double x = root(f, g, 0.0, 3.0, 1e-6);
    printf("Корень: %.6f\n", x);
    return 0;
}