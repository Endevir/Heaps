//
// Created by kikab on 10.12.2017.
//

#include <cassert>
#include <algorithm>
#include "BinomialHeap.h"


BinomialHeapNode::BinomialHeapNode(int value): _value(value), _children(std::vector<BinomialHeapNode*>(0)) {}

BinomialHeapNode::BinomialHeapNode(const BinomialHeapNode &other) {
    if (this == &other)
        return;
    _value = other._value;
    _children.resize(0);
    for (auto &child : other._children)
        _children.emplace_back(new BinomialHeapNode(*child));
}

BinomialHeapNode& BinomialHeapNode::operator =(const BinomialHeapNode &other) {
    if (this == &other)
        return *this;
    _value = other._value;
    for (auto &child : _children)
        delete child;
    _children.resize(0);
    for (auto &child : other._children)
        _children.emplace_back(new BinomialHeapNode(*child));
    return *this;
}

BinomialHeapNode::~BinomialHeapNode() {
    for (auto &child : _children)
        delete child;
}

bool BinomialHeapNode::operator <(const BinomialHeapNode *b) const {
    return _children.size() > b->_children.size();
}

void BinomialHeapNode::Meld(BinomialHeapNode *other) {
    if (_value <= other->_value) {
        _children.insert(
            std::upper_bound(_children.begin(), _children.end(), other),
            new BinomialHeapNode(*other)
        );
        MeldEquals();
    } else {
        other->Meld(this);
        *this = *other;
    }
}

void BinomialHeapNode::MeldEquals() {
    size_t i = _children.size() - 1;
    for (; i > 0; i--) {
        auto current_child = _children[i];
        auto prev_child = _children[i - 1];
        if (current_child->_children.size() != prev_child->_children.size()) {
            _children.resize(i + 1);
            break;
        }
        prev_child->Meld(current_child);
        if (i == 0)
            _children.resize(1);
    }
}


BinomialHeap::BinomialHeap(): _root(nullptr) {}

BinomialHeap::BinomialHeap(int root_key): _root(new BinomialHeapNode(root_key)) {}

BinomialHeap::~BinomialHeap() {
    delete _root;
}

void BinomialHeap::Insert(int key) {
    auto newNode = dynamic_cast<IHeap *>(new BinomialHeap(key));
    Meld(newNode);
}

int BinomialHeap::GetMin() const {
    assert(!Empty());
    return _root->_value;
}

bool BinomialHeap::Empty() const {
    return _root == nullptr;
}

void BinomialHeap::Erase() {
    delete _root;
    _root = nullptr;
}

void BinomialHeap::Meld(const IHeap *other) {
    auto _other = dynamic_cast<const BinomialHeap *>(other);
    if (_root == nullptr) {
        _root = new BinomialHeapNode(*_other->_root);
        return;
    }
    _root->Meld(_other->_root);
}

void BinomialHeap::ExtractMin() {
    assert(_root != nullptr);
    if (_root->_children.empty()) {
        delete _root;
        return;
    }
    auto new_root = new BinomialHeapNode(*_root->_children[0]);
    for (size_t i = 1; i < _root->_children.size(); i++) {
        new_root->Meld(_root->_children[i]);
    }
    delete _root;
    _root = new_root;
}

