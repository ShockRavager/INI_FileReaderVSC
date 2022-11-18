#pragma once

// PATH     ->  Content/Objects/CoreTypes
// FILE     ->  DoubleLinkedList.hpp

#include <vector>

using namespace std;


template<typename TItem>
class DoubleLinkedList {
protected:

    //////////////////////////////////////////////////

    /**
    * NESTED STRUCT
    * --------------------------------------------------
    * A node of the list
    */
    struct DLLNode {

        //////////////////////////////////////////////////

        TItem MItem;
        DLLNode
            * MPrev,
            * MNext;
    };


    //////////////////////////////////////////////////

    DLLNode* MPivot;                    // ATTRIBUTE: Pivot element of this list, only destructor can delete it
    int MLength;                        // ATTRIBUTE: Number of elements in the list


    //////////////////////////////////////////////////

    /**
    * FUNCTION - DLLNode*
    * --------------------------------------------------
    * Create pivot node
    */
    DLLNode* CreatePivot() {
        DLLNode* LNode = new DLLNode;

        LNode->MPrev = LNode;
        LNode->MNext = LNode;
        return LNode;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Insert a node in the list
    */
    void InsertNode(DLLNode* Node, DLLNode* Prev, DLLNode* Next) {
        Node->MPrev = Prev;
        Node->MNext = Next;
        Prev->MNext = Node;
        Next->MPrev = Node;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Remove a node from the list
    */
    void RemoveNode(DLLNode* Node) {
        Node->MPrev->MNext = Node->MNext;
        Node->MNext->MPrev = Node->MPrev;
        delete Node;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Recursively delete all the nodes in the list
    */
    void ClearHP(DLLNode* Node) {
        if (Node != MPivot) {
            ClearHP(Node->MNext);
            delete Node;
        }
    }

public:

    //////////////////////////////////////////////////

    /**
    * NESTED CLASS
    * --------------------------------------------------
    * Iterator for this list
    */
    class Iterator {
        protected:

        //////////////////////////////////////////////////

        DLLNode
            * MNode,
            * MPivot;
        int MOffset;            // ATTRIBUTE: The number of elements already watched

    public:

        //////////////////////////////////////////////////

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Update the ref node
        */
        void SetNode(DLLNode* Node) {
            MNode = Node;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Update the ref pivot
        */
        void SetPivot(DLLNode* Node) {
            MPivot = Node;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Update offset
        */
        void SetOffset(int Value) {
            MOffset = Value;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Shift to the next element
        */
        void ShiftForward() {
            if (MNode->MNext != MPivot) {
                MNode = MNode->MNext;
            }
            else {
                MNode = MNode->MNext->MNext;
            }
            MOffset += 1;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Shift to the previous element
        */
        void ShiftReverse() {
            if (MNode->MPrev != MPivot) {
                MNode = MNode->MPrev;
            }
            else {
                MNode = MNode->MPrev->MPrev;
            }
            MOffset += 1;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Shift forward by a certain number of elements
        */
        void ShiftForwardBy(int Offset) {
            for (int i = 0; i < Offset; i += 1) {
                if (MNode->MNext != MPivot) {
                    MNode = MNode->MNext;
                }
                else {
                    MNode = MNode->MNext->MNext;
                }
            }
            MOffset += Offset;
        }

        /**
        * FUNCTION - void
        * --------------------------------------------------
        * Shift reverse by a certain number of elements
        */
        void ShiftReverseBy(int Offset) {
            for (int i = 0; i < Offset; i += 1) {
                if (MNode->MPrev != MPivot) {
                    MNode = MNode->MPrev;
                }
                else {
                    MNode = MNode->MPrev->MPrev;
                }
            }
            MOffset -= Offset;
        }

        /**
        * FUNCTION - TItem*
        * --------------------------------------------------
        * Returns a pointer to the current item stored in 
        * the iterator
        */
        TItem* GetItem() const {
            return &MNode->MItem;
        }

        /**
        * FUNCTION - int
        * --------------------------------------------------
        * Returns the current offset
        */
        int GetOffset() const {
            return MOffset;
        }


        //////////////////////////////////////////////////

        Iterator& operator = (const Iterator& rhs) {
        if (&rhs != this) {
                MNode = rhs.MNode;
                MPivot = rhs.MPivot;
                MOffset = rhs.MOffset;
            }
            return *this;
        }
    };


    //////////////////////////////////////////////////

    /**
    * CONSTRUCTOR
    * --------------------------------------------------
    * Default constructor
    */
    DoubleLinkedList() :
        MPivot(CreatePivot()),
        MLength(0)
    { 
        MPivot->MPrev = MPivot;
        MPivot->MNext = MPivot;
    }

    /**
    * CONSTRUCTOR
    * --------------------------------------------------
    * Copy constructor
    */
    DoubleLinkedList(const DoubleLinkedList<TItem>& Copy) :
        MPivot(CreatePivot()),
        MLength(Copy.MLength)
    { 
        Iterator LIterator;
        DLLNode* LNode = nullptr;

        for (Copy.ForEachFromFirst(LIterator); LIterator.GetOffset() < Copy.MLength; LIterator.ShiftForward()) {
            LNode = new DLLNode;

            LNode->MItem = (*LIterator.GetItem());
            InsertNode(LNode, MPivot->MPrev, MPivot);
        }
    }

    /**
    * DESTRUCTOR
    * --------------------------------------------------
    * Clear all the nodes and deletes the pivot element
    */
    ~DoubleLinkedList()
    {
        ClearHP(MPivot->MNext);
        delete MPivot;
    }


    //////////////////////////////////////////////////

    /**
    * const FUNCTION - int
    * --------------------------------------------------
    * Returns the length of the list
    */
    int GetLength() const {
        return MLength;
    }

    /**
    * FUNCTION - TItem&
    * --------------------------------------------------
    * Get the last item stored at the list
    */
    TItem& GetFirst() {
        return MPivot->MNext->MItem;
    }

    /**
    * const FUNCTION - TItem&
    * --------------------------------------------------
    * Get the first item stored at the list
    */
    TItem& GetFirst() const {
        return MPivot->MNext->MItem;
    }

    /**
    * FUNCTION - TItem&
    * --------------------------------------------------
    * Get the last item stored at the list
    */
    TItem& GetLast() {
        return MPivot->MPrev->MItem;
    }

    /**
    * const FUNCTION - TItem&
    * --------------------------------------------------
    * Get the last item stored at the list
    */
    TItem& GetLast() const {
        return MPivot->MPrev->MItem;
    }

    /**
    * FUNCTION - TItem&
    * --------------------------------------------------
    * Get the item stored at the pivot element
    */
    TItem& GetPivotItem() {
        return MPivot->MItem;
    }

    /**
    * const FUNCTION - TItem&
    * --------------------------------------------------
    * Get the item stored at the pivot element
    */
    TItem& GetPivotItem() const {
        return MPivot->MItem;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Assign an item for the pivot, you can use this 
    * an additional element
    */
    void AssignPivotItem(TItem Item) {
        MPivot->MItem = Item;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Inserts an element at the start of the list
    */
    void InsertAsFirst(TItem Item) {
        DLLNode* LNode = new DLLNode;

        LNode->MItem = Item;
        InsertNode(LNode, MPivot, MPivot->MNext);
        MLength += 1;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Inserts an element at the end of the list
    */
    void InsertAsLast(TItem Item) {
        DLLNode* LNode = new DLLNode;

        LNode->MItem = Item;
        InsertNode(LNode, MPivot->MPrev, MPivot);
        MLength += 1;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Inserts an element at a specfied offset
    */
    void InsertAt(TItem Item, int Offset) {
        DLLNode
            * LNodeID = MPivot->MNext,
            * LNode = new DLLNode;
        int LIndex = 0;

        while (LIndex < Offset) {
            LNodeID = LNodeID->MNext;
            LIndex += 1;
        }
        LNode->MItem = Item;
        InsertNode(LNode, LNodeID->MPrev, LNodeID);
        MLength += 1;
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Removes an item from the list and returns false if
    * the element does not exists
    */
    bool RemoveItem(const TItem& Item) {
        DLLNode* LNodeID = MPivot;
        int LIndex = 0;

        if (MLength > 0) {
            while (LNodeID->MNext != MPivot && LNodeID->MItem != Item) {
                LNodeID = LNodeID->MNext;
            }
            if (LNodeID != MPivot) {
                RemoveNode(LNodeID);
                MLength -= 1;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Removes the item at the specified index
    * NOTE: The list is circular, so if the offset 
    *       exceeds the list length, it restart watching
    *       from the first element (until it has reached
    *       the right offset ID)
    */
    void RemoveAt(int Offset) {
        DLLNode* LNodeID = MPivot->MNext;
        int LIndex = 0;

        if (MLength > 0) {
            while (LIndex < Offset) {
                if (LNodeID->MNext != MPivot) {
                    LNodeID = LNodeID->MNext;
                }
                else {
                    LNodeID = LNodeID->MNext->MNext;
                }
                LIndex += 1;
            }
            RemoveNode(LNodeID);
            MLength -= 1;
        }
    }

    /**
    * FUNCTION - int
    * --------------------------------------------------
    * Returns the offset where the item is stored, 
    * returns -1 if the item does not exists
    */
    int FindOffset(const TItem& Item) const {
        DLLNode* LNodeID = MPivot->MPrev;
        int LIndex = MLength - 1;

        while (LNodeID != MPivot && LNodeID->MItem != Item) {
            LNodeID = LNodeID->MPrev;
            LIndex -= 1;
        }
        return LIndex;
    }

    /**
    * FUNCTION - bool
    * --------------------------------------------------
    * Returns true if the item exists in the list
    */
    bool Contains(const TItem& Item) const {
        return FindOffset(Item) != -1;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Clears the list
    */
    void Clear() {
        ClearHP(MPivot->MNext);
        delete MPivot;
        MPivot = CreatePivot();
        MLength = 0;
    }

    /**
    * FUNCTION - vector<TItem>
    * --------------------------------------------------
    * Transform the list in a vector
    */
    vector<TItem> ToArray() {
        vector<TItem> LArray;
        DLLNode LNode = MPivot->MNext;

        LArray.reserve(MLength);

        for (int i = 0; i < MLength; i += 1) {
            LArray.push_back(LNode.MItem);
        }
        return LArray;
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Begins a for each loop starting from the first
    * element
    */
    void ForEachFromFirst(Iterator& Object) const {
        Object.SetNode(MPivot->MNext);
        Object.SetPivot(MPivot);
        Object.SetOffset(0);
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Begins a for each loop starting from the last 
    * element
    */
    void ForEachFromLast(Iterator& Object) const {
        Object.SetNode(MPivot->MPrev);
        Object.SetPivot(MPivot);
        Object.SetOffset(0);
    }

    /**
    * FUNCTION - void
    * --------------------------------------------------
    * Begins a for each loop starting from a specified 
    * offset
    */
    void ForEachFrom(Iterator& Object, int Offset) const {
        DLLNode* LNodeID = MPivot->MNext;
        int LIndex = 0;

        while (LIndex < Offset) {
            if (LNodeID->MNext != MPivot) {
                LNodeID = LNodeID->MNext;
            }
            else {
                LNodeID = LNodeID->MNext->MNext;
            }
            LIndex += 1;
        }
        Object.SetNode(LNodeID);
        Object.SetPivot(MPivot);
        Object.SetOffset(0);
    }


    //////////////////////////////////////////////////

    DoubleLinkedList<TItem>& operator = (const DoubleLinkedList<TItem>& rhs) {
        if (this != &rhs) {
            Iterator LIterator;

            Clear();

            for (rhs.ForEachFromFirst(LIterator); LIterator.GetOffset() < rhs.MLength; LIterator.ShiftForward()) {
                InsertAsLast(*LIterator.GetItem());
            }
        }
        return *this;
    }

    TItem& operator [] (int Offset) {
        DLLNode* LNodeID = MPivot->MNext;
        int LIndex = 0;

        while (LIndex < Offset) {
            if (LNodeID->MNext != MPivot) {
                LNodeID = LNodeID->MNext;
            }
            else {
                LNodeID = LNodeID->MNext->MNext;
            }
            LIndex += 1;
        }
        return LNodeID->MItem;
    }

    TItem& operator [] (int Offset) const {
        DLLNode* LNodeID = MPivot->MNext;
        int LIndex = 0;

        while (LIndex < Offset) {
            if (LNodeID->MNext != MPivot) {
                LNodeID = LNodeID->MNext;
            }
            else {
                LNodeID = LNodeID->MNext->MNext;
            }
            LIndex += 1;
        }
        return LNodeID->MItem;
    }
};