//
// Created by Ivan_Arkhipov on 10.12.2017.
//

#ifndef HEAPS_IHEAP_H
#define HEAPS_IHEAP_H

#include <cstdlib>

class IHeap {
public:
    IHeap();

    IHeap(int key);

    virtual void Insert(int key);

    virtual const int GetMin();

    virtual void ExtractMin();
protected:
};


#endif //HEAPS_IHEAP_H
