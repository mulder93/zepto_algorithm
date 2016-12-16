#include <cstdio>
#include <queue>

void doTask5C()
{
	int n;
	scanf("%d", &n);

	std::queue<int> data;
	data.push(1);
	data.push(2);
	data.push(3);
	data.push(4);
	data.push(5);

	/*std::vector<int> data{ 1, 2, 3, 4, 5 };
	auto pointer = 0;*/
	/*while (data.size() < n) {
		data.push_back(data[pointer]);
		data.push_back(data[pointer]);
		++pointer;
	}

	switch (data[n - 1]) {
	case 1:
		printf("Sheldon\n");
		break;
	case 2:
		printf("Leonard\n");
		break;
	case 3:
		printf("Penny\n");
		break;
	case 4:
		printf("Rajesh\n");
		break;
	case 5:
		printf("Howard\n");
		break;
	}*/

	//auto stop = 0;
	//scanf("%d", &stop);
}

//int main()
//{
//	doTask5C();
//	return 0;
//}
