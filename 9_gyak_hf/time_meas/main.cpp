#include "..\headers\matrix.h"
#include <random>
#include <chrono>


int main()
{
    std::random_device rd{};
    std::minstd_rand gen(rd());
    
    int N = 3;
    {
        std::vector<double> data1(N);
        std::vector<double> data2(N);
        std::normal_distribution<double> distr(100,20);
        std::generate(data1.begin(),data1.end(), [&] {return distr(gen); });
        std::generate(data2.begin(),data2.end(), [&] {return distr(gen); });
        std::cout << N<<"\n";
        Matrix<double> M1(N, data1);
        Matrix<double> M2(N, data2);
        std::cout << M1;
        auto t1 = std::chrono::high_resolution_clock::now();
        //Matrix M = std::move(M1) * M2;
        auto t2 = std::chrono::high_resolution_clock::now();
    }

    
}