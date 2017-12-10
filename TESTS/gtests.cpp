//
// Created by Ivan Arkhipov on 10.12.2017.
//

#include <iostream>
#include <algorithm>
#include <vector>

#include "../PrimitiveHeap.h"
#include "../BinomialHeap.h"
#include "../SkewHeap.h"
#include "../LeftistHeap.h"
#include "../IHeap.h"

#include "gtest\gtest.h"
#include <iterator>
#include <fstream>

void GenerateTest(int &type, int &index, int &indexse, int MaximumHeaps) {
    type = rand() % 4;
    index = rand() % MaximumHeaps;
    indexse = rand() % MaximumHeaps;
    if (index == indexse)++indexse;
    if (indexse == MaximumHeaps)indexse -= 2;
}

std::ifstream GenerateFile(int MaximumHeaps, int CntOperations) {
    static int FileNumber = 0;
    ++FileNumber;
    std::ofstream ofs(std::to_string(FileNumber) + ".txt");
    std::vector<int> NowSizes(MaximumHeaps, 0);
    std::set<int> PosGoodHeaps;
    for (int it = 0; it < MaximumHeaps; ++it)PosGoodHeaps.insert(it);
    ofs << CntOperations << std::endl;
    for (int it = 0; it < CntOperations; ++it) {
        int type, index, indexse;
        do {
            GenerateTest(type, index, indexse, MaximumHeaps);
            if (type == 0)
                break;
            if ((type == 1 || type == 2) && PosGoodHeaps.find(index) != PosGoodHeaps.end() && NowSizes[index] != 0)
                break;
            if (type == 3 && PosGoodHeaps.find(index) != PosGoodHeaps.end() &&
                PosGoodHeaps.find(indexse) != PosGoodHeaps.end())
                break;
        } while (true);
        if (type == 0) {
            ofs << "Insert " << index << " " << rand() << std::endl;
            ++NowSizes[index];
        }
        if (type == 1) {
            ofs << "GetMin " << index << std::endl;
        }
        if (type == 2) {
            ofs << "ExtractMin " << index << std::endl;
            --NowSizes[index];
        }
        if (type == 3) {
            ofs << "Meld " << index << " " << indexse << std::endl;
            NowSizes[index] += NowSizes[indexse];
            PosGoodHeaps.erase(indexse);
        }
    }
    ofs.close();
    return std::ifstream(std::to_string(FileNumber) + ".txt");
}

void TestHeap(std::ifstream ifs, std::vector<IHeap *> &FirstHeaps, std::vector<IHeap *> &SecondHeaps) {
    int CntOperations;
    ifs >> CntOperations;

    for (int it = 0; it < CntOperations; ++it) {
        std::string type;
        int index, indexse, value;
        ifs >> type >> index;
        if (type == "Insert") {
            ifs >> value;
            ASSERT_NO_THROW(FirstHeaps[index]->Insert(value));
            ASSERT_NO_THROW(SecondHeaps[index]->Insert(value));
        }

        if (type == "GetMin") {
            ASSERT_EQ(SecondHeaps[index]->GetMin(), FirstHeaps[index]->GetMin());
        }
        if (type == "ExtractMin") {
            ASSERT_EQ(SecondHeaps[index]->GetMin(), FirstHeaps[index]->GetMin());
            SecondHeaps[index]->ExtractMin();
            FirstHeaps[index]->ExtractMin();
        }
        if (type == "Meld") {
            ifs >> indexse;
            ASSERT_NO_THROW(FirstHeaps[index]->Meld(FirstHeaps[indexse]));
            ASSERT_NO_THROW(SecondHeaps[index]->Meld(SecondHeaps[indexse]));
        }
    }
}

template<class HeapType1, class HeapType2>
void StartTesting(int CntOperations, size_t MaximumHeaps, int CntTests) {
    for (int i = 0; i < CntTests; i++) {
        std::vector<IHeap *> FirstHeaps(MaximumHeaps);
        std::vector<IHeap *> SecondHeaps(MaximumHeaps);

        for (int i = 0; i < MaximumHeaps; ++i) {
            FirstHeaps[i] = new HeapType1();
            SecondHeaps[i] = new HeapType2();
        }

        TestHeap(GenerateFile(MaximumHeaps, CntOperations), FirstHeaps, SecondHeaps);

        for (int i = 0; i < MaximumHeaps; ++i) {
            delete FirstHeaps[i];
            delete SecondHeaps[i];
        }
    }
}


TEST(BinomialHeapTest, FullTest) {
    StartTesting<BinomialHeap, PrimitiveHeap>(30000, 1000, 10);
}

TEST(LeftistHeapTest, FullTest) {
    StartTesting<LeftistHeap, PrimitiveHeap>(30000, 1000, 10);
}

TEST(SkewHeapTest, FullTest) {
    StartTesting<SkewHeap, PrimitiveHeap>(30000, 1000, 10);
}