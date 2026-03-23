#include "molden.h"
#include "linalg.h"

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

void CompareTwoMoldens(std::string filename_A, std::string filename_B)
{
    MoldenFile A(filename_A);
    MoldenFile B(filename_B);

    if (A.n_orbitals != B.n_orbitals)
    {
        std::cout << "Validated matching orbital counts." << std::endl;
        std::cout << filename_A << " (" << A.n_orbitals << ")" << std::endl;
        std::cout << filename_B << " (" << B.n_orbitals << ")"  << std::endl;
        std::cout << "Mismatch in orbital count!"  << std::endl;
        exit(1);
    }
    // compare each orbital
    bool rewrite_necessary = false;
    for (int q=0; q < A.n_orbitals; q++)
    {
        if (dot_product(A.GetOrbitalCoefficients(q), B.GetOrbitalCoefficients(q)) < 0)
        {
            B.PhaseSwapOrbital(q);
            rewrite_necessary = true;
        }
    }
    if (rewrite_necessary)
    {
        B.RewriteMoldenFile();
        std::cout << "Finished rewriting phase-swapped molden file." << std::endl;
    }
}

int main (int argc, char** argv)
{
    // Parse command line for filenames.  Assume first and second.
    std::vector <std::string> files = GetFileList(argc, argv);
    
    // Load first filename in the list as set of orbital values.
    for (int i = 0; i < files.size() - 1; i++)
    {
        CompareTwoMoldens(files[i], files[i+1]);
    }
    std::cout << "Completed molden file processing. " <<std::endl;
    return 0;
}
