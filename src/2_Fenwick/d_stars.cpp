#include <cstdio>
#include <vector>

template<typename DataType, typename SumType = DataType>
class FenwickSumTree3D
{
	using Vector = std::vector<SumType>;
	using Vector2D = std::vector<Vector>;
	using Vector3D = std::vector<Vector2D>;

private:
	Vector3D m_data;
	size_t m_size;

public:
	FenwickSumTree3D(size_t size) : m_size(size), m_data(size, Vector2D(size, Vector(size, 0)))
	{
	}

	void inc(int x, int y, int z, DataType value)
	{
		for (auto i = x; i < m_size; i |= (i + 1)) {
			for (auto j = y; j < m_size; j |= (j + 1)) {
				for (auto k = z; k < m_size; k |= (k + 1)) {
					m_data[i][j][k] += value;
				}
			}
		}
	}

	SumType sum(int x, int y, int z)
	{
		SumType result = 0;
		for (auto i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (auto j = y; j >= 0; j = (j & (j + 1)) - 1) {
				for (auto k = z; k >= 0; k = (k & (k + 1)) - 1) {
					result += m_data[i][j][k];
				}
			}
		}
		return result;
	}

	SumType sum(int x1, int y1, int z1, int x2, int y2, int z2)
	{
		return
			+ sum(x2,     y2,     z2)
			- sum(x2,     y2,     z1 - 1)
			- sum(x2,     y1 - 1, z2)
			+ sum(x2,     y1 - 1, z1 - 1)
			- sum(x1 - 1, y2,     z2)
			+ sum(x1 - 1, y2,     z1 - 1)
			+ sum(x1 - 1, y1 - 1, z2)
			- sum(x1 - 1, y1 - 1, z1 - 1);
	}
};

enum QueryType
{
	None = 0,
	Change = 1,
	Count = 2,
	Stop = 3
};

void doTask2D()
{
	size_t size;
	scanf("%d", &size);

	FenwickSumTree3D<int> data(size);

	QueryType query = QueryType::None;
	int x1, y1, z1, x2, y2, z2, value;

	while (query != QueryType::Stop) {
		scanf("%d", &query);
		if (query == QueryType::Change) {
			scanf("%d %d %d %d", &x1, &y1, &z1, &value);
			data.inc(x1, y1, z1, value);
		} else if (query == QueryType::Count) {
			scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
			printf("%d\n", data.sum(x1, y1, z1, x2, y2, z2));
		}
	}
}

//int main()
//{
//	doTask2D();
//	return 0;
//}
