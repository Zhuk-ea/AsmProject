#include <stdio.h>
#include <math.h>
#include <string.h>

double f1(double x);
double f2(double x);
double f3(double x);
double test1(double x);
double test2(double x);
double test3(double x);

/*
./program --test-root 1:2:-5.0:5.0:0.0001:1.34365
./program --test-root 1:3:-4.0:2.0:0.0001:-1.307861
./program --test-root 2:3:-2.0:1.0:0.0001:0.82622

./program --test-integral 1:0.0:1.0:0.0001:4.14159265
./program --test-integral 2:0.0:2.0:0.0001:4.0

*/

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
   	if (F(f, g, (a+b)/2) > ((F(f, g, a) + F(f, g, b))/2)){
      	upper = 1;
   	}
   	if ((upper != increasing)) {
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
        if (iterations > 100000) {
            break;
        }
        ++iterations;
        
    }

    return c;

}

double integral(afunc *f, double a, double b, double eps2) {
    int n = 10;
    int iter = 0;
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
     for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
   	double I = sum * h;
   	double I_n = 0;
   	double eps0 = INFINITY;

   	while(eps0 > eps2 && iter < 1000){
      	n *= 2;
        h = (b - a) / n;
        double temp = 0;

        for (int i = 1; i < n; i += 2) {
            temp += f(a + i * h);
        }
        I_n = 0.5 * I + temp * h;
      	eps0 = fabs((I - I_n)) / 3;
        I = I_n;
        ++iter;
   	}
   	return I;
}
afunc *func[6] = {f1, f2, f3, test1, test2, test3};
const double EPS = 1e-6;
double nul(double x) {return 0;}

int main(int argc, char* argv[]) {
    
	if (argc > 1) {
        if(((strcmp(argv[1], "--help") == 0) || strcmp(argv[1], "-h") == 0)) {
            printf("--help\n");
            printf("-h\n");
            printf("--root\n");
            printf("-r\n");
            printf("--iterations\n");
            printf("-i\n");
            printf("--test-root\n");
            printf("-R\n");
            printf("--test-integral\n");
            printf("-I\n");
        }
        else if((strcmp(argv[1], "--root") == 0) || (strcmp(argv[1], "-r") == 0)) {
            printf("%lf\n", root(f1, f2, 0, 2, EPS));
            printf("%lf\n", root(f1, f3, -10, 10, EPS));
            printf("%lf\n", root(f3, f2, -10, -0.1, EPS));
        }
        else if((strcmp(argv[1], "--iterations") == 0) || (strcmp(argv[1], "-i") == 0)) {
            long long unsigned count = 0;
            root(f1, f2, 0, 2, EPS);
            count += iterations;
            root(f1, f3,  -10, 10, EPS);
            count += iterations;
            root(f2, f3, -10, -0.1, EPS);
            count += iterations;
            printf("%llu\n", count);
        }
        else if((strcmp(argv[1], "--test-root") == 0) || (strcmp(argv[1], "-R") == 0) ) {
            int f1, f2;
            double a,b, eps, r;
            sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &f1, &f2, &a, &b, &eps, &r);
            double anw = root(func[f1-1], func[f2-1], a, b, eps); 
            printf("%lf %lf %lf\n", anw, fabs(anw - r), fabs((anw - r) / r));
        }
        else if((strcmp(argv[1], "--test-integral") == 0) || (strcmp(argv[1], "-I") == 0) ){
            int f;
            double a,b, eps, r;
            sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &f, &a, &b, &eps, &r);
            --f;
            double anw = integral(func[f-1], a, b, eps);
            printf("%lf %lf %lf\n", anw, fabs(anw - r), fabs((anw - r) / r));		
        }
    }
	else{
		double r1 = root(f1, f2, 0, 2, EPS);
		double r2 = root(f1, f3, -5, 2, EPS);
		double r3 = root(f2, f3, -2, 2, EPS);
        printf("%lf %lf %lf\n", r1, r2, r3);
		double i1 = integral(f1, r2, r3, EPS);
      	double i2 = integral(f3, r3, r1, EPS);
      	double i3 = integral(f2, r3, r1, EPS);
		printf("%lf\n", i1 - i2 - i3);
	}
}