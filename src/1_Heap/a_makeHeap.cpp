//
//  a_makeHeap.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 23.04.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include "a_makeHeap.h"
#include <cstdio>
#include <cstring>
#include <cmath>

namespace makeHeap
{

void doTask()
{
    auto input = readInput();
    std::vector<int> shift(input.size());
    for (int i = 0; i < shift.size(); ++i) {
        shift[i] = i;
    }

    heapify(input, shift);
    for (auto pos : shift) {
        printf("%d\n", pos + 1);
    }
}

NumeredStringList readInput()
{
    int inputSize;
    scanf("%d", &inputSize);

    NumeredStringList input(inputSize);
    for (int i = 0; i < inputSize; ++i) {
        scanf("%s", input[i].str);
        input[i].num = i;
    }

    return input;
}

void heapify(NumeredStringList& list, std::vector<int>& shift)
{
    if (list.size() > 1) {
        for (auto i = std::floor(list.size() / 2) - 1; i >= 0; --i) {
            heapify(list, shift, i);
        }
    }
}

void heapify(NumeredStringList& list, std::vector<int>& shift, int index)
{
    while (2 * index + 1 < list.size()) {
        int childIndex = 2 * index + 1;
        if (childIndex + 1 < list.size() && strcmp(list[childIndex + 1].str, list[childIndex].str) > 0) {
            ++childIndex;
        }
        if (strcmp(list[childIndex].str, list[index].str) > 0) {
            std::swap(list[childIndex], list[index]);
            std::swap(shift[list[childIndex].num], shift[list[index].num]);
            index = childIndex;
        } else {
            break;
        }
    }
}

}
