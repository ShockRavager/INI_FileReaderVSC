#pragma once

// PATH     ->  Content/UserInterface
// FILE     ->  INI_RWFlow.hpp

#include <iostream>
#include <string>
#include "../Objects/SaveData/INI_File.hpp"

using namespace std;


class INI_RWFlow {
public:

    //////////////////////////////////////////////////

    static void WriteSectionData(INI_File& File) {
        string LString;

        cout << "Insert section name: ";
        cin >> LString;
        File.AddSection(LString);
    }

    static void WriteParamData(INI_File& File) {
        string LString[3];

        cout << "Insert the parent section name: ";
        cin >> LString[0];
        cout << "Insert param name: ";
        cin >> LString[1];
        cout << "Insert param value (insert a # or a ; if you want to not specify a value): ";
        cin >> LString[2];

        if (LString[2] == "#" || LString[2] == ";") {
            File.AddParam(LString[0], LString[1]);
        }
        else {
            File.AddParam(LString[0], LString[1], LString[2]);
        }
    }

    static void UpdateParamValue(INI_File& File) {
        string LString[3];

        cout << "Insert the parent section name: ";
        cin >> LString[0];
        cout << "Insert param name: ";
        cin >> LString[1];
        cout << "Insert param value (insert a # or a ; if you want to not specify a value): ";
        cin >> LString[2];
        File.AssignParam(LString[0], LString[1], LString[2]);
    }
};