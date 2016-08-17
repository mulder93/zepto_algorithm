#include <cstdio>
#include <vector>
#include <algorithm>

class SparseMinTable
{
	using Vector = std::vector<int>;
	using Vector2D = std::vector<Vector>;

private:
	size_t m_width;
	size_t m_height;
	Vector2D m_data;
	Vector m_numbersToTwoPower;
	Vector m_twoPowers;

public:
	SparseMinTable(const Vector& data) : m_width(data.size()), m_numbersToTwoPower(data.size() + 1, 0)
	{
		calcPowers();
		calcHeigth();
		constructTable(std::move(data));
	}

	int getMin(int left, int right)
	{
		if (left > right) {
			std::swap(left, right);
		}
		auto len = right - left + 1;
		auto row = m_numbersToTwoPower[len] - 1;
		return std::min(m_data[row][left], m_data[row][right - m_twoPowers[row] + 1]);
	}

	void print()
	{
		printf("--------------\n");
		for (auto i = 0; i < m_height; ++i) {
			for (auto j = 0; j < m_data[i].size(); ++j) {
				printf("%d ", m_data[i][j]);
			}
			printf("\n");
		}
		printf("--------------\n");
	}

private:
	void calcPowers()
	{
		auto currentPow = 1;
		if (m_numbersToTwoPower.size() > 1) {
			// Must have height '1' for width '1'
			m_numbersToTwoPower[currentPow] = 1;
		}

		m_twoPowers.push_back(1); // 2^0 = 1
		
		for (auto i = 2; i <= m_width; ++i) {
			m_numbersToTwoPower[i] = currentPow;
			if ((i & (i - 1)) == 0) {
				m_twoPowers.push_back(i);
				++currentPow;
			}
		}
	}

	void calcHeigth()
	{
		m_height = m_numbersToTwoPower[m_width];
	}

	void constructTable(const Vector& data)
	{
		if (data.size() == 0) {
			return;
		}

		m_data = Vector2D(m_height);
		m_data[0] = std::move(data);

		for (auto i = 1; i < m_height; ++i) {
			for (auto j = 0; j < m_width; ++j) {
				auto rightJ = j + m_twoPowers[i - 1];
				if (rightJ < m_data[i - 1].size()) {
					m_data[i].push_back(std::min(m_data[i - 1][j], m_data[i - 1][rightJ]));
				} else {
					continue;
				}
			}
		}
	}
};

void doTask3A()
{
	// Read main params
	auto dataSize = 0;
	auto queryCount = 0;
	auto dataItem = 0;
	scanf("%d %d %d", &dataSize, &queryCount, &dataItem);

	// Generate data
	std::vector<int> data(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		data[i] = dataItem;
		dataItem = (23 * dataItem + 21563) % 16714589;
	}

	// Construct sparse table
	SparseMinTable table(std::move(data));

	// Read first query
	auto queryLeft = 0;
	auto queryRight = 0;
	scanf("%d %d", &queryLeft, &queryRight);

	// Generage next queries and results
	auto queryResult = table.getMin(queryLeft - 1, queryRight - 1);
	for (auto i = 1; i < queryCount; ++i) {
		queryLeft = ((17 * queryLeft + 751 + queryResult + 2 * i) % dataSize) + 1;
		queryRight = ((13 * queryRight + 593 + queryResult + 5 * i) % dataSize) + 1;
		queryResult = table.getMin(queryLeft - 1, queryRight - 1);
	}

	// Print last result
	printf("%d %d %d", queryLeft, queryRight, queryResult);
}

//int main()
//{
//	doTask3A();
//	return 0;
//}
