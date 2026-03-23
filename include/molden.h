#ifndef MOLDEN_H
#define MOLDEN_H
#include "utilities.h"
#include "constants.h"

class MoldenFile
{
    public:
        MoldenFile(std::string filename);
        ~MoldenFile();
        int n_orbitals;
        void PhaseSwapOrbital(int orb_number);
        void RewriteMoldenFile();
        std::vector<double> GetOrbitalCoefficients(int orb_num);
        std::vector<double> energies;
        std::vector<std::string> spins;
        std::vector<double> occupancies;
        std::vector<std::vector<double>> orb_coefficients;
    private:
        std::string molden_filename;
        void ParseToOrbitals();
        std::string pre_orbital_text;
};



#endif