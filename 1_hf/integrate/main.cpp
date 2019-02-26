#include <iostream>
#include <cmath>

using namespace std;

double integrate(int n, double x0, double x1){
    double e = 2.718;
    double h = (x1-x0)/(n+2);
    double q;
    for(int j=0; j<n/2; j++){
        q += cos(x0+(2*j+1)*h)*pow(e,-((x0+(2*j+1)*h)*(x0+(2*j+1)*h)));
    }
    return 2*h*q;
}

int main()
{
    std::cout.precision(12);
    std::cout << integrate(250,-1,3) << endl;
    return 0;
}
