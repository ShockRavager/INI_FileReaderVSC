#pragma once

// PATH     ->  UnitTest
// FILE     ->  INI_FileUT.hpp

#include <iostream>
#include <fstream>
#include "../Content/Objects/SaveData/INI_File.hpp"

using namespace std;


class INI_FileUT {
public:

    //////////////////////////////////////////////////

    static void SaveData() {
        INI_File LFile;
        ifstream LFileStr;
        string 
            LString,
            LSlash;

        cout << "\n****** INI_File Save Test ******\n\n";
        LSlash += DirManager::GetPathSlash();
        LFile.AddSection("Section");
        LFile.AddParam("Section", "Param");
        LFile.AssignParam("Section", "Param", "Value");
        LFile.SaveToFile("FileName", "Path1" + LSlash + "Path2" + LSlash);
        LFileStr.open(BASE_PATH + "Path1" + LSlash + "Path2" + LSlash + "FileName.ini");
        getline(LFileStr, LString);

        if (LString == "[Section]") {
            cout << "[SECTION]\t\tDONE\n";
        }
        else {
            cout << "[SECTION]\t\tFAILED\n";
        }
        getline(LFileStr, LString);

        if (LString == "Param = Value") {
            cout << "[PARAM]\t\t\tDONE\n";
        }
        else {
            cout << "[PARAM]\t\t\tFAILED\n";
        }
        cout << "\n";
        LFileStr.close();
    }

    static void RetrieveData() {
        INI_File LFile;

        cout << "\n****** INI_File Retrieve Data Test ******\n\n";
        LFile.AddSection("Section");
        LFile.AddParam("Section", "Param");
        LFile.AssignParam("Section", "Param", "Value");
        LFile.SaveToFile("FileName", "Path1/Path2/");
        LFile.LoadFromFile("FileName", "Path1/Path2/");

        if (LFile.GetParamValue("Section", "Param") == "Value") {
            cout << "[PARAM VALUE]\t\tDONE\n";
        }
        else {
            cout << "[PARAM VALUE]\t\tFAILED\n";
        }
        cout << "\n";
    }

    static void AssignValue() {
        INI_File LFile;

        cout << "\n****** INI_File Assign Data Test ******\n\n";
        LFile.AddSection("Section");
        LFile.AddParam("Section", "Param");
        LFile.AssignParam("Section", "Param", "Value");

        if (LFile.GetParamValue("Section", "Param") == "Value") {
            cout << "[PARAM VALUE]\t\tDONE\n";
        }
        else {
            cout << "[PARAM VALUE]\t\tFAILED\n";
        }
        cout << "\n";
    }
};