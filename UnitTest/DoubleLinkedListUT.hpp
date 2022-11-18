#pragma once

// PATH     ->  UnitTest
// FILE     ->  DoubleLinkedListUT.hpp

#include <iostream>
#include "../Content/Objects/CoreTypes/DoubleLinkedList.hpp"

using namespace std;


class DoubleLinkedListUT {
public:

    //////////////////////////////////////////////////

    static void InsertUT() {
        DoubleLinkedList<short> LList;

        LList.InsertAsFirst(20);
        LList.InsertAsLast(30);

        if (LList.GetFirst() == 20) {
            cout << "\n[INSERT AS FIRST]\tDONE";
        }
        else {
            cout << "\n[INSERT AS FIRST]\tFAILED";
        }

        if (LList.GetLast() == 30) {
            cout << "\n[INSERT AS LAST]\tDONE";
        }
        else {
            cout << "\n[INSERT AS LAST]\tFAILED";
        }
        LList.InsertAt(40, 1);

        if (LList[1] == 40) {
            cout << "\n[INSERT AT POSITION]\tDONE";
        }
        else {
            cout << "\n[INSERT AT POSITION]\tFAILED";
        }
        cout << "\n\n";
    }
};