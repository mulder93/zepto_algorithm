#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

int quickSortRandomPartition(std::vector<int>& data, int left, int right)
{
	auto size = right - left + 1;
	auto pivot = rand() % size;
	auto pivotValue = data[left + pivot];

	auto i = left;
	auto j = right;
	while (i <= j) {
		while (data[i] < pivotValue) {
			++i;
		}
		while (data[j] > pivotValue) {
			--j;
		}
		if (i <= j) {
			std::swap(data[i], data[j]);
			++i;
			--j;
		}
	}

	return i - 1 - left;
}

int getKth(std::vector<int>& data, int k)
{
	auto left = 0;
	auto right = data.size() - 1;
	while (true) {
		int pivotPos = quickSortRandomPartition(data, left, right);
		if (k == pivotPos) {
			return data[left + pivotPos];
		} else if (k < pivotPos) {
			right = left + pivotPos - 1;
		} else {
			left += pivotPos + 1;
			k -= (pivotPos + 1);
		}
	}
}

void doTask4B()
{
	srand(time(0));

	auto dataSize = 0;
	scanf("%d", &dataSize);

	auto queryCount = 0;
	scanf("%d", &queryCount);

	std::vector<int> data(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		scanf("%d", &data[i]);
	}

	auto left = 0;
	auto right = 0;
	auto k = 0;
	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d %d", &left, &right, &k);
		std::vector<int> dataPart(std::vector<int>(data.begin() + left - 1, data.begin() + right));
		printf("%d\n", getKth(dataPart, k - 1));
	}

	//auto stop = 0;
	//scanf("%d", &stop);
}

int main()
{
	doTask4B();
	return 0;
}
