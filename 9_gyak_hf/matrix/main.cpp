#include "..\headers\matrix.h"

int main()
{
    

    std::vector<double> x { -5.1, 3.2, 4.4,
                            -1.2, -3.3, 1.5,
                            4.9, 6.6, -7.3};

    std::vector<double> y { 7.2, -1.1, 0.7,
                            4.3, 3.9, -2.2,
                            -2.4, -5.1, 6.8};

    std::vector<double> test {  2.1, 2.1, 5.1,
                                3.1, 0.6, -0.7,
                                2.5, 1.5, -0.5};

    Matrix<double> A(3,x);
    Matrix<double> B(3,y);
    Matrix<double> C_test(3,test);

    Matrix<double> C = A + B;
    /*if (!compare(C,C_test,1E-8))
    {
        std::cout << "Error: addition doesn't work properly.\n ";
    }

    std::vector<double> q ={-12.3, 4.3, 3.7,
                            -5.5, -7.2,  3.7,
                             7.3, 11.7, -14.1}; 
    //Matrix<double> C_test(3,q);
    C = A - B;
    if (!compare(C,C_test,1E-8))
    {
        std::cout << "Error: subtraction doesn't work properly.\n ";
    }*/
/*
    C_test.data = { -33.52, -4.35, 19.31,
                    -26.43, -19.2, 16.62,
                    81.18, 57.58, -60.73};
    C = A * B;
    if (!compare(C,C_test,1E-8))
    {
        std::cout << "Error: matrix multiplication doesn't work properly.\n ";
    }
    C = std::move(A) * B;

    if (!compare(C,C_test,1E-8))
    {
        std::cout << "Error:r-value matrix multiplication doesn't work properly.\n ";
    }


    A.data = x;
    C_test.data = { -15.3, 9.6, 13.2,
                    -3.6, -9.9, 4.5,
                    14.7, 19.8, -21.9};

    
    if (!compare(3*A,A*3,1E-8) && !compare(3*A,C_test,1E-8))
    {
        std::cout << "Error: matrix scalar multiplication doesn't work properly.\n";
    }

    C = A/3;
    C_test.data = { -1.7, 1.06667, 1.46667,
                    -0.4, -1.1, 0.5,
                    1.63333, 2.2, -2.43333};
    if (!compare(C,C_test, 1E-5))
    {
        std::cout << "Error: matrix scalar division doesn't work properly.\n";
    }

    /*C = A;
    C += B;
    C_test.data = { -12.3, 4.3, 3.7,
                    -5.5, -7.2,  3.7,
                    7.3, 11.7, -14.1};
    if (!compare(C,C_test,1E-8))
    {
        std::cout << "Error: compound addition doesn't work properly.\n ";
    }*/
    return 0;
}