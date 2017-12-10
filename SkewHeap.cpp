//
// Created by Ivan_Arkhipov on 10.12.2017.
//
#include "SkewHeap.h"


SkewHeapNode::SkewHeapNode() :value(0), l(nullptr), r(nullptr) {}

SkewHeapNode::SkewHeapNode(int value) : value(value), l(nullptr), r(nullptr) {}

SkewHeapNode::~SkewHeapNode() {
    delete l;
    delete r;
}


SkewHeapNode* SkewHeap::Merge(SkewHeapNode *a, SkewHeapNode *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    if (a->value > b->value)
        std::swap(a, b);

    a->r = Merge(a->r, b);
    std::swap(a->r, a->l);

    return a;
}

SkewHeap::SkewHeap() :root(nullptr) {}

SkewHeap::SkewHeap(int value) : root(new SkewHeapNode(value)) {}

SkewHeap::~SkewHeap() {
    delete root;
}

void SkewHeap::Meld(IHeap * b) {
    auto _b = dynamic_cast<SkewHeap*>(b);
    root = Merge(root, _b->root);
    _b->root = nullptr;
}

void SkewHeap::Insert(int value) {
    root = Merge(root, new SkewHeapNode(value));
}

int SkewHeap::GetMin() const {
    assert(!Empty());
    return root->value;
}

bool SkewHeap::Empty() const {
    return root == nullptr;
}

void SkewHeap::ExtractMin() {
    SkewHeapNode * tmp = Merge(root->l, root->r);
    root->l = root->r = 0;
    delete root;
    root = tmp;
}
