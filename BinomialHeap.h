//
// Created by kikab on 10.12.2017.
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
};

class BinomialHeap : public IHeap{
public:
    BinomialHeap();

    explicit BinomialHeap(int root_key);

    ~BinomialHeap() override;

    void Insert(int key) override;

    int GetMin() const override;

    bool Empty() const override;

    void Erase() override;

    void Meld(const IHeap *other) override;

    void ExtractMin() override;

private:
    BinomialHeapNode *_root;
};

#endif //HEAPS_BINOMIALHEAP_H
