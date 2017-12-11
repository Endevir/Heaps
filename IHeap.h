//
// Created by Ivan Arkhipov on 10.12.2017.
//

#ifndef HEAPS_IHEAP_H
#define HEAPS_IHEAP_H

#include <cstdlib>

class IHeap {
public:
    virtual ~IHeap() = default;

    virtual void Insert(int key) = 0;

    virtual int GetMin() const = 0;

    virtual bool Empty() const = 0;

    virtual void Erase() = 0;

    virtual void Meld(const IHeap *other) = 0;

    virtual void ExtractMin() = 0;
};


#endif //HEAPS_IHEAP_H
