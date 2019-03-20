#include <iostream>
#include <vector>
#include <numeric>
#include <array>
#include <cmath>


std::array<double, 2> parameters(std::vector<double> const& x, std::vector<double> const& y){
    if ( x.size() != y.size() ){
        std::cout << "Error: size of X and Y don't match. \n";
        return {NAN,NAN};
    }
    if ( x.size() == 0)
    {
        return {NAN,NAN};
    }

    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    int i = static_cast<int>(x.size());
    
    double mean_x = sum_x/i;
    double mean_y = sum_y/i;
    
    double b_numer = 0;
    double b_denom = 0;
    
    auto f = [mean_x,mean_y](double a, double b){ return (a - mean_x) * (b - mean_y);};
    auto g = [](double a, double b){ return a + b*b;};
    b_numer = std::inner_product(x.begin(), x.end(), y.begin(), 0.0, std::plus<double>(), f);
    b_denom = std::accumulate(x.begin(), x.end(), 0.0, g);
    //for(int j = 0; j < i; j++){
        //b_numer += (x[j] - mean_x) * (y[j] - mean_y);
    //}
    
    double b = b_numer/b_denom;
    double m = mean_y - (b * mean_x);
    return {b,m};
}

int main(){
    //Test case: straight line connecting 2 points
    std::vector<double> u = {0, 1};
    std::vector<double> v = {0, 2};
    std::array<double, 2> param = parameters(u,v);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;

    //Test case: non-matching vector size
    u = {0, 1};
    v = {0};
    param = parameters(u,v);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;

    //Numbers scattered around a straight line: y = 3.9*x-4.777+rand
    std::vector<double> X = {-10.,  -9.,  -8.,  -7.,  -6.,  -5.,  -4.,  -3.,  -2.,  -1.,   0.,
         1.,   2.,   3.,   4.,   5.,   6.,   7.,   8.,   9.,  10.};
    std::vector<double> Y = {-45.70739507, -42.99107028, -35.22373496, -28.16090156,
        -29.11249698, -25.70972399, -23.93654365, -15.9180436 ,
        -11.5717097 , -11.57979128,  -1.37509144,  -0.40783734,
          6.92779448,   7.29152571,  14.7608187 ,  13.20322845,
         15.60232528,  20.49305139,  28.31013749,  31.85108189,
         34.69176681};
    
    
    param = parameters(X,Y);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;
    return 0;
}
