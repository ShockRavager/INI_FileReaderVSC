#pragma once

// PATH     ->  Content/Libraries/Functions
// FILE     ->  Memory.hpp


class Memory {
public:

    //////////////////////////////////////////////////

    /**
    * STATIC FUNCTION - void
    * --------------------------------------------------
    * Reallocates an array passed as a raw pointer
    */
    template<typename TItem>
    static void Realloc(TItem*& Pointer, int Length, int NewLength) {
        TItem* LArray = new TItem[NewLength];
        int LLength;

        (NewLength < Length) 
        ? LLength = NewLength
        : LLength = Length;

        for (int i = 0; i < LLength; i += 1) {
            LArray[i] = Pointer[i];
        }
        delete Pointer;
        Pointer = LArray;
    }
};