// PATH     ->  *
// FILE     ->  Launch.cpp

#include "UnitTest/UnitTest.hpp"
#include "Content/UserInterface/UIFlow.hpp"

using namespace std;


int main() {
    UIFlow LUserInterface;

    UnitTest::ExecAllTests("DoubleLinkedList");
    UnitTest::ExecAllTests("INI_File");
    LUserInterface.BeginFlow();
    return 0;
}