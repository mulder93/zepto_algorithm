#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

struct TreeNode
{
	int num;
	std::vector<int> children;
	std::vector<int> parents;

	TreeNode() : num(0) { }
};

using Tree = std::vector<TreeNode>;

void fillParents(Tree& tree, int node, std::vector<int>& parents)
{
	for (auto height = 2; height <= parents.size(); height *= 2) {
		tree[node].parents.push_back(parents[parents.size() - (height - 1) - 1]);
	}
	parents.push_back(node);
	for (auto child : tree[node].children) {
		fillParents(tree, child, parents);
	}
	parents.pop_back();
}

void doTask3B()
{
	// Get params
	auto nodeCount = 0;
	auto queryCount = 0;
	scanf("%d %d", &nodeCount, &queryCount);

	// Read tree
	Tree tree(nodeCount);
	auto parentIndex = 0;
	for (auto i = 1; i < nodeCount; ++i) {
		scanf("%d", &parentIndex);
		tree[i].num = i;
		tree[i].parents.push_back(parentIndex);
		tree[parentIndex].children.push_back(i);
	}
	std::vector<int> parents;
	fillParents(tree, 0, parents);

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
	auto height = 0;

	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d", &node, &height);
		currentNode = node;

		while (height != 0) {
			powerOfTwoComponent = twoPowers[height].value;
			power = twoPowers[height].power;
			if (tree[currentNode].parents.size() > power) {
				currentNode = tree[currentNode].parents[power];
				height -= powerOfTwoComponent;
			} else {
				currentNode = -1;
				break;
			}
		}

		printf("%d ", currentNode);
	}
}

int main()
{
	doTask3B();
	return 0;
}
