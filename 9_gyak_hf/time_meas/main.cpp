#include "..\headers\matrix.h"
#include <random>
#include <chrono>

auto print = [](const int& n) { std::cout << " " << n; };

int main()
{
    std::random_device rd{};
    std::minstd_rand gen(rd());
    for (int N = 3; N < 400; N++)
    {
        std::vector<double> data1(N);
        std::vector<double> data2(N);
        std::normal_distribution<double> distr(100,20);
        
        for (int q = 0; q < 10; q++)
        {
            std::generate(data1.begin(),data1.end(), [&] {return distr(gen); });
            std::generate(data2.begin(),data2.end(), [&] {return distr(gen); });
            Matrix<double> M1(N, data1);
            Matrix<double> M2(N, data2);
            auto t1 = std::chrono::high_resolution_clock::now();
            Matrix M = std::move(M1) * M2;
            auto t2 = std::chrono::high_resolution_clock::now();
            double x =(static_cast<std::chrono::duration<double, std::milli>>(t2-t1)).count();
            std::cout.precision(16);
            std::cout << N << " " << x << "\n";
        }   
    }
}