#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_vector1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}


inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };
inline auto sq  = [](auto const& x){ return x*x; }; 

template<typename T>
class Matrix
{
    
    public:
        int N;
        std::vector<T> data;
        
        Matrix(int n, std::vector<T> const& x): N(n), data(x)
        {}        
        
    T&      operator ()(int i, int j)
    { return data[N * i + j];}

    T const& operator ()(int i, int j) const
    { return data[N * i + j];}

    /*std::vector<T>&       operator ()(int i)
    { return std::slice(data, N * i, N * (i+1) - 1);}

    std::vector<T> const& operator ()(int i) const
    { return data[N * i ];}*/
};


template<typename T>
std::ostream& operator<<( std::ostream& o, Matrix<T> const& A )
{
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.N; j++)
        {
            o << A(i,j) << " ";
        }
        o <<"\n";
    }
    o << "\n";
    return o;   
}

template<typename T>
std::ostream& operator<<( std::ostream& o, std::vector<T> const& A )
{
    for (int i = 0; i < A.size(); i++)
    {
        o << A[i] << " ";
    }
    o << "\n";
    return o;   
}

template<typename T>
std::istream& operator>>( std::istream& i, Matrix<T> A )
{
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.N; j++)
        {
            i >> A(i,j);
        }
        
    }
    return i;
}

template<typename T>
Matrix<T> operator+( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
        exit(-1);
    }
    std::vector<T> v ( A.N * A.N );
    Matrix<T> C(A.N, v);
    detail::transform_vector2(A.data, B.data, C.data, add);
    return C;
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
        exit(-1);
    }
    detail::transform_vector2(A.data, B.data, A.data, add);
    return std::move(A);
}

template<typename T>
Matrix<T> operator-( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of subtraction.\n";
        exit(-1);
    }
    std::vector<T> v ( A.N * A.N);
    Matrix<T> C(A.N, v);
    detail::transform_vector2(A.data, B.data, C.data, sub);
    return C;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of subtraction.\n";
        exit(-1);
    }
    detail::transform_vector2(A.data, B.data, A.data, sub);
    return std::move(A);
}

template<typename T>
bool compare( Matrix<T> const& A, Matrix<T> const& B, double delta)
{
    if (A.N != B.N)
    {
        return false;
    }
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.N; j++)
        {
            if  (std::abs(A(i,j) - B(i,j)) > delta)
            {
                return false;
            }
        }
    }
    return true;
}


template<typename T,typename F>
Matrix<T> operator*( Matrix<T> const& A, F q)
{   
    std::vector<T> v ( A.N * A.N );
    Matrix<T> C(A.N, v);
    detail::transform_vector1(A.data, v, [=](T const& x){ return x * q; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator*( Matrix<T>&& A, F q)
{   
    detail::transform_vector1(A.data, A.data, [=](T const& x){ return x * q; });
    return std::move(A);
}

template<typename T,typename F>
Matrix<T> operator*(  F q, Matrix<T> const& A)
{   
    std::vector<T> v ( A.N * A.N );
    Matrix<T> C(A.N, v);
    detail::transform_vector1(A.data, v, [=](T const& x){ return q * x; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator*( F q, Matrix<T>&& A)
{   
    detail::transform_vector1(A.data, A.data, [=](T const& x){ return q * x; });
    return std::move(A);
}

template<typename T,typename F>
Matrix<T> operator/( Matrix<T> const& A,  F q)
{   
    std::vector<T> v ( A.N * A.N );
    Matrix<T> C(A.N, v);
    detail::transform_vector1(A.data, C.data, [=](T const& x){ return x / q; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator/( Matrix<T>&& A,  F q)
{   
    detail::transform_vector1(A.data, A.data, [=](T const& x){ return x / q; });
    return std::move(A);
}

template<typename T>
Matrix<T> operator*( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<T> v ( A.N * A.N );
    Matrix<T> C(A.N, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < B.N; j++)
        {
            T sum = 0;
            for (int k = 0; k < A.N; k++)
            {
                sum += A(i,k) * B(k,j);
            }
            C(i,j) = sum;
        }
    }
    return C;
}

template<typename T>
Matrix<T>&& operator*( Matrix<T>&& A, Matrix<T> const& B)
{   
    if (A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<T> v ( A.N );
    
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < B.N; j++)
        {
            T sum = 0;
            for (int k = 0; k < A.N; k++)
            {
                sum += A(i,k) * B(k,j);
            }
            v[j] = sum;
        }
        std::copy(v.begin(), v.end(), A.data.begin()+(A.N * i));
        std::cout << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    return std::move(A);
}