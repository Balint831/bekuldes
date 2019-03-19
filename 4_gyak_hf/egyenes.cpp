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
    std::vector<double> Y = {-38.66244597, -28.95488426, -29.7711778 , -20.86226482,
       -36.17297738, -22.68780779, -17.47410452, -15.82897239,
       -12.64531047,   8.4791807 ,  -3.54591447,   4.81745921,
         6.07552966,   3.97511625,   9.09218524,  16.39128824,
        18.57345306,  19.07712847,  31.87348948,  33.53273962,
        40.31253216};
    
    
    param = parameters(X,Y);
    std::cout <<"y = " << param[0] << " * x + " << param[1] <<std::endl;
    return 0;
}