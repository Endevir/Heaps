//
// Created by kikab on 10.12.2017.
//

#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>

#include "BinomialHeap.h"


BinomialHeapNode::BinomialHeapNode(int value) : _value(value), _children(std::vector<BinomialHeapNode *>(0)), _k(0) {}

BinomialHeapNode::BinomialHeapNode(const BinomialHeapNode &other) {
    if (this == &other)
        return;
    _value = other._value;
    _children.resize(0);
    for (auto &child : other._children)
        _children.emplace_back(new BinomialHeapNode(*child));
}

BinomialHeapNode &BinomialHeapNode::operator=(const BinomialHeapNode &other) {
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

bool BinomialHeapNode::operator<(const BinomialHeapNode *b) const {
    return _k > b->_k;
}

void BinomialHeapNode::Meld(BinomialHeapNode *other) {
    assert(_k == other->_k);

    if (_value <= other->_value) {
        _k++;
        _children.insert(
                std::upper_bound(_children.begin(), _children.end(), other),
                new BinomialHeapNode(*other)
        );
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

struct Comparator {
    bool operator()(BinomialHeapNode *one, BinomialHeapNode *another) const {
        return one->_k < another->_k;
    }
};

BinomialHeap::BinomialHeap(int root_key) {
    _children.emplace_back(new BinomialHeapNode(root_key));
    _MinIndex = 0;
}

BinomialHeap::~BinomialHeap() {
    for (auto &i : _children)
        delete i;
}

void BinomialHeap::Insert(int key) {
    auto i = new BinomialHeap(key);
    Meld(i);
}

int BinomialHeap::GetMin() const {
    assert(!Empty());
    return _children[_MinIndex]->_value;
}

bool BinomialHeap::Empty() const {
    return _children.empty();
}

void BinomialHeap::Meld(IHeap *other) {
    auto _other = dynamic_cast<BinomialHeap *>(other);
    std::vector<BinomialHeapNode *> _buffer;
    std::merge(_children.begin(), _children.end(), _other->_children.begin(),
               _other->_children.end(), back_inserter(_buffer), Comparator());
    _children.clear();

    for (size_t i = 0; i < _buffer.size(); ++i) {
        if (i + 1 == _buffer.size() || _buffer[i]->_k != _buffer[i + 1]->_k ||
            (i + 2 < _buffer.size() && _buffer[i]->_k == _buffer[i + 1]->_k &&
             _buffer[i + 1]->_k == _buffer[i + 2]->_k)) {
            _children.push_back(_buffer[i]);
        } else {
            _buffer[i + 1]->Meld(_buffer[i]);
        }
    }
    _other->_children.clear();
    UpdateMin();
}

void BinomialHeap::ExtractMin() {
    BinomialHeapNode *PosMin = _children[_MinIndex];
    _children.erase(_children.begin() + _MinIndex);
    Meld(new BinomialHeap(PosMin));
    delete PosMin;
}

void BinomialHeap::UpdateMin() {
    _MinIndex = 0;
    for (size_t i = 1; i < _children.size(); ++i) {
        if (_children[_MinIndex]->_value > _children[i]->_value)
            _MinIndex = i;
    }
}

BinomialHeap::BinomialHeap(BinomialHeapNode *t) {
    _children = t->_children;
    t->_children.clear();
}

