#include <iostream>
#include <cmath>

using namespace std;

double integrate(int n, double x0, double x1){
    double e = 2.718;
    double h = (x1-x0)/(n+2);
    double q;
    for(int j=0; j<n/2+1; j++){
        q += cos(x0+(j+1)*h)*pow(e,-x0+(j+1)*h*x0+(j+1)*h);
    }
    double x = 0;
    return 2*h*q-(x1-x0)*h*h*pow(e,-1*pow(x,2)*((4*pow(x,2)-3)*cos(x)+4*x*sin(x))/6);
}

int main()
{
    cout << integrate(250,-1,3) << endl;
    return 0;
}
