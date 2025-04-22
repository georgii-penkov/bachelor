#include <fstream>
#include <iostream>
#include <filesystem> //for file remove
#include <string>


int main()
{
    double a = 1.1;
    double b = 2.2;
    std::string filename = "./data.txt";
    std::ofstream file;
    std::filesystem::remove(filename);
    file.open(filename);
    file << "Signal data \n";
    file << a << "\n";
    file << b << "\n";
    file.close();
}


