//
//  b_heapSort.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 27.03.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <cmath>

int whileCount = 0;

void doTask1B();
int getMaxChildIndex(std::vector<int>& data, int index, int size);
void heapify(std::vector<int>& data, int index, int size);
void heapify(std::vector<int>& data);

//int main()
//{
//    doTask1B();
//    return 0;
//}

void doTask1B()
{
    int size;
    scanf("%d", &size);

    std::vector<int> input(size);
    for (int i = 0; i < size; ++i) {
        scanf("%d", &input[i]);
    }

    heapify(input);
    int heapSize = static_cast<int>(input.size());
    while (heapSize > 1) {
        std::swap(input[0], input[heapSize - 1]);
        --heapSize;
        heapify(input, 0, heapSize);
    }

    printf("%d\n", whileCount);
}

int getMaxChildIndex(std::vector<int>& data, int index, int size)
{
    int childIndex = 2 * index + 1;
    if (childIndex < size) {
        if (childIndex + 1 < size && data[childIndex + 1] >= data[childIndex]) {
            ++childIndex;
        }
        return childIndex;
    } else {
        return static_cast<int>(size);
    }
}

void heapify(std::vector<int>& data, int index, int size)
{
    int value = data[index];
    int childIndex = getMaxChildIndex(data, index, size);

    while (childIndex < size && data[childIndex] > value) {
        data[index] = data[childIndex];
        index = childIndex;
        childIndex = getMaxChildIndex(data, index, size);

        ++whileCount;
    }

    data[index] = value;
}

void heapify(std::vector<int>& data)
{
    for (int i = std::floor(data.size() / 2) - 1; i >= 0; --i) {
        heapify(data, i, static_cast<int>(data.size()));
    }
}
