#include <iostream>
#include <math.h>

using namespace std;

double sqrt_newton(double num, double x0){
    double a;
    for (;;) {
        a = x0 - ((pow(x0,2)-num)/(2*x0));
        if (fabs(x0-a)<10E-12){
            std::cout.precision(12);
            std::cout << a << endl;
            break;
        }
        x0 = a;
    }

}


int main()
{
    sqrt_newton(612,10);
    return 0;
}
