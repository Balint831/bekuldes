#include <iostream>
#include <cmath>

using namespace std;



double f(double x){
    return cos(x)*std::exp(-1*std::pow(x,2));
}

double integrate(int n, double x0, double x1){
    double h = (x1-x0)/(n+2);
    double q;
    for(int j=0; j <= n/2; j++){
        q += f(x0+(2*j+1)*h);
    }
    return 2*h*q;
}

/*double integrate(int n, double x0, double x1){
    double h = (x1-x0)/n;
    double q;
    double xj;
    for(int j = 1; j<=n-1; j++){
        q += f(x0 + j*h);
    }
    return h/2 * (f(x0) + 2*q + f(x1));
}*/

int main()
{
    std::cout.precision(16);
    double z = integrate(25000000,-1,3);
    std::cout <<"Az eredmeny: " << z << "\n"
        << "A WolframAlpha szerint: 1.34638795680345037669816 \nA ketto kulonbsege: "
        << fabs(z-1.34638795680345037669816) << endl;

    return 0;
}
