#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

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
    private:
        int N;
        std::vector<T> data;
    public:
        Matrix(int n, std::vector<T> const& x): N(n), data(x)
        {}

        Matrix( Matrix const& ) = default;
        Matrix( Matrix && ) = default;

        Matrix<T>& operator=( Matrix <T>&& mv) = default;
        Matrix<T>& operator=( Matrix<T> const& cpy) = default;
        
        int getN() const
        {
            return N;
        }

        std::vector<T> getdata() const
        {
            return data;
        }

        int getlen()
        {
            return static_cast<int>(data.size());
        }

        /*Matrix<T>& operator+= (Matrix<T> const& A)
	    {
            if (A.getN() != this->getN())
            {
                std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
                exit(-1);
            }

		    std::vector<T>& cpy = A.getdata();
            detail::transform_vector2(this->data, cpy, this->data, add);
		    return *this;
        }*/

        /*Matrix<T>& operator-= (Matrix<T> const& A)
	    {
		    std::vector<T>& cpy = A.getdata();
            detail::transform_vector2(*this, cpy, *this, sub);
		    return *this;
        }

        Matrix<T>& operator*= (T const& scl)
	    {
            
		    detail::transform_vector1(*this, *this, [=](T const& x){ return x * scl;} );
		    return *this;
        }*/



    T&      operator ()(int i, int j)
    { return data[N * i + j];}

    T const& operator ()(int i, int j) const
    { return data[N * i + j];}
};


template<typename T>
std::ostream& operator<<( std::ostream& o, Matrix<T> const& A )
{
    for (int i = 0; i < A.getN(); i++)
    {
        for (int j = 0; j < A.getN(); j++)
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
    for (int i = 0; i < A.getN(); i++)
    {   
        o << A[i] << " ";
    }
    o << "\n";
    return o;   
}

template<typename T>
std::istream& operator>>( std::istream& i, Matrix<T> A )
{
    for (int k = 0; k < A.getN(); k++)
    {
        for (int j = 0; j < A.getN(); j++)
        {
            i >> A(k,j);
        }
        
    }
    return i;
}

template<typename T>
Matrix<T> operator+( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
        exit(-1);
    }
    std::vector<T> v;
    detail::transform_vector2(A.getdata(), B.getdata(), v, add);
    Matrix<T> C(A.getN(), v);
    return C;
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& A, Matrix<T> const& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
        exit(-1);
    }
    detail::transform_vector2(A.getdata(), B.getdata(), A.getdata(), add);
    return std::move(A);
}

template<typename T>
Matrix<T> operator-( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of subtraction.\n";
        exit(-1);
    }
    std::vector<T> v;
    detail::transform_vector2(A.getdata(), B.getdata(), v, sub);
    Matrix<T> C(A.getN(), v);
    return C;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& A, Matrix<T> const& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of subtraction.\n";
        exit(-1);
    }
    detail::transform_vector2(A.getdata(), B.getdata(), A.getdata(), sub);
    return std::move(A);
}

template<typename T>
bool compare( Matrix<T> const& A, Matrix<T> const& B, double delta)
{
    if (A.getN() != B.getN())
    {
        return false;
    }
    if (static_cast<int>(A.getdata().size()) != static_cast<int>(B.getdata().size()))
    {
        return false;
    }
    if (static_cast<int>(A.getdata().size()) != A.getN())
    {
        return false;
    }
    if (static_cast<int>(B.getdata().size()) != B.getN())
    {
        return false;
    }
    for (int i = 0; i < A.getN(); i++)
    {   
        for (int j = 0; j < A.getN(); j++)
        {
            if  ((std::accumulate(A.getdata().begin(),A.getdata().end(),0) - std::accumulate(B.getdata().begin(),B.getdata().end(),0)) > delta)
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
    std::vector<T> v ( A.getN() * A.getN() );
    Matrix<T> C(A.getN(), v);
    detail::transform_vector1(A.getdata(), v, [=](T const& x){ return x * q; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator*( Matrix<T>&& A, F q)
{   
    detail::transform_vector1(A.getdata(), A.getdata(), [=](T const& x){ return x * q; });
    return std::move(A);
}

template<typename T,typename F>
Matrix<T> operator*(  F q, Matrix<T> const& A)
{   
    std::vector<T> v ( A.getN() * A.getN() );
    Matrix<T> C(A.getN(), v);
    detail::transform_vector1(A.getdata(), v, [=](T const& x){ return q * x; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator*( F q, Matrix<T>&& A)
{   
    detail::transform_vector1(A.getdata(), A.getdata(), [=](T const& x){ return q * x; });
    return std::move(A);
}

template<typename T,typename F>
Matrix<T> operator/( Matrix<T> const& A,  F q)
{   
    std::vector<T> v ( A.getN() * A.getN() );
    Matrix<T> C(A.getN(), v);
    detail::transform_vector1(A.getdata(), C.getdata(), [=](T const& x){ return x / q; });
    return C;
}

template<typename T,typename F>
Matrix<T>&& operator/( Matrix<T>&& A,  F q)
{   
    detail::transform_vector1(A.getdata(), A.getdata(), [=](T const& x){ return x / q; });
    return std::move(A);
}

template<typename T>
Matrix<T> operator*( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<T> v ( A.getN() * A.getN() );
    Matrix<T> C(A.getN(), v);
    for (int i = 0; i < A.getN(); i++)
    {   
        for (int j = 0; j < B.getN(); j++)
        {
            T sum = 0;
            for (int k = 0; k < A.getN(); k++)
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
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<T> v ( A.getN() );
    
    for (int i = 0; i < A.getN(); i++)
    {   
        for (int j = 0; j < B.getN(); j++)
        {
            T sum = 0;
            for (int k = 0; k < A.getN(); k++)
            {
                sum += A(i,k) * B(k,j);
            }
            v[j] = sum;
        }
        std::copy(v.begin(), v.end(), A.getdata().begin()+(A.getN() * i));
    }
    return std::move(A);
}

template<typename T>
Matrix<T>&& operator*( Matrix<T>& A, Matrix<T> const&& B)
{   
    if (A.getN() != B.getN())
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<T> v ( A.getN() );
    
    for (int i = 0; i < A.getN(); i++)
    {   
        for (int j = 0; j < B.getN(); j++)
        {
            T sum = 0;
            for (int k = 0; k < A.getN(); k++)
            {
                sum += A(i,k) * B(k,j);
            }
            v[j] = sum;
        }
        std::copy(v.begin(), v.end(), A.getdata().begin()+(A.getN() * i));
    }
    return std::move(B);
}