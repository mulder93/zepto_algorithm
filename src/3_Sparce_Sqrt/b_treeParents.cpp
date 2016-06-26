#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

//class PowerOfTwoUtils
//{
//private:
//	int m_maxValue;
//	std::map<int, int> m_powers;
//
//public:
//	PowerOfTwoUtils(int maxValue) : m_maxValue(maxValue)
//	{
//		fillPowers();
//	}
//
//	static bool isPowerOfTwo(int value)
//	{
//		return (value & (value - 1)) == 0;
//	}
//
//	int getMaxPowerOfTwoComponent(int value)
//	{
//		if (value > 0) {
//			if (isPowerOfTwo(value)) {
//				return value;
//			} else {
//				return (*(--m_powers.lower_bound(value))).first;
//			}
//		} else {
//			return 0;
//		}
//	}
//
//	int getPowerForValue(int value)
//	{
//		if (m_powers.find(value) != m_powers.end()) {
//			return m_powers[value];
//		} else {
//			return 0;
//		}
//		
//	}
//
//private:
//	void fillPowers()
//	{
//		auto power = 0;
//		auto powerValue = 1;
//		while (power <= m_maxValue) {
//			m_powers[powerValue] = power;
//			++power;
//			powerValue *= 2;
//		}
//	}
//};

void doTask3B()
{
	using Vector = std::vector<int>;
	using Vector2D = std::vector<Vector>;

	// Get params
	auto nodeCount = 0;
	auto queryCount = 0;
	scanf("%d %d", &nodeCount, &queryCount);

	// Read tree
	Vector2D tree(nodeCount);
	int firstParent = 0;
	for (auto i = 1; i < nodeCount; ++i) {
		scanf("%d", &firstParent);
		tree[i].push_back(firstParent);
	}

	// Save info about parents
	auto height = 0;
	auto parent = 0;
	for (auto i = 1; i < nodeCount; ++i) {
		height = 1;
		parent = tree[i][0];
		while (parent != 0) {
			++height;
			parent = tree[parent][0];
			if ((height & (height -1)) == 0) {
				tree[i].push_back(parent);
			}
		}
	}

	struct PowerOfTwo
	{
		int power;
		int value;
	};

	// Precalculations
	std::vector<PowerOfTwo> twoPowers(nodeCount + 1, { 0, 1 });
	auto twoPower = 0;
	auto twoValue = 1;
	for (auto i = 2; i <= nodeCount; ++i) {
		if ((i & (i - 1)) == 0) {
			++twoPower;
			twoValue *= 2;
		}
		twoPowers[i] = { twoPower, twoValue };
	}

	// Queries
	auto node = 0;
	auto currentNode = 0;
	auto powerOfTwoComponent = 0;
	auto power = 0;
	height = 0;

	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d", &node, &height);
		currentNode = node;

		while (height != 0) {
			powerOfTwoComponent = twoPowers[height].value;
			power = twoPowers[height].power;
			if (tree[currentNode].size() > power) {
				currentNode = tree[currentNode][power];
				height -= powerOfTwoComponent;
			} else {
				currentNode = -1;
				break;
			}
		}

		printf("%d ", currentNode);
	}

	int stop;
	scanf("%d", &stop);
}

int main()
{
	doTask3B();
	return 0;
}
