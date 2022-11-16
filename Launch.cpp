// PATH     ->  *
// FILE     ->  Launch.cpp

#include "Content/Libraries/Functions/DirManager.hpp"
#include "Content/Objects/SaveData/INI_File.hpp"
#include "UnitTest/INI_FileUT.hpp"

using namespace std;


int main() {
    INI_File LFile;

    LFile.AddSection("Section1");
    LFile.AddParam("Section1", "Param1");
    LFile.AddParam("Section1", "Param3");
    LFile.LoadFromFile("Config", "Data/INI/");
    cout << "\n";
    LFile.PrintRows();
    return 0;
}