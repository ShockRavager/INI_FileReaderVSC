#pragma once

// PATH     ->  Objects/SaveData
// FILE     ->  INI_File.hpp

#ifdef __APPLE__
    #include <sys/stat.h>
#else
    #include <filesystem>
#endif
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../CoreTypes/DoubleLinkedList.hpp"
#include "../../Libraries/Functions/DirManager.hpp"

using namespace std;
#ifdef __APPLE__
    // NOTHING
#else
    using namespace filesystem;
#endif


/**
* CLASS
* --------------------------------------------------
* Class that can store data and save it in a file
* .ini
*/
class INI_File {
protected:

    //////////////////////////////////////////////////

    /**
    * NESTED STRUCT
    * --------------------------------------------------
    * Keeps memory of the line as string and its line 
    * number
    */
    struct INI_Line {

        //////////////////////////////////////////////////

        string MLine;
        int MIndex;


        //////////////////////////////////////////////////

        INI_Line& operator = (const INI_Line& rhs) {
            if (this != &rhs) {
                MLine = rhs.MLine;
                MIndex = rhs.MIndex;
            }
            return *this;
        }
    };

    /**
    * NESTED STRUCT
    * --------------------------------------------------
    * Represents a section of the file and contains a 
    * list of params
    */
    struct INI_Section {

        //////////////////////////////////////////////////

        map<string, string> MParamMap;


        //////////////////////////////////////////////////

        INI_Section& operator = (const INI_Section& rhs) {
            if (this != &rhs) {
                MParamMap = rhs.MParamMap;
            }
            return *this;
        }
    };

    /**
    * NESTED CLASS
    * --------------------------------------------------
    * This struct contains the list of the lines of the
    * .ini file. This is a volatile object so you need
    * to save the file in order to save data
    */
    struct INI_Loader {

        //////////////////////////////////////////////////

        DoubleLinkedList<INI_Line> MFileRows;
        bool MRowsSaved;


        //////////////////////////////////////////////////

        INI_Loader& operator = (const INI_Loader& rhs) {
            if (this != &rhs) {
                MFileRows = rhs.MFileRows;
                MRowsSaved = rhs.MRowsSaved;
            }
            return *this;
        }
    };


    //////////////////////////////////////////////////

    map<string, INI_Section> MFileMap;              // ATTRIBUTE - Map of all params that can be read by the file
    map<string, string> MParentSections;            // ATTRIBUTE - Map of the parent sections for all params
    INI_Loader MLoader;                             // ATTRIBUTE - View INI_Loader struct
    string MExtension;                              // ATTRIBUTE - Default extension of the file (.ini)
    const char MSlashOP;                            // ATTRIBUTE - Separator for the paths (OS depending)


    //////////////////////////////////////////////////

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is a comment delimitator
    */
    bool IsComment(char Value) const {
        return Value == '#' || Value == ';';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is an escape delimitator
    */
    bool IsEscape(char Value) const {
        return Value == '\\';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is a section start 
    * delimitator
    */
    bool IsSectionStart(char Value) const {
        return Value == '[';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is a section end 
    * delimitator
    */
    bool IsSectionEnd(char Value) const {
        return Value == ']';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is a param separator 
    * between its name and its value
    */
    bool IsParamSep(char Value) const {
        return Value == '=';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is an end line or a invalid
    * (null) character
    */
    bool IsEndLine(char Value) const {
        return Value == '\n' || Value == '\0';
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Return true if the char is a space (or a tab)
    */
    bool IsSpace(char Value) const {
        return Value == ' ' || Value == '\t';
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Read the lines that are stored in the loader
    * object
    */
    void SaveData(const string& FileName, const string& Path) {
        string LFullPath = DirManager::GetFullPath(FileName, Path, MExtension);
        ofstream LFileStr;
        DoubleLinkedList<INI_Line>::Iterator LLineIT;

        LFileStr.open(LFullPath);

        for (MLoader.MFileRows.ForEachFromFirst(LLineIT); LLineIT.GetOffset() < MLoader.MFileRows.GetLength(); LLineIT.ShiftForward()) {
            LFileStr << LLineIT.GetItem()->MLine;
        }
        LFileStr.close();
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Read the lines that are stored in the loader
    * object
    */
    void LoadData() {
        INI_Section* LSection = nullptr;
        DoubleLinkedList<INI_Line>::Iterator LIterator;

        for (MLoader.MFileRows.ForEachFromFirst(LIterator); LIterator.GetOffset() < MLoader.MFileRows.GetLength(); LIterator.ShiftForward()) {
            ReadLine(LIterator.GetItem()->MLine, &LSection);
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Read the line char by char
    */
    void ReadLine(const string& Line, INI_Section** Section) {
        bool LBreak = false;
        int LIndex = 0;
        char LChar;

        while (!LBreak && LIndex < Line.length()) {
            LChar = Line[LIndex];

            if (IsEndLine(LChar) || IsComment(LChar)) {
                LBreak = true;
            }
            else if (IsSpace(LChar)) {
                LIndex += 1;
            }
            else if (IsSectionStart(LChar)) {
                *Section = LoadSection(Line, LIndex);
            }
            else {
                if (Section != nullptr) {
                    LoadParam(Line, LIndex, *Section);
                }
                else {
                    LBreak = true;
                }
            }
        }
    }

    /**
    * FUNCTION - INI_Section*
    * --------------------------------------------------
    * Load a section from its name passed as a file line
    */
    INI_Section* LoadSection(const string& Line, int& Index) {
        bool LBreak = false;
        char LChar;
        string LFakeLine;
        map<string, INI_Section>::iterator LSectionIT;
        INI_Section* LReturn = nullptr;

        LFakeLine.reserve(Line.length());
        Index += 1;

        while (!LBreak && Index < Line.length()) {
            LChar = Line[Index];

            if (IsEndLine(LChar)) {
                LBreak = true;
            }
            else if (IsSpace(LChar)) {
                Index += 1;
            }
            else if (IsSectionEnd(LChar)) {
                LBreak = true;
                LSectionIT = MFileMap.find(LFakeLine);

                if (LSectionIT != MFileMap.end()) {
                    LReturn = &LSectionIT->second;
                }
                Index += 1;
            }
            else {
                LFakeLine.push_back(LChar);
                Index += 1;
            }
        }
        return LReturn;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Load a param from its name and value passed as a 
    * file line and stores it in its parent section
    */
    void LoadParam(const string& Line, int& Index, INI_Section* Section) {
        if (Section != nullptr) {
            bool 
                LBreak = false,
                LParamNameB = false;
            char LChar;
            string 
                LParamName,
                LParamValue;
            string
                * LFakeLine = &LParamName,
                * LParam = nullptr;
            map<string, string>::iterator LParamIT;

            LParamName.reserve(Line.length());
            LParamValue.reserve(Line.length());

            while (!LBreak && Index < Line.length()) {
                LChar = Line[Index];

                if (IsEndLine(LChar) || IsComment(LChar) || (IsParamSep(LChar) && LParamNameB)) {
                    LBreak = true;
                }
                else if (IsSpace(LChar)) {
                    Index += 1;
                }
                else if (IsEscape(LChar)) {
                    LFakeLine->push_back(Line[Index + 1]);
                    Index += 2;
                }
                else if (IsParamSep(LChar) && !LParamNameB) {
                    LParamIT = Section->MParamMap.find(*LFakeLine);

                    if (LParamIT != Section->MParamMap.end()) {
                        LParam = &LParamIT->second;
                        LFakeLine = &LParamValue;
                        LParamNameB = true;
                        Index += 1;
                    }
                    else {
                        LBreak = true;
                        Index = Line.length();
                    }
                }
                else {
                    LFakeLine->push_back(LChar);
                    Index += 1;
                }
            }
            if (Index == Line.length() && LParamNameB) {
                (*LParam) = (*LFakeLine);
            }
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Stores data as string lines in the loader object
    */
    void CopyToLoader() {
        INI_Line LLine;
        int LIndex = 0;

        MLoader.MFileRows.Clear();

        for (auto& PairS : MFileMap) {
            LLine.MLine = "[" + PairS.first + "]\n";
            LLine.MIndex = LIndex;
            MLoader.MFileRows.InsertAsLast(LLine);
            LIndex += 1;

            for (auto& PairP : PairS.second.MParamMap) {
                LLine.MLine = PairP.first + " = " + PairP.second + "\n";
                LLine.MIndex = LIndex;
                MLoader.MFileRows.InsertAsLast(LLine);
                LIndex += 1;
            }
            LLine.MLine = "\n";
            LLine.MIndex = LIndex;
            MLoader.MFileRows.InsertAsLast(LLine);
        }
        MLoader.MRowsSaved = true;
    }

    /**
    * FUNCTION - INI_Line
    * --------------------------------------------------
    * Creates a INI_Line object
    */
    INI_Line CreateLoaderLine(string Row, int Index) {
        INI_Line LLine;

        LLine.MLine = Row;
        LLine.MIndex = Index;
        return LLine;
    }

public:

    //////////////////////////////////////////////////

    #ifdef __APPLE__
        INI_File() :
            MSlashOP('/'),
            MExtension(".ini")
        { }
    #else
        INI_File() :
            MSlashOP('\\'),
            MExtension(".ini")
        { }
    #endif

    ~INI_File()
    { }


    //////////////////////////////////////////////////

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Adds a new section in the file map
    */
    void AddSection(string SectionName) {
        pair<string, INI_Section> LPair;

        LPair.first = SectionName;
        LPair.second = INI_Section();
        MFileMap.insert(LPair);
        MLoader.MRowsSaved = false;
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Adds a new param in the file map, returns false if
    * a section with the specified name does not exists
    */
    bool AddParam(const string& SectionName, string ParamName, string DefaultValue = "#") {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            pair<string, string> LPair;

            LPair.first = ParamName;
            LPair.second = DefaultValue;
            LSectionIT->second.MParamMap.insert(LPair);
            LPair.first = ParamName;
            LPair.second = SectionName;
            MParentSections.insert(LPair);
            MLoader.MRowsSaved = false;
            return true;
        }
        else {
            return false;
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Removes the section and its children params
    */
    void RemoveSection(const string& SectionName) {
        map<string, string>::iterator LIterator = MParentSections.begin();

        MFileMap.erase(SectionName);
    
        while (LIterator != MParentSections.end()) {
            if (LIterator->second == SectionName) {
                LIterator = MParentSections.erase(LIterator);
                MLoader.MRowsSaved = false;
            }
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Removes a param from the map
    */
    void RemoveParam(const string& SectionName, const string& ParamName) {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            LSectionIT->second.MParamMap.erase(ParamName);
            MParentSections.erase(ParamName);
            MLoader.MRowsSaved = false;
        }
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Assign a value to a param
    */
    bool AssignParam(const string& SectionName, const string& ParamName, string ParamValue) {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);
        bool LValid = false;;

        if (LSectionIT != MFileMap.end()) {
            map<string, string>::iterator LParamIT = LSectionIT->second.MParamMap.find(ParamName);

            if (LParamIT != LSectionIT->second.MParamMap.end()) {
                LParamIT->second = ParamValue;
                LValid = true;
                MLoader.MRowsSaved = false;
            }
        }
        return LValid;
    }

    /**
    * FUNCTION - string
    * --------------------------------------------------
    * Returns the value of a param as string
    */
    string GetParamValue(const string& SectionName, const string& ParamName) {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            map<string, string>::iterator LParamIT = LSectionIT->second.MParamMap.find(ParamName);

            if (LParamIT != LSectionIT->second.MParamMap.end()) {
                return LParamIT->second;
            }
            else {
                return "NONE";
            }
        }
        else {
            return "NONE";
        }
    }

    /**
    * FUNCTION - string
    * --------------------------------------------------
    * Returns the name of the parent section of a param
    */
    string GetParentSection(const string& ParamName) {
        map<string, string>::iterator LParamIT = MParentSections.find(ParamName);

        if (LParamIT != MParentSections.end()) {
            return LParamIT->second;
        }
        else {
            return "#";
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Prints all data in a command line window
    */
    void PrintRows() {
        for (auto& PairS : MFileMap) {
            cout << "[" << PairS.first << "]\n";

            for (auto& PairP : PairS.second.MParamMap) {
                cout << PairP.first + " = " << PairP.second << "\n";
            }
            cout << "\n";
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Clear data in the loader to save space
    */
    void ClearLoader() {
        MLoader.MFileRows.Clear();
        MLoader.MRowsSaved = false;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Reads the file content and stores it in the loader
    * NOTE: This will not load any data from the file,
    *       you must use LoadFromFile function in order 
    *       to do it
    */
    bool ReadFile(const string& FileName, const string& Path) {
        string LFullPath = DirManager::GetFullPath(FileName, Path, MExtension);
        
        if (DirManager::DoesPathExists(LFullPath)) {
            string LFileRow;
            ifstream LFileStr;
            INI_Line LLine;
            int LIndex = 0;

            LFileStr.open(LFullPath);
            ClearLoader();
            
            while (getline(LFileStr, LFileRow)) {
                MLoader.MFileRows.InsertAsLast(CreateLoaderLine(LFileRow, LIndex));
                LIndex += 1;
            }
            LFileStr.close();
            return true;
        }
        else {
            return false;
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Writes data in the loader as strings
    * NOTE: This will not save any data in the file, you
    *       must use SaveToFile function in order to do
    *       it
    */
    void WriteFile() {
        if (!MLoader.MRowsSaved) {
            CopyToLoader();
            MLoader.MRowsSaved = true;
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Saves the content of the loader in a file .ini. 
    * Mark the override param as true if you want to let
    * this function to override file if it already exists
    * in the specified path or as false if you want to
    * ignore saving in this case
    */
    bool SaveToFile(const string& FileName, const string& Path, bool Override = true) {
        string LFullPath = DirManager::GetFullPath(FileName, Path, MExtension);

        if (!DirManager::DoesPathExists(LFullPath)) {
            DirManager::CreatePath(Path);
            WriteFile();
            SaveData(FileName, Path);
            return true;
        }
        else if (Override) {
            WriteFile();
            SaveData(FileName, Path);
            return true;
        }
        else {
            return false;
        }
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Retrieve data from a file .ini and returns false
    * if the specified path or file does not exists
    */
    bool LoadFromFile(const string& FileName, const string& Path) {
        bool LLoad = ReadFile(FileName, Path);
        
        if (LLoad) {
            LoadData();
        }
        return LLoad;
    }
};
