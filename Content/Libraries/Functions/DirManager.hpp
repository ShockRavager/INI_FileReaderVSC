#pragma once

// PATH     ->  Content/Libraries/Functions
// FILE     ->  DirManager.hpp

#ifdef __APPLE__
    #include <sys/stat.h>
#else
    #include <filesystem>
#endif
#include <string>
#include "../../Objects/CoreTypes/DoubleLinkedList.hpp"

using namespace std;
#ifdef __APPLE__
    // NOTHING
#else
    using namespace filesystem;
#endif


class DirManager {
protected:

    //////////////////////////////////////////////////

    /**
    * STATIC FUNCTION - char
    * --------------------------------------------------
    * Returns the OS based slash separator for the paths
    */
    static char GetPathSlash() {
        #ifdef __APPLE__
            return '/';
        #else
            return '\\';
        #endif
    }

    /**
    * STATIC FUNCTION - void
    * --------------------------------------------------
    * Returns the OS based slash separator for the paths
    */
    static void CreateDirectory(const string& Path) {
        #ifdef __APPLE__
            mkdir(Path.c_str(), 0777);
        #else
            create_directories(Path);
        #endif
    }

public:

    //////////////////////////////////////////////////

    /**
    * STATIC FUNCTION - void
    * --------------------------------------------------
    * Creates a path of directories and subdirectories
    * starting from the path string
    */
    static void CreatePath(const string& Path) {
        string 
            LString,
            LFullString;
        int LMaxID = Path.length();

        LString.reserve(LMaxID);
        LFullString.reserve(LMaxID);

        for (int i = 0; i < LMaxID; i += 1) {
            if (Path[i] != GetPathSlash()) {
                LString.push_back(Path[i]);
            }
            else {
                LString.push_back(GetPathSlash());
                CreateDirectory(LFullString + LString);
                LFullString.append(LString);
                LString.clear();
                LString.reserve(LMaxID);
            }
        }
    }

    /**
    * STATIC FUNCTION - bool
    * --------------------------------------------------
    * Check if this path exists (OS based). You can
    * include a file in the path
    */
    static bool DoesPathExists(const string& Path) {
        #ifdef __APPLE__
            struct stat LStat;

            return stat(Path.c_str(), &LStat) != -1;
        #else
            return exists(Path);
        #endif
    }

    /**
    * STATIC FUNCTION - void
    * --------------------------------------------------
    * Creates the path if not exists
    */
    static void CreatePathIfNotExists(const string& Path) {
        if (!DoesPathExists(Path)) {
            CreatePath(Path);
        }
    }

    /**
    * STATIC FUNCTION - string
    * --------------------------------------------------
    * Creates the path if not exists
    */
    static string GetFullPath(const string& FileName, const string& Path, const string& Extension) {
        return Path + FileName + Extension;
    }
};