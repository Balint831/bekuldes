#include <cmath>
#include <vector>

template<typename T>
struct Matrix
{
    int N,M;
    std::vector<T> data;

    Matrix(int n, int m, std::vector<T> x)
    : N(n), M(m), data(x)
    {}


    T&      operator ()(int i, int j)
    { return data[N * i + j];}

    T const& operator ()(int i, int j) const
    { return data[N * i + j];}
};

template<typename T>
void print_matrix( Matrix<T> const& A)
{
    for (int i = 0; i < A.N; i++)
    {
        for (int j = 0; j < A.M; j++)
        {
            std::cout << A.data[ i * A.N + j] << " ";
        }
        std::cout <<"\n";
    }
    std::cout << "\n";
}

template<typename T>
Matrix<T> operator+( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.M != B.M || A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of addition.\n";
        exit(-1);
    }
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            C(i,j) =  A(i,j) + B(i,j);
        }
    }
    return C;
}

template<typename T>
Matrix<T> operator-( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.M != B.M || A.N != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of subtraction.\n";
        exit(-1);
    }
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            C(i,j) =  A(i,j) - B(i,j);
        }
    }
    return C;
}

template<typename T>
bool compare( Matrix<T> const& A, Matrix<T> const& B, double delta)
{
    if (A.M != B.M || A.N != B.N)
    {
        return false;
    }
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            if  (fabs(A(i,j) - B(i,j)) > delta)
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
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            C(i,j) =  A(i,j) * q;
        }
    }
    return C;
}

template<typename T,typename F>
Matrix<T> operator*(  F q, Matrix<T> const& A)
{   
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            C(i,j) = q * A(i,j);
        }
    }
    return C;
}

template<typename T,typename F>
Matrix<T> operator/( Matrix<T> const& A,  F q)
{   
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < A.M; j++)
        {
            C(i,j) = A(i,j) / q;
        }
    }
    return C;
}

template<typename T>
Matrix<T> operator*( Matrix<T> const& A, Matrix<T> const& B)
{   
    if (A.M != B.N)
    {
        std::cout << "Error: the matrices at hand aren't compatible from the perspective of matrix multiplication.\n";
        exit(-1);
    }
    std::vector<double> v ( A.N * A.M );
    Matrix<double> C(A.N, A.M, v);
    double sum = 0;
    for (int i = 0; i < A.N; i++)
    {   
        for (int j = 0; j < B.M; j++)
        {
            for (int k = 0; k < A.M; k++)
            {
                sum += A(i,k) * B(k,j);
            }
            C(i,j) = sum;
            sum = 0;
        }
    }
    return C;
}