#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
T sq(T x){return x*x;}

double f(double x){return cos(x)*std::exp(-1*sq(x));}

//n>0, a>b
double integrate(int n, double x0, double x1){
    if (n <=0){ cout<<"Hiba: n<=0\n"; return 1;}
    if (x0>x1){std::swap(x0,x1);
        std::cout << "\nA hatarok rosszul lettek megadva: x1<x0. Megcsereltem oket!\n" <<endl;}//megcserélés
    double h = (x1-x0)/(n+2);
    double q = 0;
    for(int j=0; j <= n/2; j++){
        q += f(x0+(2*j+1)*h);
    }
    return 2*h*q;
}

int main()
{
    std::cout.precision(16);
    double z = integrate(250000,-1,3);

    std::cout <<"Eredmenye: " << z << "\n"
        << "integrate(cos(x)*e^(-x^2), -1,3) a WolframAlpha szerint: 1.34638795680345037669816 \nA ketto kulonbsege: "
        << fabs(z-1.34638795680345037669816) << endl;

    return 0;
}
