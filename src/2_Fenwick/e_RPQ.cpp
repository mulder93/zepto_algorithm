#include <cstdio>
#include <vector>

class FenwickTreeProduct
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
	FenwickTreeProduct(size_t size, int module) : m_data(size, 1), m_tree(size, 1), m_module(module)
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

void doTask2E();

//int main()
//{
//    doTask2E();
//    return 0;
//}

void doTask2E()
{
    int dataSize;
    int queryCount;
	int module;
    scanf("%d %d %d", &dataSize, &queryCount, &module);

    FenwickTreeProduct data(dataSize, module);
    for (auto i = 0; i < queryCount; ++i) {
        QueryType queryType;
        scanf("%d", &queryType);

        if (queryType == QueryType::Multiply) {
			int pos;
			int value;
			scanf("%d %d", &pos, &value);
			data.multiply(pos - 1, value);
        } else if (queryType == QueryType::Product) {
			int left;
			int right;
			scanf("%d %d", &left, &right);
			printf("%d\n", data.product(left - 1, right - 1));
        }
    }
}
