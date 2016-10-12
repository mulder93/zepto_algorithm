#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

int quickSortRandomPartition(std::vector<int>& data, const int left, const int right)
{
	const auto size = right - left + 1;
	auto pivotPos = left + rand() % size;

	std::swap(data[pivotPos], data[right]);
	pivotPos = right;
	const auto pivotValue = data[pivotPos];

	auto leftCursor = left - 1;
	auto rightCursor = left;
	
	while (rightCursor < pivotPos) {
		if (data[rightCursor] <= pivotValue) {
			++leftCursor;
			std::swap(data[leftCursor], data[rightCursor]);
		}
		++rightCursor;
	}

	std::swap(data[leftCursor + 1], data[pivotPos]);
	return leftCursor + 1;
}

int getKth(std::vector<int>& data, const int k)
{
	auto left = 0;
	auto right = data.size() - 1;
	while (true) {
		const int pivotPos = quickSortRandomPartition(data, left, right);
		if (k == pivotPos) {
			return data[pivotPos];
		} else if (k < pivotPos) {
			right = pivotPos - 1;
		} else {
			left = pivotPos + 1;
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

	auto stop = 0;
	scanf("%d", &stop);
}

int main()
{
	doTask4B();
	return 0;
}
