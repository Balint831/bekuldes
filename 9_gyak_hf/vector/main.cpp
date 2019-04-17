#include "vector2.h"
#include <iostream>


int main(int, char**) 
{
    Vector2d<double> v{};
    Vector2d<double> u{};

    /*std::cout << "Enter vector 1:\n";
    std::cin >> v.x;
    std::cin >> v.y;
    std::cout << v << "\n";

    std::cout << "Enter vector 2:\n";
    std::cin >> u.x;
    std::cin >> u.y;
    std::cout << u << "\n";

    std::cout << "The sum of the two vectors is:\n" << v + u << "\n";*/

    Vector2d<double> w;
    Vector2d<double> test;

    v = {1.4, -3.2};
    u = {-0.2, 5.5};
    
    w = u - v;
    test = {-1.6, 8.7};
    
    if (length(w - test) > 1E-12)
    {
        std::cout << "Error: subtraction doesn't work properly.\n";
    }

    w = 4.1 * v;
    test = {5.74, -13.12};
    if ( length(w - test) > 1E-12)
    {
        std::cout << "Error: left-side scalar multiplication doesn't work properly. \n";
    }

    w = v * 4.1;
    test = {5.74, -13.12};
    if ( length(w - test) > 1E-12)
    {
        std::cout << "Error: right-side scalar multiplication doesn't work properly. \n";
    }

    w = v / 2;
    test = {0.7, -1.6};
    if ( length(w-test) > 1E-12 )
    {
        std::cout << "Error: division with scalar doesn't work properly. \n";
    }

    double t = -17.88;
    if (std::abs(t - dot(v,u)) > 1E-12)
    {
        std::cout << "Error: dot-product doesn't work properly.\n";
    }
    
    t = 3.49284983;
    if (std::abs(length(v) - t) > 1E-8)
    {
        std::cout << "Error: length calculation doesn't work properly.\n";
    }

    t = 12.2;
    if (std::abs(sqlength(v) - t) > 1E-12)
    {
        std::cout << "Error: square length calculation doesn't work properly.\n ";
    }

    test = {0.400818835, -0.916157337};
    if (abs(length(test) - length(normalize(v))) > 1E-8)
    {
        std::cout << "Error: vector normalization doesn't work properly.\n";
    }


    v += {-0.2,5.5};
    test = {1.2, 2.3};
    if (abs(length(v) - length(test)) > 1E-12)
    {
        std::cout << "Error: compound assignment += doesn't work properly.\n";
    }

    v = {1.4,-3.2};
    v -= {-0.2,5.5};
    test = {1.6, -8.7};
    if (abs(length(v) - length(test)) > 1E-12)
    {
        std::cout << "Error: compound assignment -= doesn't work properly.\n";
    }

    v = {1.4,-3.2};
    v *= 3.2;
    test = {4.48, -10.24};
    if (abs(length(v) - length(test)) > 1E-12)
    {
        std::cout << "Error: compound assignment *= doesn't work properly.\n";
    }

    v = {1.4,-3.2};
    v /= 3.2;
    test = {0.4375, -1};
    if (abs(length(v) - length(test)) > 1E-12)
    {
        std::cout << "Error: compound assignment /= doesn't work properly.\n";
    }
    return 0;
}