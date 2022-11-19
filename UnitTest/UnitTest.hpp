#pragma once

// PATH     ->  UnitTest
// FILE     ->  UnitTest.hpp

#include <string>
#include "INI_FileUT.hpp"
#include "DoubleLinkedListUT.hpp"


class UnitTest {
public:

    //////////////////////////////////////////////////

    static void ExecAllTests(const string& Option) {
        if (Option == "DoubleLinkedList") {
            DoubleLinkedListUT::FindUT();
            DoubleLinkedListUT::InsertUT();
            DoubleLinkedListUT::RemoveUT();
        }
        else if (Option == "INI_File") {
            INI_FileUT::AssignValue();
            INI_FileUT::RetrieveData();
            INI_FileUT::SaveData();
        }
    }
};