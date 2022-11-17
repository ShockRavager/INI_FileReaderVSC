#pragma once

// PATH     ->  Content/UserInterface
// FILE     ->  UIFlow.hpp

#include <iostream>
#include <string>
#include <map>
#include "INI_RWFlow.hpp"

using namespace std;


class UIFlow {
protected:

    //////////////////////////////////////////////////

    map<string, string> LCmdMap;


    //////////////////////////////////////////////////

    void InsertCmd(string Name, string Desc) {
        pair<string, string> LPair;

        LPair.first = Name;
        LPair.second = Desc;
        LCmdMap.insert(LPair);
    }

    void CreateCommands() {
        InsertCmd("CMD", "View all commands");
        InsertCmd("EXIT", "Quit program");
        InsertCmd("SECINS", "Add new section");
        InsertCmd("PARINS", "Add new param");
        InsertCmd("PARASS", "Assign a value to a param (if it does not exists, returns an error message)");
        InsertCmd("SECVIEW", "Watch all params for a section and their value (if it does not exists, returns an error message)");
        InsertCmd("PARVIEW", "Watch the value of this param (if it does not exists, returns an error message)");
        InsertCmd("FILEVIEW", "Watch all the file content");
        InsertCmd("SECREM", "Removes a section and all its children param (if it does not exists, returns an error message)");
        InsertCmd("PARREM", "Removes a param (if it does not exists, returns an error message)");
    }

    void PrintSpaces(int Amount) {
        for (int i = 0; i < Amount; i += 1) {
            cout << " ";
        }
    }

    void PrintCommands() {
        cout << "\n";

        for (auto& Pair : LCmdMap) {
            cout << Pair.first;
            PrintSpaces(16 - Pair.first.length());
            cout << "=";
            PrintSpaces(12);
            cout << Pair.second;
            cout << "\n";
        }
        cout << "\n";
    }

    string ExecAction(const string& ActionName, INI_File& File) {
        if (ActionName == "CMD") {
            PrintCommands();
        }
        else if (ActionName == "SECINS") {
            ActionSECINS(File);
        }
    }

    void ActionSECINS(INI_File& File) {
        string LString;

        cout << "Insert section name: ";
        cin >> LString;
        File.AddSection(LString);
    }

    void ActionPARINS(INI_File& File) {
        string LString[3];
        bool LInserted;

        cout << "Insert param name: ";
        cin >> LString[0];
        cout << "Insert parent section name: ";
        cin >> LString[1];
        cout << "Insert param default value (type # or ; to leave the value empty): ";
        cin >> LString[2];
        LInserted = File.AddParam(LString[1], LString[0], LString[2]);

        if (!LInserted) {
            cout << "\nERROR - The specified section does not exists...\n";
        }
    }

public:

    //////////////////////////////////////////////////

    void BeginFlow() {
        INI_File LFile;
        string LString;
        bool LExecValid = true;

        CreateCommands();
        cout << "\n****** INI File Reader ******\n\n";

        while (LExecValid) {
            cout << "Type CMD to view all commands or a command: ";
            cin >> LString;

            if (LString != "EXIT") {
                ExecAction(LString, LFile);
            }
            else {
                LExecValid = false;
            }
        }
    }
};