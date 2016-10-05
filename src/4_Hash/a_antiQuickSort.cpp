#include <cstdio>
#include <vector>

void doTask4A()
{
	auto dataSize = 0;
	scanf("%d", &dataSize);

	std::vector<int> data(dataSize);
	for (auto i = 0; i < dataSize; ++i) {
		data[i] = i + 1;
	}

	for (auto i = 2; i < dataSize; ++i) {
		std::swap(data[i], data[i / 2]);
	}

	for (auto i = 0; i < dataSize; ++i) {
		printf("%d ", data[i]);
	}

	//auto stop = 0;
	//scanf("%d", &stop);
}

//int main()
//{
//	doTask4A();
//	return 0;
//}
