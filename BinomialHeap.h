//
// Created by Ivan_Arkhipov on 10.12.2017.
//

#ifndef HEAPS_BINOMIALHEAP_H
#define HEAPS_BINOMIALHEAP_H

#include <vector>
#include "IHeap.h"

class BinomialHeapNode {
public:
    explicit BinomialHeapNode(int value);

    BinomialHeapNode(const BinomialHeapNode &other);

    BinomialHeapNode& operator =(const BinomialHeapNode &other);

    ~BinomialHeapNode();

    bool operator <(const BinomialHeapNode *b) const;

    void Meld(BinomialHeapNode *other);

    void MeldEquals();

    int _value;

    std::vector <BinomialHeapNode *> _children;

    int _k;
};

class BinomialHeap : public IHeap{
public:
    BinomialHeap() = default;

    explicit BinomialHeap(BinomialHeapNode *t);

    explicit BinomialHeap(int root_key);

    ~BinomialHeap() override;

    void Insert(int key) override;

    int GetMin() const override;

    bool Empty() const override;

    void Meld(IHeap *other) override;

    void ExtractMin() override;

    void UpdateMin();
private:
    int _MinIndex;
    std::vector<BinomialHeapNode*> _children;
};

#endif //HEAPS_BINOMIALHEAP_H
