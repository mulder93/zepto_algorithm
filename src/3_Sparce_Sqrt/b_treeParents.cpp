#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

class SparceTree
{
	using Vector = std::vector<int>;
	using Vector2D = std::vector<Vector>;

	struct PowerOfTwo
	{
		int power;
		int value;
	};

private:
	size_t m_width;
	size_t m_height;
	Vector2D m_data;
	Vector m_twoPowers;
	std::vector<PowerOfTwo> m_twoComponents;

public:
	static const int NO_PARENT = -1;

public:
	SparceTree(const Vector& data) : m_width(data.size())
	{
		calcPowers();
		calcHeigth();
		constructTree(data);
	}

	int getParent(int node, int height)
	{
		auto currentNode = node;
		auto powerOfTwoComponent = 0;
		auto power = 0;

		while (height != 0) {
			powerOfTwoComponent = m_twoComponents[height].value;
			power = m_twoComponents[height].power;
			if (m_data[power][currentNode] != NO_PARENT) {
				currentNode = m_data[power][currentNode];
				height -= powerOfTwoComponent;
			} else {
				currentNode = -1;
				break;
			}
		}

		return currentNode;
	}

	void print()
	{
		printf("--------------\n");
		for (auto i = 0; i < m_height; ++i) {
			for (auto j = 0; j < m_data[i].size(); ++j) {
				printf("%d\t", m_data[i][j]);
			}
			printf("\n");
		}
		printf("--------------\n");
	}

private:
	void calcPowers()
	{
		auto currentPow = 1;
		m_twoPowers.push_back(1); // 2^0 = 1
		for (auto i = 2; i <= m_width; ++i) {
			if ((i & (i - 1)) == 0) {
				m_twoPowers.push_back(i);
				++currentPow;
			}
		}

		m_twoComponents = std::vector<PowerOfTwo>(m_width + 1, { 0, 1 });
		auto twoPower = 0;
		auto twoValue = 1;
		for (auto i = 2; i <= m_width; ++i) {
			if ((i & (i - 1)) == 0) {
				++twoPower;
				twoValue *= 2;
			}
			m_twoComponents[i] = { twoPower, twoValue };
		}
	}

	void calcHeigth()
	{
		if (m_width >= 2) {
			m_height = std::ceil(std::log2(m_width));
		} else if (m_width == 1) {
			m_height = 1;
		} else {
			m_height = 0;
		}
	}

	void constructTree(const Vector& data)
	{
		m_data = Vector2D(m_height, Vector(m_width));
		m_data[0] = data;

		auto row = 1;
		while (row < m_twoPowers.size() && m_twoPowers[row] < m_width) {
			for (auto i = 0; i < m_width; ++i) {
				if (m_data[row - 1][i] == NO_PARENT) {
					m_data[row][i] = NO_PARENT;
				} else {
					m_data[row][i] = m_data[row - 1][m_data[row - 1][i]];
				}
			}
			++row;
		}
	}
};

void doTask3B()
{
	// Get params
	auto nodeCount = 0;
	auto queryCount = 0;
	scanf("%d %d", &nodeCount, &queryCount);

	// Read tree
	std::vector<int> data(nodeCount + 1);
	data[0] = SparceTree::NO_PARENT;
	for (auto i = 1; i < data.size() - 1; ++i) {
		scanf("%d", &data[i]);
	}
	SparceTree tree(data);

	// Queries
	auto node = 0;
	auto height = 0;

	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d", &node, &height);
		printf("%d ", tree.getParent(node, height));
	}
}

//int main()
//{
//	doTask3B();
//	return 0;
//}
