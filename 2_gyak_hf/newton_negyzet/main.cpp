#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
T sq(T x){ return x*x; }

double sqrt_newton(double num, double x0){
    double a;
    for (;;) {
        a = x0 - ((sq(x0)-num)/(2*x0));
        if (fabs(x0-a)<10E-12){
            return a;
        }
        x0 = a;
    }

}


int main()
{
    double a = sqrt_newton(612,10);
    std::cout<< a;
    return 0;
}
