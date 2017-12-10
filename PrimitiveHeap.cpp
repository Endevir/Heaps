//
// Created by Ivan_Arkhipov on 10.12.2017.
//
#include "PrimitiveHeap.h"
#include <algorithm>
#include <cassert>

void PrimitiveHeap::Insert(int key) {
    _heap.push_back(key);
    std::sort(_heap.begin(), _heap.end());
}

int PrimitiveHeap::GetMin() const {
    assert(!_heap.empty());
    return _heap[0];
}

bool PrimitiveHeap::Empty() const {
    return _heap.empty();
}

void PrimitiveHeap::Meld(IHeap *other) {
    auto b = dynamic_cast<const PrimitiveHeap *>(other);
    _heap.insert(_heap.end(), b->_heap.begin(), b->_heap.end());
    std::sort(_heap.begin(), _heap.end());
}

void PrimitiveHeap::ExtractMin() {
    assert(!_heap.empty());
    std::swap(_heap[0], _heap[_heap.size() - 1]);
    _heap.resize(_heap.size() - 1);
    std::sort(_heap.begin(), _heap.end());
}
