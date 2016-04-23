//
//  a_makeHeap.h
//  zepto_algorithm
//
//  Created by Boris Tsarev on 23.04.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#pragma once

#include <vector>

namespace makeHeap
{

struct NumeredString
{
    int num;
    char str[1000];
};

using NumeredStringList = std::vector<NumeredString>;

void doTask();

NumeredStringList readInput();
void heapify(NumeredStringList& list, std::vector<int>& shift);
void heapify(NumeredStringList& list, std::vector<int>& shift, int index);

}
