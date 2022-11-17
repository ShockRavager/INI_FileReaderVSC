#pragma once

// PATH     ->  Content/UserInterface
// FILE     ->  INI_RWFlow.hpp

#include <iostream>
#include <string>
#include "../Objects/SaveData/INI_File.hpp"
#include "../Libraries/Functions/DirManager.hpp"

using namespace std;


class INI_RWFlow {
protected:

    //////////////////////////////////////////////////

    INI_File* LFileRef;
    string MGivenPath[2];


    //////////////////////////////////////////////////

    void ActionPARASS() {
        string LString[3];
        bool LInserted;

        cout << "\nInsert param name: ";
        cin >> LString[0];
        cout << "Insert parent section name: ";
        cin >> LString[1];
        cout << "Insert param value (type # or ; to leave the value empty): ";
        cin >> LString[2];
        LInserted = LFileRef->AssignParam(LString[1], LString[0], LString[2]);

        if (!LInserted) {
            cout << "\nERROR - The specified section or param does not exists...\n";
        }
    }

    void ActionFILESAVC() {
        string LString[2];
        short LOverride;

        cout << "\nInsert file name: ";
        cin >> LString[0];
        cout << "Insert path (from this folder): ";
        cin >> LString[1];

        if (DirManager::DoesPathExists(LString[1] + LString[0] + ".ini")) {
            cout << "A file with this name already exists in this path, type 0 if you want to override it: ";
            cin >> LOverride;

            if (LOverride == 0) {
                LFileRef->SaveToFile(LString[0], LString[1]);
            }
        }
        else {
            LFileRef->SaveToFile(LString[0], LString[1]);
        }
    }

    void ActionFILESAVO() {
        if (MGivenPath[0] != "\0" && MGivenPath[1] != "\0") {
            LFileRef->SaveToFile(MGivenPath[0], MGivenPath[1]);
        }
    }

    void ActionFILELOAD() {
        string LString[2];

        cout << "\nInsert file name: ";
        cin >> LString[0];
        cout << "Insert path (from this folder): ";
        cin >> LString[1];

        if (DirManager::DoesPathExists(LString[1] + LString[0] + ".ini")) {
            LFileRef->LoadFromFile(LString[0], LString[1]);
        }
        else {
            short LOption;

            cout << "ERROR - The specified file or path does not exists...\n";
            cout << "Type 1 if you want to retry this operation or another key if you want to exit: ";
            cin >> LOption;

            if (LOption == 1) {
                ExecAction("FILELOAD");
            }
        }
    }

    void ActionFILEVIEW() {
        cout << "\n";
        LFileRef->PrintRows();
    }

    void ActionGIVEPATH() {
        cout << "\nInsert file name: ";
        cin >> MGivenPath[0];
        cout << "Insert path (from this folder): ";
        cin >> MGivenPath[1];
    }

public:

    //////////////////////////////////////////////////

    INI_RWFlow(INI_File* File) :
        LFileRef(File)
    { 
        MGivenPath[0] = "\0";
        MGivenPath[1] = "\0";
    }


    //////////////////////////////////////////////////

    INI_File* GetFile() const {
        return LFileRef;
    }

    bool ExecAction(const string& Value) {
        bool LReturn = true;

        if (Value == "PARASS") {
            ActionPARASS();
        }
        else if (Value == "FILESAVC") {
            ActionFILESAVC();
        }
        else if (Value == "FILESAVO") {
            ActionFILESAVO();
        }
        else if (Value == "FILELOAD") {
            ActionFILELOAD();
        }
        else if (Value == "FILEVIEW") {
            ActionFILEVIEW();
        }
        else if (Value == "GIVEPATH") {
            ActionGIVEPATH();
        }
        else {
            LReturn = false;
        }
        return LReturn;
    }
};