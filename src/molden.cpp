#include "molden.h"

MoldenFile::MoldenFile(std::string filename)
{
    molden_filename = filename;
    pre_orbital_text = "";
    energies = {};
    spins = {};
    occupancies = {};
    orb_coefficients = {};
    ParseToOrbitals();
}

MoldenFile::~MoldenFile()
{

}

void MoldenFile::ParseToOrbitals()
{
    std::string line;
    std::string junk;
    std::ifstream ifile(molden_filename, std::ios::in);
    while (getline(ifile,line))
    {
        // Get past [MO] line
        pre_orbital_text+=line;
        pre_orbital_text+="\n";
        if (line.find("[MO]") != std::string::npos)
        {
            break;
        }
    }
    bool first_orbital_done = false;
    double energy=0.0, occup=-1.0;
    std::string spin;
    std::vector<double> coeffs = {};
    while (getline(ifile,line))
    {
        std::stringstream dummy;
        if (line.empty())
        {
            continue;
        }
        dummy.str(line);
        if (line.find("Ene=") != std::string::npos)
        {
            if (first_orbital_done)
            {
                orb_coefficients.push_back(coeffs);

                coeffs.clear();
            }
            dummy >> junk >> energy;
            energies.push_back(energy);
            first_orbital_done = true;
            continue;
        }
        else if (line.find("Spin=")!= std::string::npos)
        {
            dummy >> junk >> spin;
            spins.push_back(spin);
            continue;
        }
        else if (line.find("Occup=")!= std::string::npos)
        {
            dummy >> junk >> occup;
            occupancies.push_back(occup);
            continue;
        }
        // handle coefficients
        else if (line.find_first_not_of(' ') != std::string::npos)
        {
            dummy >> junk >> junk;
            coeffs.push_back(stof(junk));
            continue;
        }
    }
    orb_coefficients.push_back(coeffs);
    n_orbitals = orb_coefficients.size();
    ifile.close();
}

void MoldenFile::PhaseSwapOrbital(int orb_number)
{
    for (int i=0; i < orb_coefficients[orb_number].size(); i++)
    {
        orb_coefficients[orb_number][i] = orb_coefficients[orb_number][i]*-1;
    }
}

void MoldenFile::RewriteMoldenFile()
{   
    std::ofstream ofile(molden_filename, std::ios::out);
    ofile << pre_orbital_text;
    for (int i = 0; i < n_orbitals; i++)
    {
        std::vector<double> coeffs = orb_coefficients[i];
        std::stringstream buffer;
        buffer.str("");
        buffer << " Ene=" << std::right << std::fixed << std::setw(11) << std::setprecision(4) << std::setfill(' ') << energies[i] << std::endl;
        buffer << " Spin= " << spins[i] << std::endl;
        buffer << " Occup= " << std::fixed << std::setprecision(1) << occupancies[i] << std::endl;
        for (int j=0; j < coeffs.size(); j++)
        {
            buffer << std::right << std::setw(5) << std::setfill(' ') << j+1 << " " << std::setw(10) << std::fixed << std::setprecision(5) << coeffs[j] << std::endl;
        }
        ofile << buffer.str();
    }
    ofile.close();
}

std::vector<double> MoldenFile::GetOrbitalCoefficients(int orb_num)
{
    return orb_coefficients[orb_num];
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