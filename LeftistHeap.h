//
// Created by Ivan_Arkhipov on 10.12.2017.
//
#ifndef HEAPS_LEFTISTHEAP_H
#define HEAPS_LEFTISTHEAP_H

#include "IHeap.h"

struct LeftistHeapNode {
    int _value;
    LeftistHeapNode *l, *r;
    int d;

    LeftistHeapNode();

    explicit LeftistHeapNode(int value);

    ~LeftistHeapNode();
};

class LeftistHeap : public IHeap {
    int GetD(LeftistHeapNode *t);

    LeftistHeapNode *root;

    LeftistHeapNode *Merge(LeftistHeapNode *a, LeftistHeapNode *b);

public:
    LeftistHeap();

    explicit LeftistHeap(int value);

    ~LeftistHeap() override;

    void Meld(IHeap *b) override;

    void Insert(int value) override;

    bool Empty() const override;

    int GetMin() const override;

    void ExtractMin() override;
};


#endif //HEAPS_LEFLeftistHeapNodeISLeftistHeapNodeHEAP_H
