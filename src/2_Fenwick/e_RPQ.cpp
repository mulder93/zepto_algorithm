#include <cstdio>
#include <vector>

class FenwickProductTree
{
private:
	std::vector<int> m_data;
    std::vector<int> m_tree;
	int m_module;

private:
	int mod(long long value)
	{
		return value - m_module * (value / m_module);
	}

public:
	FenwickProductTree(size_t size, int module) : m_data(size, 1), m_tree(size, 1), m_module(module)
    {
    }

    void multiply(int pos, int value)
    {
		m_data[pos] = mod(static_cast<long long>(m_data[pos]) * mod(value));
        for (; pos < m_tree.size(); pos |= (pos + 1)) {
            m_tree[pos] = mod(static_cast<long long>(m_tree[pos]) * mod(value));
        }
    }

    int product(int pos)
    {
        int result = 1;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
            result = mod(static_cast<long long>(result) * m_tree[pos]);
        }
        return result;
    }

    int product(int left, int right)
    {
		int result = 1;
		while (right >= left) {
			int next = (right & (right + 1));
			if (next >= left) {
				result = mod(static_cast<long long>(result) * m_tree[right]);
				right = next - 1;
			} else {
				result = mod(static_cast<long long>(result) * m_data[right]);
				--right;
			}
		}
		return result;
    }
};

enum QueryType
{
    Multiply = 1,
    Product = 2
};

void doTask2E()
{
    size_t dataSize;
    int queryCount;
	int module;
    scanf("%d %d %d", &dataSize, &queryCount, &module);

	FenwickProductTree data(dataSize, module);
	QueryType queryType = QueryType::Multiply;
	int x = 0;
	int y = 0;

    for (auto i = 0; i < queryCount; ++i) {
        scanf("%d", &queryType);
        if (queryType == QueryType::Multiply) {
			scanf("%d %d", &x, &y);
			data.multiply(x - 1, y);
        } else if (queryType == QueryType::Product) {
			scanf("%d %d", &x, &y);
			printf("%d\n", data.product(x - 1, y - 1));
        }
    }
}

//int main()
//{
//    doTask2E();
//    return 0;
//}
