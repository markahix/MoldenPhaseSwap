#include "molden.h"

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
