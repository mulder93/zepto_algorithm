//
//  b_segmentUpdates.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 13.05.16.
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

template<typename DataType>
class RangeUpdatableVector
{
private:
	FenwickSumTree<DataType> m_data;

public:
	RangeUpdatableVector(size_t size) : m_data(size)
	{
	}

	DataType getValue(int pos)
	{
		return m_data.sum(0, pos);
	}

	void inc(int left, int right, DataType value)
	{
		m_data.inc(left, value);
		m_data.inc(right + 1, -value);
	}

	void inc(int pos, DataType value)
	{
		inc(pos, pos, value);
	}
};

enum QueryType
{
	Update = 1,
	Get = 2
};

void doTask2B()
{
	size_t dataSize;
	int queryCount;
	scanf("%d %d", &dataSize, &queryCount);

	RangeUpdatableVector<int> data(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		int value;
		scanf("%d", &value);
		data.inc(i, value);
	}

	QueryType queryType = QueryType::Update;
	int x = 0;
	int y = 0;
	int z = 0;

	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d", &queryType);
		if (queryType == QueryType::Update) {
			scanf("%d %d %d", &x, &y, &z);
			data.inc(x - 1, y - 1, z);
		}
		else if (queryType == QueryType::Get) {
			scanf("%d", &x);
			printf("%d\n", data.getValue(x - 1));
		}
	}
}

//int main()
//{
//	doTask2B();
//	return 0;
//}
