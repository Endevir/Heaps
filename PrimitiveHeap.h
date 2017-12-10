//
// Created by Ivan Arkhipov on 10.12.2017.
//
#ifndef HEAPS_PRIMITIVEHEAP_H
#define HEAPS_PRIMITIVEHEAP_H

#include <vector>
#include "IHeap.h"

class PrimitiveHeap : public IHeap {
public:
    ~PrimitiveHeap() override = default;

    void Insert(int key) override;

    int GetMin() const override;

    bool Empty() const override;

    void Meld(IHeap *other) override;

    void ExtractMin() override;
private:
    std::vector<int> _heap;
};


#endif //HEAPS_PRIMITIVEHEAP_H
