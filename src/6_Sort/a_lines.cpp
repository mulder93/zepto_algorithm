#include <cstdio>
#include <vector>
#include <algorithm>

struct Point
{
	int number;
	int x;
	int y;

	Point() : x(0), y(0) { }
	Point(int x, int y) : x(x), y(y) { }
};

void doTask6A()
{
	int pointsCount = 0;
	scanf("%d", &pointsCount);
	
	std::vector<Point> points(pointsCount);
	for (int i = 0; i < pointsCount; ++i) {
		auto& point = points[i];
		point.number = i + 1;
		scanf("%d %d", &point.x, &point.y);
	}

	std::sort(points.begin(), points.end(), [](const Point& lhs, const Point& rhs) {
		if (lhs.x == rhs.x) {
			return lhs.y < rhs.y;
		} else {
			return lhs.x < rhs.x;
		}
	});

	for (int i = 0; i < pointsCount; ++i) {
		printf("%d ", points[i].number);
	}

	/*auto stop = 0;
	scanf("%d", &stop);*/
}

int main()
{
	doTask6A();
	return 0;
}
