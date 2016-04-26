//
//  a_makeHeap.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 26.03.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>

struct NumeredString
{
    int num;
    char str[1000];
};
using NumeredStringList = std::vector<NumeredString>;

void doTask1A();
void heapify(NumeredStringList& list, std::vector<int>& shift);
void heapify(NumeredStringList& list, std::vector<int>& shift, int index);

//int main(int argc, const char* argv[])
//{
//    doTask1A();
//    return 0;
//}

void doTask1A()
{
    int inputSize;
    std::cin >> inputSize;

    NumeredStringList input(inputSize);
    std::vector<int> shift(inputSize);
    char buf[1000];
    for (int i = 0; i < inputSize; ++i) {
        scanf("%s", buf);
        strcpy(input[i].str, buf);
        input[i].num = i;
        shift[i] = i;
    }

    heapify(input, shift);

    for (auto pos : shift) {
        printf("%d\n", pos + 1);
    }
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