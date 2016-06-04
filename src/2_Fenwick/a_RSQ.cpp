//
//  a_RSQ.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 10.05.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <cstdio>
#include <vector>

class FenwickTree
{
private:
    std::vector<long long> m_data;

public:
    FenwickTree(size_t size) : m_data(size, 0)
    {
    }

    void inc(size_t pos, int value)
    {
        for (; pos < m_data.size(); pos |= (pos + 1)) {
            m_data[pos] += value;
        }
    }

    long long sum(int pos)
    {
        long long result = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
            result += m_data[pos];
        }
        return result;
    }

    long long sum(int left, int right)
    {
        return sum(right) - sum(left - 1);
    }

    int getValue(int pos)
    {
        return static_cast<int>(sum(pos) - sum(pos - 1));
    }
};

enum QueryType
{
    Sum = 0,
    Set = 1
};

void doTask2A();

//int main()
//{
//    doTask2A();
//    return 0;
//}

void doTask2A()
{
    int dataSize;
    int queryCount;
    scanf("%d %d", &dataSize, &queryCount);

    FenwickTree data(dataSize);
    for (auto i = 0; i < dataSize; ++i) {
        int value;
        scanf("%d", &value);
        data.inc(i, value);
    }

    std::vector<long long> sums;
    for (auto i = 0; i < queryCount; ++i) {
        int queryType;
        int x;
        int y;
        scanf("%d %d %d", &queryType, &x, &y);

        if (queryType == QueryType::Sum) {
            sums.push_back(data.sum(x - 1, y - 1));
        } else if (queryType == QueryType::Set) {
            auto prevValue = data.getValue(x - 1);
            data.inc(x - 1, y - prevValue);
        }
    }

    for (auto sum : sums) {
        printf("%I64d\n", sum);
    }
}
