#pragma once

// PATH     ->  Content/UserInterface
// FILE     ->  UIFlow.hpp

#include <iostream>
#include <string>
#include <map>
#include "INI_ReadWrite.hpp"

using namespace std;


class UIFlow {
protected:

    //////////////////////////////////////////////////

    map<string, string> MCmdMap;            // ATTRIBUTE: Map of all commands


    //////////////////////////////////////////////////

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Insert a command in the map (init only)
    */
    void InsertCmd(string Name, string Desc) {
        pair<string, string> LPair;

        LPair.first = Name;
        LPair.second = Desc;
        MCmdMap.insert(LPair);
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Stores all commands (init only)
    */
    void CreateCommands() {
        InsertCmd("CMD", "View all commands");
        InsertCmd("EXIT", "Quit program");
        InsertCmd("PARASS", "Assign a value to a param (if it does not exists, returns an error message)");
        InsertCmd("SECVIEW", "Watch all params for a section and their value (if it does not exists, returns an error message)");
        InsertCmd("PARVIEW", "Watch the value of this param (if it does not exists, returns an error message)");
        InsertCmd("FILEVIEW", "Watch all the file content");
        InsertCmd("FILESAVC", "Saves the file to a location");
        InsertCmd("GIVEPATH", "Gives a default path where to save (call FILESAVO)");
        InsertCmd("FILESAVO", "Saves the file in the default given location (if you give it before)");
        InsertCmd("FILELOAD", "Loads file from a location");
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Prints a certain number of empty spaces in the 
    * string
    */
    void PrintSpaces(int Amount) {
        for (int i = 0; i < Amount; i += 1) {
            cout << " ";
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Prints all commands presents in the map
    */
    void PrintCommands() {
        cout << "\n";

        for (auto& Pair : MCmdMap) {
            cout << Pair.first;
            PrintSpaces(16 - Pair.first.length());
            cout << "=";
            PrintSpaces(12);
            cout << Pair.second;
            cout << "\n";
        }
        cout << "\n";
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Init sections and params of the file .ini (init 
    * only)
    */
    void InitFileMap(INI_File& File) {
        File.AddSection("GameCharacter");
        File.AddSection("GC.Knight");
        File.AddSection("GC.Bandit");
        File.AddParam("GameCharacter", "DefHP");
        File.AddParam("GameCharacter", "DefFP");
        File.AddParam("GameCharacter", "MaxArmor");
        File.AddParam("GC.Knight", "OverrideHP");
        File.AddParam("GC.Knight", "OverrideFP");
        File.AddParam("GC.Knight", "OverrideMaxArmor");
        File.AddParam("GC.Knight", "TrainingCost");
        File.AddParam("GC.Knight", "TrainingTime");
        File.AddParam("GC.Bandit", "OverrideHP");
        File.AddParam("GC.Bandit", "OverrideFP");
        File.AddParam("GC.Bandit", "OverrideMaxArmor");
        File.AddParam("GC.Bandit", "TrainingCost");
        File.AddParam("GC.Bandit", "TrainingTime");
    }

public:

    //////////////////////////////////////////////////

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Begins the flow of the program
    */
    void BeginFlow() {
        INI_File LFile;
        INI_ReadWrite LFileFlow(&LFile);
        string LString;
        bool LExecValid = true;

        InitFileMap(LFile);
        CreateCommands();
        cout << "\n****** INI File Reader ******\n\n";

        while (LExecValid) {
            cout << "\nType CMD to view all commands or a command: ";
            cin >> LString;

            if (MCmdMap.find(LString) != MCmdMap.end()) {
                if (LString == "CMD") {
                    PrintCommands();
                }
                else if (LString == "EXIT") {
                    LExecValid = false;
                }
                else {
                    LFileFlow.ExecAction(LString);
                }
            }
            else {
                cout << "ERROR - Invalid command...\n";
            }
        }
    }
};