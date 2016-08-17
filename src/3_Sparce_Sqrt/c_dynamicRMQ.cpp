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
	}

	void set(int pos, int value)
	{
		auto blockIndex = getBlockIndex(pos);
		auto& block = m_blocks[blockIndex];

		switch (block.state) {
			case BlockState::DirtyData:
				updateBlockData(block);
				m_data[pos] = value;
				block.value = std::min(block.value, value);
				break;

			case BlockState::DirtyBlock:
				m_data[pos] = value;
				break;

			case BlockState::Normal:
				m_data[pos] = value;
				if (value > block.value) {
					block.state = BlockState::DirtyBlock;
				} else {
					block.value = value;
				}
				break;
		}
	}

	void set(int left, int right, int value)
	{
		for (auto i = left; i <= right;) {
			if (isBlockStart(i) && i + m_blockSize - 1 <= right) {
				auto& block = m_blocks[getBlockIndex(i)];
				block.value = value;
				block.state = BlockState::DirtyData;
				i += m_blockSize;
			} else {
				set(i, value);
				++i;
			}
		}
	}

	int getMin(int left, int right)
	{
		auto result = INT_MAX;
		for (auto i = left; i <= right;) {
			auto blockIndex = getBlockIndex(i);
			auto& block = m_blocks[blockIndex];

			if (isBlockStart(i) && i + m_blockSize - 1 <= right) {
				if (block.state == BlockState::DirtyBlock) {
					updateBlock(block);
				}
				result = std::min(result, block.value);
				i += m_blockSize;
			} else {
				if (block.state == BlockState::DirtyData) {
					updateBlockData(block);
				}
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
	enum class BlockState
	{
		Normal,
		DirtyData,
		DirtyBlock
	};

	struct Block
	{
		int value;
		int index;
		BlockState state;

		Block(int value, int index, BlockState state) : value(value), index(index), state(state) { }
	};

	void initBlocks()
	{
		if (m_data.size() > 0) {
			auto sqrt = std::sqrt(m_data.size());
			m_blockTwoPower = std::floor(std::log2(sqrt));
			m_blockSize = std::pow(2, m_blockTwoPower);
		}

		auto extraBlock = (m_data.size() % m_blockSize != 0);
		auto blocksCount = (m_data.size() / m_blockSize) + (extraBlock ? 1 : 0);

		for (auto i = 0; i < blocksCount; ++i) {
			m_blocks.emplace_back(INT_MAX, i, BlockState::DirtyBlock);
		}

		calcBlockMask();
	}

	void updateBlock(Block& block)
	{
		auto startPos = block.index * m_blockSize;
		block.value = INT_MAX;
		for (auto i = startPos; i < startPos + m_blockSize && i < m_data.size(); ++i) {
			block.value = std::min(block.value, m_data[i]);
		}
		block.state = BlockState::Normal;
	}

	void updateBlockData(Block& block)
	{
		auto startPos = block.index * m_blockSize;
		for (auto i = startPos; i < startPos + m_blockSize && i < m_data.size(); ++i) {
			m_data[i] = m_blocks[block.index].value;
		}
		block.state = BlockState::Normal;
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

	std::vector<int> m_data;
	std::vector<Block> m_blocks;
	int m_blockSize;
	int m_blockMask;
	int m_blockTwoPower;
};

enum QueryType
{
	GetMin = 1,
	Set = 2
};

void doTask3C()
{
	auto dataSize = 0;
	scanf("%d", &dataSize);

	std::vector<int> data(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		scanf("%d", &data[i]);
	}

	RootHeuristicMin rootHeuristic(data);
	
	auto queryCount = 0;
	scanf("%d", &queryCount);

	auto queryType = 0;
	auto left = 0;
	auto right = 0;
	auto value = 0;
	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d %d", &queryType, &left, &right);
		if (queryType == GetMin) {
			printf("%d\n", rootHeuristic.getMin(left - 1, right - 1));
		} else {
			scanf("%d", &value);
			rootHeuristic.set(left - 1, right - 1, value);
		}
	}
}

//int main()
//{
//	doTask3C();
//	return 0;
//}
