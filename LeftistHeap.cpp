//
// Created by Ivan_Arkhipov on 10.12.2017.
//

#include "LeftistHeap.h"

LeftistHeapNode::LeftistHeapNode() : _value(0), l(nullptr), r(nullptr), d(1) {}

LeftistHeapNode::LeftistHeapNode(int value) : _value(value), l(nullptr), r(nullptr), d(1) {}

LeftistHeapNode::~LeftistHeapNode() {
    delete l;
    delete r;
}

int LeftistHeap::GetD(LeftistHeapNode *t) {
    if (t != nullptr)
        return t->d;
    else
        return 0;
}

LeftistHeapNode *LeftistHeap::Merge(LeftistHeapNode *a, LeftistHeapNode *b) {
    if (!a)
        return b;
    if (!b)
        return a;
    if (a->_value > b->_value)
        std::swap(a, b);

    a->r = Merge(a->r, b);

    if (GetD(a->r) > GetD(a->l))
        std::swap(a->l, a->r);

    a->d = GetD(a->r) + 1;
    return a;
}

LeftistHeap::LeftistHeap() : root(nullptr) {}

LeftistHeap::LeftistHeap(int value) : root(new LeftistHeapNode(value)) {}

LeftistHeap::~LeftistHeap() {
    delete root;
}

void LeftistHeap::Meld(IHeap *b) {
    auto *b_ = dynamic_cast<LeftistHeap *>(b);
    root = Merge(root, b_->root);
    b_->root = nullptr;
}

void LeftistHeap::Insert(int value) {
    root = Merge(root, new LeftistHeapNode(value));
}

bool LeftistHeap::Empty() const {
    return root == nullptr;
}

int LeftistHeap::GetMin() const {
    assert(!Empty());
    return root->_value;
}

void LeftistHeap::ExtractMin() {
    LeftistHeapNode *tmp = Merge(root->l, root->r);
    root->l = root->r = nullptr;
    delete root;
    root = tmp;
}


