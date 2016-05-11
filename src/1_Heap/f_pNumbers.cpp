//
//  f_pNumbers.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 06/05/16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct GeneratorItem
{
    long long num;
    int index;
    int prime;
    
    GeneratorItem() : num(1), index(-1), prime(1)
    {
    }
    
    long long getValue() const
    {
        return num * prime;
    }
    
    bool operator<(const GeneratorItem& other) const
    {
        return getValue() < other.getValue();
    }
    bool operator>(const GeneratorItem& other) const
    {
        return getValue() > other.getValue();
    }
};

void doTaskF();

int main()
{
    doTaskF();
    return 0;
}

void doTaskF()
{
    int primeCount;
    int searchIndex;
    scanf("%d %d", &primeCount, &searchIndex);
    
    std::priority_queue<GeneratorItem, std::vector<GeneratorItem>, std::greater<GeneratorItem>> generators;
    for (auto i = 0; i < primeCount; ++i) {
        GeneratorItem item;
        scanf("%d", &item.prime);
        generators.push(std::move(item));
    }
    
    std::vector<long long> sequence(searchIndex);
    for (auto i = 0; i < searchIndex; ++i) {
        auto shiftGenerators = [&generators, &sequence]() {
            auto generator = generators.top();
            generators.pop();
            
            ++generator.index;
            generator.num = sequence[generator.index];
            generators.push(generator);
        };
        
        while (i >= 1 && sequence[i - 1] == generators.top().getValue()) {
            shiftGenerators();
        }
        
        sequence[i] = generators.top().getValue();
    }
    
    std::cout << sequence[searchIndex - 1] << std::endl;
}
