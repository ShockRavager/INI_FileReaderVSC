#pragma once

// PATH     ->  Content/Libraries/Functions
// FILE     ->  FileManager.hpp

#include <string>
#include "../../Objects/CoreTypes/DoubleLinkedList.hpp"

using namespace std;


class FileManager {
protected:

    //////////////////////////////////////////////////

    static char GetPathSlash() {
        #ifdef __APPLE__
            return '/';
        #else
            return "\\";
        #endif
    }

public:

    //////////////////////////////////////////////////

    static void CreatePath(const string& Path) {
        DoubleLinkedList<string> LList;
        string LString;

        LString.reserve(Path.length());

        for (int i = 0; i < Path.length(); i += 1) {
            if (Path[i] != FileManager::GetPathSlash()) {
                LString.push_back(Path[i]);
            }
        }
    }
};