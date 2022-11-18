#pragma once

// PATH     ->  Content/UserInterface
// FILE     ->  INI_ReadWrite.hpp

#include <iostream>
#include <string>
#include "../Objects/SaveData/INI_File.hpp"
#include "../Libraries/Functions/DirManager.hpp"

using namespace std;


class INI_ReadWrite {
protected:

    //////////////////////////////////////////////////

    INI_File* LFileRef;             // ATTRIBUTE: Address of the file class that is written or read
    string MGivenPath[2];           // ATTRIBUTE: Default save path tuple (FileName, Path)


    //////////////////////////////////////////////////

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes PARASS action
    */
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

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes FILESAVC action
    */
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

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes FILESAVO action
    */
    void ActionFILESAVO() {
        if (MGivenPath[0] != "\0" && MGivenPath[1] != "\0") {
            LFileRef->SaveToFile(MGivenPath[0], MGivenPath[1]);
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes FILELOAD action
    */
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

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes FILEVIEW action
    */
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

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes SECVIEW action
    */
    void ActionSECVIEW() {
        string LString;
        DoubleLinkedList<string> LList;

        cout << "\nInsert section name: ";
        cin >> LString;
        LList = LFileRef->GetParamList(LString);
        
        if (LList.GetPivotItem() == "NONE") {
            cout << "\nERROR - The specified section or param does not exists...\n";
        }
        else {
            DoubleLinkedList<string>::Iterator LIterator;

            cout << "\n";

            for (LList.ForEachFromFirst(LIterator); LIterator.GetOffset() < LList.GetLength(); LIterator.ShiftForward()) {
                cout << *LIterator.GetItem() << " = ";
                LIterator.ShiftForward();
                cout << *LIterator.GetItem();
                cout << "\n";
            }
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes PARVIEW action
    */
    void ActionPARVIEW() {
        string LString[2];

        cout << "\nInsert param name: ";
        cin >> LString[0];
        cout << "Insert parent section name: ";
        cin >> LString[1];
        cout << "\nValue = " << LFileRef->GetParamValue(LString[1], LString[0]) << "\n";
    }

public:

    //////////////////////////////////////////////////

    /**
    * CONSTRUCTOR
    * --------------------------------------------------
    * Init default params, the address of the FileRef
    * can't be nullptr
    */
    INI_ReadWrite(INI_File* File) :
        LFileRef(File)
    { 
        MGivenPath[0] = "\0";
        MGivenPath[1] = "\0";
    }


    //////////////////////////////////////////////////

    /**
    * const FUNCTION - INI_File*
    * --------------------------------------------------
    * Returns the address of the file object ref (read 
    * only)
    */
    const INI_File* GetFile() const {
        return LFileRef;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Executes an action based on its name
    */
    void ExecAction(const string& Value) {
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
        else if (Value == "SECVIEW") {
            ActionSECVIEW();
        }
        else if (Value == "PARVIEW") {
            ActionPARVIEW();
        }
        else {
            return;
        }
    }
};