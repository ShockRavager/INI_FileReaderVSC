// PATH     ->  *
// FILE     ->  Launch.cpp

#include "Content/Libraries/Functions/DirManager.hpp"
#include "Content/Objects/SaveData/INI_File.hpp"


int main() {
    INI_File LFile;

    LFile.AddSection("Section1");
    LFile.AddSection("Section2");
    LFile.AddParam("Section1", "Param1");
    LFile.AddParam("Section1", "Param2");
    LFile.AddParam("Section1", "Param3");
    LFile.AddParam("Section1", "Param4");
    LFile.AddParam("Section2", "Param1");
    LFile.AssignParam("Section1", "Param1", "100");
    LFile.AssignParam("Section1", "Param2", "150");
    DirManager::CreatePath("Alfa/Beta/Gamma/");
    return 0;
}