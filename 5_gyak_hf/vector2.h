#include <cmath>
#include <numeric>
#include <iostream>

template<typename T>
T sq(T x)
{
    return x*x;
}

template<typename T>
struct Vector2d
{
    T x, y;

    Vector2d& operator+=( Vector2d const& v )
    {
        x += v.x; y += v.y;
        return *this;
    }

    Vector2d& operator-=( Vector2d const& v )
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    template<typename G>
    Vector2d& operator*=( G lambda )
    {
        x *= lambda; y *= lambda;
        return *this;
    }

    template<typename G>
    Vector2d& operator/=( G lambda )
    {
        x /= lambda; y /= lambda;
        return *this;
    }
    


};

template<typename T>
Vector2d<T> operator+( Vector2d<T> const& a, Vector2d<T> const& b )
{
    return Vector2d<T>{ a.x + b.x, a.y + b.y};
}

template<typename T>
Vector2d<T> operator-( Vector2d<T> const& a, Vector2d<T> const& b )
{
    return Vector2d<T>{ a.x - b.x, a.y - b.y};
}

template<typename T, typename F>
Vector2d<T> operator*( Vector2d<T> const& a, F lambda )
{
    return Vector2d<T>{ lambda * a.x, lambda * a.y};
}

template<typename T, typename F>
Vector2d<T> operator*( F lambda, Vector2d<T> const& a )
{
    return Vector2d<T>{ lambda * a.x, lambda * a.y};
}

template<typename T, typename F>
Vector2d<T> operator/( Vector2d<T> const& a, F lambda )
{
    return Vector2d<T>{a.x / lambda, a.y / lambda};
}

template<typename T>
double dot( Vector2d<T> const& a, Vector2d<T> const& b )
{
    return a.x * b.x + a.y * b.y;
}

template<typename T>
double length( Vector2d<T> const& a )
{
    return sqrt(sq(a.x) + sq(a.y));
}

template<typename T>
double sqlength( Vector2d<T> const& a )
{
    return sq(a.x) + sq(a.y);
}

template<typename T>
Vector2d<T> normalize( Vector2d<T> const& a )
{
    return Vector2d<T>{ a.x / length(a), a.y / length(a) } ;
}

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& v )
{
    o << v.x << "  " << v.y;
    return o;
}

template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T> v )
{
    i >> v.x;
    i >> v.y;
    return i;
}