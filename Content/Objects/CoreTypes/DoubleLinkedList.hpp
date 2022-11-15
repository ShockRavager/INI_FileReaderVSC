#pragma once

// PATH     ->  Content/Objects/CoreTypes
// FILE     ->  DoubleLinkedList.hpp


template<typename TItem>
class DoubleLinkedList {
protected:

    //////////////////////////////////////////////////

    struct DLLNode {

        //////////////////////////////////////////////////

        TItem MItem;
        DLLNode
            * MPrev,
            * MNext;
    };


    //////////////////////////////////////////////////

    DLLNode* MPivot;
    int MLength;


    //////////////////////////////////////////////////

    DLLNode* CreatePivot() {
        DLLNode* LNode = new DLLNode;

        LNode->MPrev = LNode;
        LNode->MNext = LNode;
        return LNode;
    }

    void InsertNode(DLLNode* Node, DLLNode* Prev, DLLNode* Next) {
        Node->MPrev = Prev;
        Node->MNext = Next;
        Prev->MNext = Node;
        Next->MPrev = Node;
    }

    void RemoveNode(DLLNode* Node) {
        Node->MPrev->MNext = Node->MNext;
        Node->MNext->MPrev = Node->MPrev;
        delete Node;
    }

    void ClearHP(DLLNode* Node) {
        if (Node != MPivot) {
            ClearHP(Node->MNext);
            delete Node;
        }
    }

public:

    //////////////////////////////////////////////////

    DoubleLinkedList() :
        MPivot(CreatePivot()),
        MLength(0)
    { 
        MPivot->MPrev = MPivot;
        MPivot->MNext = MPivot;
    }

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

    ~DoubleLinkedList()
    {
        ClearHP(MPivot->MNext);
        delete MPivot;
    }


    //////////////////////////////////////////////////

    class Iterator {
        protected:

        //////////////////////////////////////////////////

        DLLNode
            * MNode,
            * MPivot;
        int MOffset;

    public:

        //////////////////////////////////////////////////

        void SetNode(DLLNode* Node) {
            MNode = Node;
        }

        void SetPivot(DLLNode* Node) {
            MPivot = Node;
        }

        void SetOffset(int Value) {
            MOffset = Value;
        }

        void ShiftForward() {
            if (MNode->MNext != MPivot) {
                MNode = MNode->MNext;
            }
            else {
                MNode = MNode->MNext->MNext;
            }
            MOffset += 1;
        }

        void ShiftReverse() {
            if (MNode->MPrev != MPivot) {
                MNode = MNode->MPrev;
            }
            else {
                MNode = MNode->MPrev->MPrev;
            }
            MOffset += 1;
        }

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

        TItem* GetItem() const {
            return &MNode->MItem;
        }

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

    DLLNode* GetPivot() const {
        return MPivot;
    }

    int GetLength() const {
        return MLength;
    }

    TItem& GetFirst() {
        return MPivot->MNext->MItem;
    }

    TItem& GetFirst() const {
        return MPivot->MNext->MItem;
    }

    TItem& GetLast() {
        return MPivot->MPrev->MItem;
    }

    TItem& GetLast() const {
        return MPivot->MPrev->MItem;
    }

    TItem& GetPivotItem() {
        return MPivot->MItem;
    }

    TItem& GetPivotItem() const {
        return MPivot->MItem;
    }

    void AssignPivotItem(TItem Item) {
        MPivot->MItem = Item;
    }

    void InsertAsFirst(TItem Item) {
        DLLNode* LNode = new DLLNode;

        LNode->MItem = Item;
        InsertNode(LNode, MPivot, MPivot->MNext);
        MLength += 1;
    }

    void InsertAsLast(TItem Item) {
        DLLNode* LNode = new DLLNode;

        LNode->MItem = Item;
        InsertNode(LNode, MPivot->MPrev, MPivot);
        MLength += 1;
    }

    void InsertAt(TItem Item, int Offset) {
        DLLNode
            * LNodeID = MPivot,
            * LNode = new DLLNode;
        int LIndex = 0;

        while (LIndex < Offset) {
            LNodeID = LNodeID->MNext;
            LIndex += 1;
        }
        LNode->MItem = Item;
        InsertNode(LNode, LNodeID, LNodeID->MNext);
        MLength += 1;
    }

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

    void RemoveAt(int Offset) {
        DLLNode* LNodeID = MPivot;
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

    void Clear() {
        ClearHP(MPivot->MNext);
        delete MPivot;
        MPivot = CreatePivot();
        MLength = 0;
    }

    void ForEachFromFirst(Iterator& Object) const {
        Object.SetNode(MPivot->MNext);
        Object.SetPivot(MPivot);
        Object.SetOffset(0);
    }

    void ForEachFromLast(Iterator& Object) const {
        Object.SetNode(MPivot->MPrev);
        Object.SetPivot(MPivot);
        Object.SetOffset(0);
    }

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
        DLLNode* LNodeID = MPivot;
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
        DLLNode* LNodeID = MPivot;
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