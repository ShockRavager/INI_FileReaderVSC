// PATH     ->  *
// FILE     ->  Launch.cpp

#include "UnitTest/INI_FileUT.hpp"
#include "UnitTest/DoubleLinkedListUT.hpp"
#include "Content/UserInterface/UIFlow.hpp"

using namespace std;


void ExecAllTests(const string& Option) {
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

int main() {
    UIFlow LUserInterface;

//    ExecAllTests("DoubleLinkedList");
//    ExecAllTests("INI_File");
//    DirManager::CreatePath("Data\\");
    LUserInterface.BeginFlow();
    return 0;
}