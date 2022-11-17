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
        InsertCmd("PARASS", "Assign a value to a param (if it does not exists, returns an error message)");
        InsertCmd("SECVIEW", "Watch all params for a section and their value (if it does not exists, returns an error message)");
        InsertCmd("PARVIEW", "Watch the value of this param (if it does not exists, returns an error message)");
        InsertCmd("FILEVIEW", "Watch all the file content");
        InsertCmd("SECREM", "Removes a section and all its children param (if it does not exists, returns an error message)");
        InsertCmd("PARREM", "Removes a param (if it does not exists, returns an error message)");
        InsertCmd("FILESAVC", "Saves the file to a location");
        InsertCmd("GIVEPATH", "Gives a default path where to save (call FILESAVO)");
        InsertCmd("FILESAVO", "Saves the file in the default given location (if you give it before)");
        InsertCmd("FILELOAD", "Loads file from a location");
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

public:

    //////////////////////////////////////////////////

    void BeginFlow() {
        INI_File LFile;
        INI_RWFlow LFileFlow(&LFile);
        string LString;
        bool 
            LExecValid = true,
            LCmdValid;

        LFile.AddSection("Computer1");
        LFile.AddParam("Computer1", "Color");
        LFile.AddParam("Computer1", "Type");
        LFile.AddParam("Computer1", "Weight");
        LFile.AddSection("Computer2");
        LFile.AddParam("Computer2", "Color");
        LFile.AddParam("Computer2", "Type");
        LFile.AddParam("Computer2", "Weight");
        CreateCommands();
        cout << "\n****** INI File Reader ******\n\n";

        while (LExecValid) {
            cout << "\nType CMD to view all commands or a command: ";
            cin >> LString;

            if (LString == "CMD") {
                PrintCommands();
            }
            else if (LString == "EXIT") {
                LExecValid = false;
            }
            else {
                LCmdValid = LFileFlow.ExecAction(LString);
            }

            if (!LCmdValid) {
                cout << "ERROR - Invalid command...\n";
            }
        }
    }
};