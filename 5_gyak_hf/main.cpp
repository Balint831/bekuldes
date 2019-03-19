#include "vector2.h"
#include <iostream>


int main(int, char**) 
{
    Vector2d<double> v{};
    Vector2d<double> u{};

    std::cout << "Enter vector 1:\n";
    std::cin >> v.x;
    std::cin >> v.y;
    std::cout << v << "\n";

    std::cout << "Enter vector 2:\n";
    std::cin >> u.x;
    std::cin >> u.y;
    std::cout << u << "\n";

    std::cout << "The sum of the two vectors is:\n" << v + u << "\n";

    Vector2d<double> w;

    w = v - u; 
    std::cout << w.x << " " << w.y <<"\n"; //Subtraction

    w = 2 * v;
    std::cout << w.x << " " << w.y <<"\n"; //Left-side multiplication with scalar

    w = v * 3;
    std::cout << w.x << " " << w.y <<"\n"; //Right-side multiplication with scalar

    w = v / 2;
    std::cout << w.x << " " << w.y <<"\n"; //Dividing with scalar

    std::cout << dot(v,u) <<"\n"; //Dot product of two vectors
    
    std::cout << length(v) << "\n"; //Length of a vector

    std::cout << sqlength(v) << "\n"; //Square of a length of a vector

    std::cout << normalize(v).x << " " << normalize(v).y << "\n"; //Vector normalization

    v += u;
    std::cout << v.x << " " << v.y << "\n";

    v -= u;
    std::cout << v.x << " " << v.y << "\n";  

    v *= 3.2;
    std::cout << v.x << " " << v.y << "\n";

    v /= 3.2;
    std::cout << v.x << " " << v.y << "\n";
    return 0;
}