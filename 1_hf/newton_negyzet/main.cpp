#include <iostream>

using namespace std;

double sqrt_newton(double num, double x0){
    double a;
    a = x0-((x0*x0-num)/(2*x0));
    return a;
}


int main()
{
    double u,v;
    double x0 = 10;
    for(int i = 0; i < 5; i++){
        v = sqrt_newton(612, x0);
        x0 = v;
        cout << x0 << endl;
    }

    return 0;
}
