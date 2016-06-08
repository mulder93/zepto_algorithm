#include <cstdio>
#include <climits>
#include <algorithm>
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

void doTask2C()
{
	size_t dataSize;
	scanf("%d", &dataSize);

	const int maxValue = 1000000;

	FenwickSumTree<int> data(maxValue + 1);
	auto value = 0;
	long long inverstionsCount = 0;
	for (auto i = 0; i < dataSize; ++i) {
		scanf("%d", &value);
		data.inc(maxValue - value, 1);
		inverstionsCount += data.sum(maxValue - value - 1);
	}

	printf("%I64d", inverstionsCount);
}

//int main()
//{
//	doTask2C();
//	return 0;
//}
