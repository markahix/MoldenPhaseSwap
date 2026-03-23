#include "linalg.h"
#include <iostream>

double dot_product(std::vector<double> A, std::vector<double> B)
{
    if (A.size() != B.size())
    {
        // vector size mismatch, error out.
        std::cout << "Vector size mismatch: "<< A.size() <<  " vs. " << B.size() << std::endl;
        std::cout << "Terminating."<<std::endl;
        exit(1);
    }
    double dot_prod = 0;
    for (int i=0; i < A.size(); i++)
    {
        dot_prod = dot_prod + (A[i]*B[i]);
    }
    return dot_prod;
}