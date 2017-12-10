//
// Created by Ivan_Arkhipov on 10.12.2017.
//

#ifndef HEAPS_SKEWHEAP_H
#define HEAPS_SKEWHEAP_H

#include <algorithm>
#include <cassert>
#include "IHeap.h"

struct SkewHeapNode {
    int _value;
    SkewHeapNode * l, *r;

    SkewHeapNode();
    
    explicit SkewHeapNode(int value);
    
    ~SkewHeapNode();
};

class SkewHeap :public IHeap {
    SkewHeapNode * root;
private:
    SkewHeapNode* Merge(SkewHeapNode *a, SkewHeapNode *b);
            
public:
    SkewHeap();

    explicit SkewHeap(int value);

    ~SkewHeap() override;

    void Meld(IHeap * b) override;

    void Insert(int value) override;

    int GetMin() const override;

    bool Empty() const override;

    void ExtractMin() override;
};

#endif //HEAPS_SKEWHEAP_H
