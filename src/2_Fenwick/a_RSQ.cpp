//
//  a_RSQ.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 10.05.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <cstdio>
#include <vector>

template<typename DataType, typename SumType = DataType>
class FenwickSumTree
{
private:
    std::vector<SumType> m_data;

public:
	FenwickSumTree(size_t size) : m_data(size, 0)
    {
    }

    void inc(int pos, DataType value)
    {
        for (; pos < m_data.size(); pos |= (pos + 1)) {
            m_data[pos] += value;
        }
    }

	SumType sum(DataType pos)
    {
		SumType result = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
            result += m_data[pos];
        }
        return result;
    }

	SumType sum(int left, int right)
    {
        return sum(right) - sum(left - 1);
    }

    DataType getValue(int pos)
    {
        return static_cast<DataType>(sum(pos) - sum(pos - 1));
    }

	void setValue(int pos, DataType value)
	{
		inc(pos, value - getValue(pos));
	}
};

enum QueryType
{
    Sum = 0,
    Set = 1
};

void doTask2A()
{
    size_t dataSize;
    int queryCount;
    scanf("%d %d", &dataSize, &queryCount);

    FenwickSumTree<int, long long> data(dataSize);
    for (auto i = 0; i < dataSize; ++i) {
        int value;
        scanf("%d", &value);
        data.inc(i, value);
    }

	QueryType queryType = QueryType::Sum;
	int x = 0;
	int y = 0;
    for (auto i = 0; i < queryCount; ++i) {
        scanf("%d %d %d", &queryType, &x, &y);
        if (queryType == QueryType::Sum) {
			printf("%I64d\n", data.sum(x - 1, y - 1));
        } else if (queryType == QueryType::Set) {
			data.setValue(x - 1, y);
        }
    }
}

//int main()
//{
//    doTask2A();
//    return 0;
//}
