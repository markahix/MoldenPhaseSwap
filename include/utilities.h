#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iomanip>
#include <ctime>
#include <set>
#include <complex>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


double dot_product(std::vector<double> A, std::vector<double> B);
std::vector<std::string> GetFileList(int argc, char** argv);

#endif