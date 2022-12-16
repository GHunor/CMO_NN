#include "optoforce.h"
#include "useful_macros.h"

#include <fstream>

int main(){
    std::ofstream file;
    file.open("log10000_optoclass.txt");
    optoforce OF((char*)"COM3", (char*)"Optoforce1");
    std::vector<int> VEC = OF.Get_vector();
    for IRANGE(100)
    {
        Sleep(25);
        VEC = OF.Get_vector();
        file << VEC[0] << ",\t" << VEC[1] << ",\t" << VEC[2] << ",\t" << VEC[3] << "\n";
    }
}