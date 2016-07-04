#include <cstdio>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

class RootHeuristicMin
{
public:
	RootHeuristicMin(std::vector<int> data) : m_data(std::move(data)), m_blockSize(0), m_blockMask(0)
	{
		initBlocks();
		calcBlockMask();
	}

	void set(int pos, int value)
	{
		m_data[pos] = value;
		m_blocks[getBlockIndex(pos)] = { std::min(value, m_blocks[getBlockIndex(pos)].min), false };
	}

	void set(int left, int right, int value)
	{

	}

	int getMin(int left, int right)
	{
		auto result = INT_MAX;
		for (auto i = left; i <= right;) {
			if (isBlockStart(i) && i + m_blockSize - 1 <= right) {
				result = std::min(result, m_blocks[getBlockIndex(i)].min);
				i += m_blockSize;
			} else {
				result = std::min(result, m_data[i]);
				++i;
			}
		}
		return result;
	}

	void print()
	{
		printf("Block size: %d\n", m_blockSize);
		printf("Blocks count: %d\n", m_blocks.size());
		for (auto i = 0; i < m_data.size(); ++i) {
			if (isBlockStart(i)) {
				printf("\n");
			}
			printf("%d ", m_data[i]);
		}
		printf("\n");
	}

private:
	void initBlocks()
	{
		if (m_data.size() > 0) {
			auto sqrt = std::sqrt(m_data.size());
			m_blockTwoPower = std::floor(std::log2(sqrt));
			m_blockSize = std::pow(2, m_blockTwoPower);
		}
		
		for (auto i = 0; i < m_data.size(); i += m_blockSize) {
			auto blockMin = INT_MAX;
			for (auto j = i; j < i + m_blockSize && j < m_data.size(); ++j) {
				blockMin = std::min(blockMin, m_data[j]);
			}
			m_blocks.push_back({ blockMin, false });
		}
	}

	void calcBlockMask()
	{
		auto twoPowerValue = 1;
		while (m_blockMask < m_blockSize) {
			m_blockMask += twoPowerValue;
			twoPowerValue <<= 1;
		}
		m_blockMask -= (twoPowerValue >> 1);
	}

	bool isBlockStart(int pos)
	{
		return (pos & m_blockMask) == 0;
	}

	int getBlockIndex(int pos)
	{
		return (pos >> m_blockTwoPower);
	}

private:
	struct Block
	{
		int min;
		bool dirty;
	};

	std::vector<int> m_data;
	std::vector<Block> m_blocks;
	int m_blockSize;
	int m_blockMask;
	int m_blockTwoPower;
};

void doTask3C()
{
	RootHeuristicMin rootHeuristic({ 3, 5, 3, 6, 7, 4, 3, 5, 7, 7, 1, 7, 12, 5, 7, 1, 0 });
	rootHeuristic.print();
	printf("Min 0 - 16: %d", rootHeuristic.getMin(0, 16));

	auto stop = 0;
	scanf("%d", &stop);
}

int main()
{
	doTask3C();
	return 0;
}
