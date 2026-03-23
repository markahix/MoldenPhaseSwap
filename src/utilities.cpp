#include "utilities.h"

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

std::vector<std::string> GetFileList(int argc, char** argv)
{
    std::vector <std::string> files = {};
    for (int i=1; i<argc; i++) //argv[0] is the executable, so start at 1 for arguments.
    {
        std::string filename = argv[i];
        if (!fs::exists(filename))
        {
            std::cout << filename << " not found. " << std::endl;
            continue;
        }
        files.push_back(filename);
    }
    std::cout << "Found " << files.size() << " molden files. " << std::endl;
    if (files.size() < 2) // Need at least two molden files for phase checking.
    {
        std::cout << "Not enough valid molden files to compare.  Exiting." << std::endl;
        exit(1);
    }
    return files;
}
