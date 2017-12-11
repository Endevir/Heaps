//
// Created by Ivan Arkhipov on 10.12.2017.
//
#include <gtest/gtest.h>
#include <ctime>
#include <random>

#include "../IHeap.h"
#include "../BinomialHeap.h"
#include "../PrimitiveHeap.h"

enum HEAP_TYPE {
    PRIMITIVE_HEAP = 0,
    BINOMIAL_HEAP = 0
};

HEAP_TYPE TEST_TYPES[] = {BINOMIAL_HEAP};

class TestHeap : public ::testing::Test {
protected:
    IHeap *CreateHeap(HEAP_TYPE type) {
        switch (type) {
            case BINOMIAL_HEAP:
                return dynamic_cast<IHeap *>(new BinomialHeap());
            default:
                return dynamic_cast<IHeap *>(new PrimitiveHeap());
        }
    }

    std::vector<int> GenerateRandomNumbers(int num) {
        srand(time(0));
        std::vector<int> nums(num);
        for (auto &i : nums)
            i = rand();
        return nums;
    }

};


TEST_F(TestHeap, test_insert) {
    const size_t amount_of_inserts = 100000;
    auto nums = GenerateRandomNumbers(amount_of_inserts);

    for (auto i : TEST_TYPES) {
        auto primitive_heap = CreateHeap(PRIMITIVE_HEAP);
        auto test_heap = CreateHeap(i);

        for (auto j : nums) {
            primitive_heap->Insert(j);
            test_heap->Insert(j);
            ASSERT_EQ(primitive_heap->GetMin(), test_heap->GetMin());
        }

        delete primitive_heap;
        delete test_heap;
    }
}


TEST_F(TestHeap, test_extract_min) {
    const size_t amount_of_inserts = 1;
    auto nums = GenerateRandomNumbers(amount_of_inserts);
    std::cout << nums[0] << std::endl;

    for (auto i : TEST_TYPES) {
        auto primitive_heap = CreateHeap(PRIMITIVE_HEAP);
        auto test_heap = CreateHeap(i);

        for (auto j : nums) {
            primitive_heap->Insert(j);
            test_heap->Insert(j);
            ASSERT_EQ(primitive_heap->GetMin(), test_heap->GetMin());
        }

        while (!primitive_heap->Empty()) {
            //ASSERT_EQ(primitive_heap->GetMin(), test_heap->GetMin());
            primitive_heap->ExtractMin();
            test_heap->ExtractMin();
        }

        delete primitive_heap;
        delete test_heap;
    }
}

TEST_F(TestHeap, test_meld) {
    const size_t amount_of_inserts = 100000;
    auto nums = GenerateRandomNumbers(amount_of_inserts);
    auto nums2 = GenerateRandomNumbers(amount_of_inserts);

    for (auto i : TEST_TYPES) {
        auto primitive_heap = CreateHeap(PRIMITIVE_HEAP);
        auto primitive_heap2 = CreateHeap(PRIMITIVE_HEAP);

        auto test_heap = CreateHeap(i);
        auto test_heap2 = CreateHeap(i);

        for (auto j : nums) {
            primitive_heap->Insert(j);
            test_heap->Insert(j);
        }

        for (auto j : nums2) {
            primitive_heap2->Insert(j);
            test_heap2->Insert(j);
        }

        primitive_heap->Meld(primitive_heap2);
        test_heap->Meld(test_heap2);

    }
}


