#include <vector>
#include <cstdio>
#include <map>

class FenwickTreeCount
{
private:
	std::vector<std::map<int, int>> m_data;

public:
	FenwickTreeCount(size_t size) : m_data(size)
	{
	}

	void set(size_t pos, int value)
	{
		for (; pos < m_data.size(); pos |= (pos + 1)) {
			if (m_data[pos].find(value) != m_data[pos].end()) {
				++m_data[pos][value];
			} else {
				m_data[pos][value] = 1;
			}
		}
	}

	int countLowerThan(int pos, int value)
	{
		int count = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
			for (auto pair : m_data[pos]) {
				if (pair.first < value) {
					count += pair.second;
				} else {
					break;
				}
			}
		}
		return count;
	}

	int countLowerThan(int left, int right, int value)
	{
		return countLowerThan(right, value) - countLowerThan(left - 1, value);
	}
};

void doTask2C();

//int main()
//{
//	doTask2C();
//	return 0;
//}

void doTask2C()
{
	int dataSize;
	scanf("%d", &dataSize);

	std::vector<int> data(dataSize);
	FenwickTreeCount tree(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		int value;
		scanf("%d", &value);
		data[i] = value;
		tree.set(i, value);
	}

	long long inversionsCount = 0;
	for (auto i = 0; i < dataSize - 1; ++i) {
		inversionsCount += tree.countLowerThan(i + 1, dataSize - 1, data[i]);
	}

	printf("%I64d\n", inversionsCount);
}
