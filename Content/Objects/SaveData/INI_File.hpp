#pragma once

// PATH     ->  Objects/SaveData
// FILE     ->  INI_File.hpp

#ifdef __APPLE__
    #include<sys/stat.h>
#else
    #include<filesystem>
#endif
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../CoreTypes/DoubleLinkedList.hpp"

using namespace std;
#ifdef __APPLE__
    // NOTHING
#else
    using namespace filesystem;
#endif


class INI_File {
protected:

    //////////////////////////////////////////////////

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

    map<string, INI_Section> MFileMap;
    map<string, string> MParentSections;
    INI_Loader MLoader;
    string MExtension;
    const char MSlashOP;


    //////////////////////////////////////////////////

    bool IsComment(char Value) const {
        return Value == '#' || Value == ';';
    }

    bool IsEscape(char Value) const {
        return Value == '\\';
    }

    bool IsSectionStart(char Value) const {
        return Value == '[';
    }

    bool IsSectionEnd(char Value) const {
        return Value == ']';
    }

    bool IsParamSep(char Value) const {
        return Value == '=';
    }

    bool IsEndLine(char Value) const {
        return Value == '\n' || Value == '\0';
    }

    bool IsSpace(char Value) const {
        return Value == ' ' || Value == '\t';
    }

    void LoadData() {
        INI_Section* LSection = nullptr;
        DoubleLinkedList<INI_Line>::Iterator LIterator;

        for (MLoader.MFileRows.ForEachFromFirst(LIterator); LIterator.GetOffset() < MLoader.MFileRows.GetLength(); LIterator.ShiftForward()) {
            ReadLine(LIterator.GetItem()->MLine, &LSection);
        }
    }

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

    INI_Line CreateLoaderLine(string Row, int Index) {
        INI_Line LLine;

        LLine.MLine = Row;
        LLine.MIndex = Index;
        return LLine;
    }

    void CreatePath(const string& Path) {
        #ifdef __APPLE__
            struct stat LStat;

            if (stat(Path.c_str(), &LStat) == -1) {
                mkdir(Path.c_str(), 0777);
            }
        #else
            if (!exists(Path)) {
                create_directories(Path);
            }
        #endif
    }

    bool IsPathValid(const string& Path) const {
        #ifdef __APPLE__
            struct stat LStat;

            return stat(Path.c_str(), &LStat) != -1;
        #else
            return exists(Path);
        #endif
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

    void AddSection(string SectionName) {
        pair<string, INI_Section> LPair;

        LPair.first = SectionName;
        LPair.second = INI_Section();
        MFileMap.insert(LPair);
    }

    void AddParam(const string& SectionName, string ParamName, string DefaultValue = "#") {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            pair<string, string> LPair;

            LPair.first = ParamName;
            LPair.second = DefaultValue;
            LSectionIT->second.MParamMap.insert(LPair);
            LPair.first = ParamName;
            LPair.second = SectionName;
            MParentSections.insert(LPair);
        }
    }

    void RemoveSection(const string& SectionName) {
        map<string, string>::iterator LIterator = MParentSections.begin();

        MFileMap.erase(SectionName);
    
        while (LIterator != MParentSections.end()) {
            if (LIterator->second == SectionName) {
                LIterator = MParentSections.erase(LIterator);
            }
        }
    }

    void RemoveParam(const string& SectionName, const string& ParamName) {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            LSectionIT->second.MParamMap.erase(ParamName);
            MParentSections.erase(ParamName);
        }
    }

    void AssignParam(const string& SectionName, const string& ParamName, string ParamValue) {
        map<string, INI_Section>::iterator LSectionIT = MFileMap.find(SectionName);

        if (LSectionIT != MFileMap.end()) {
            map<string, string>::iterator LParamIT = LSectionIT->second.MParamMap.find(ParamName);

            if (LParamIT != LSectionIT->second.MParamMap.end()) {
                LParamIT->second = ParamValue;
            }
        }
    }

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

    string GetParentSection(const string& ParamName) {
        map<string, string>::iterator LParamIT = MParentSections.find(ParamName);

        if (LParamIT != MParentSections.end()) {
            return LParamIT->second;
        }
        else {
            return "#";
        }
    }

    void PrintRows() {
        for (auto& PairS : MFileMap) {
            cout << "[" << PairS.first << "]\n";

            for (auto& PairP : PairS.second.MParamMap) {
                cout << PairP.first + " = " << PairP.second << "\n";
            }
            cout << "\n";
        }
    }

    void ClearFileLoader() {
        MLoader.MFileRows.Clear();
        MLoader.MRowsSaved = false;
    }

    bool ReadFile(const string& FileName, const string& Path) {
        if (IsPathValid(Path)) {
            string  
                LFullPath = Path + MSlashOP + FileName + MExtension,
                LFileRow;
            ifstream LFileStr;
            INI_Line LLine;
            int LIndex = 0;

            LFileStr.open(LFullPath);
            ClearFileLoader();
            
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

    void WriteFile() {
        if (!MLoader.MRowsSaved) {
            CopyToLoader();
            MLoader.MRowsSaved = true;
        }
    }

    void SaveToFile(const string& FileName, const string& Path) {
        string LFullPath = Path + MSlashOP + FileName + MExtension;
        ofstream LFileStr;
        DoubleLinkedList<INI_Line>::Iterator LLineIT;

        CreatePath(Path);
        LFileStr.open(LFullPath);
        WriteFile();

        for (MLoader.MFileRows.ForEachFromFirst(LLineIT); LLineIT.GetOffset() < MLoader.MFileRows.GetLength(); LLineIT.ShiftForward()) {
            LFileStr << LLineIT.GetItem()->MLine;
        }
        LFileStr.close();
    }

    bool LoadFromFile(const string& FileName, const string& Path) {
        bool LLoad = ReadFile(FileName, Path);
        
        if (LLoad) {
            LoadData();
        }
        return LLoad;
    }
};
