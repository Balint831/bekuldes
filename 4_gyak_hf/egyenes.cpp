#include <iostream>
#include <vector>
#include <numeric>
#include <array>
#include <cmath>

template<typename T>
T sq(T x){ return x*x; }

std::array<double, 2> parameters(std::vector<double> const& x, std::vector<double> const& y){
    if ( x.size() != y.size() ){
        std::cout << "Error: size of X and Y don't match. \n";
        return {NAN,NAN};
    }
    double sum_x = std::accumulate(x.begin(), x.end(), 0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0);
    int i = static_cast<int>(x.size());
    
    double mean_x = sum_x/i;
    double mean_y = sum_y/i;
    
    double b_numer = 0;
    double b_denom = 0;
    
    for(int j = 0; j < i; j++){
        b_numer += (x[j] - mean_x) * (y[j] - mean_y);
        b_denom += sq(x[j] - mean_x);
    }
    double b = b_numer/b_denom;
    double m = mean_y - (b * mean_x);
    return {b,m};
}

int main(){

    std::vector<double> X = {-10.,  -9.,  -8.,  -7.,  -6.,  -5.,  -4.,  -3.,  -2.,  -1.,   0.,
         1.,   2.,   3.,   4.,   5.,   6.,   7.,   8.,   9.,  10.};
    std::vector<double> Y = {-40.84402621, -34.44268102, -30.18946895, -30.32277281,
       -23.46251648, -20.6829044 , -15.90160359, -13.76817768,
        -7.82667235,  -1.10506376,  -3.48847497,  -0.56390248,
         5.43916348,  11.99643555,  17.34254311,  21.2161478 ,
        21.49048847,  24.65790221,  30.20248365,  33.02920248,
        40.02040066};
    
    //Numbers scattered around a straight line: y = 3.9*x-4.777+rand
    std::array<double, 2> param = parameters(X,Y);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;
    
    //Test case: non-matching vector size
    std::vector<double> u = {0, 1};
    std::vector<double> v = {0};
    param = parameters(u,v);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;
    
    //Test case: straight line connecting 2 points
    std::vector<double> u = {0, 1};
    std::vector<double> v = {0, 2};
    param = parameters(u,v);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;


    return 0;
}