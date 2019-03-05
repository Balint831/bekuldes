#include <iostream>
#include <cmath>

using namespace std;

template<typename F, typename G, typename T>
T newton(F f, G g, T x0){
    double a;
    for (;;) {
        a = x0 - f(x0)/g(x0);
        if (fabs(x0-a)<1E-12){
            return a;
        }
        x0 = a;
    }
}

int main()
{
    double a;
    a = newton([](double x){return x * x - 612.0; }, [](double x){return 2.0 * x; }, 10.0);
    return a;
}
