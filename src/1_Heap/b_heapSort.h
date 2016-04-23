//
//  b_heapSort.h
//  zepto_algorithm
//
//  Created by Boris Tsarev on 23.04.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#pragma once

#include <vector>

namespace heapSort
{

void doTask();

std::vector<int> readInput();
void heapify(std::vector<int>& data, int index, int size);
void heapify(std::vector<int>& data);
int getMaxChildIndex(std::vector<int>& data, int index, int size);

}
