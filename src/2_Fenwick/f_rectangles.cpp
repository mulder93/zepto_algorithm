#include <cstdio>
#include <iostream>
#include <cstring>

class FenwickTree2D
{
private:
	int** m_data;
	size_t m_width;
	size_t m_height;

public:
	FenwickTree2D(size_t width, size_t height) : m_width(width), m_height(height)
	{
		m_data = new int*[width];
		for (int i = 0; i < width; ++i) {
			m_data[i] = new int[height];
			memset(m_data[i], 0, sizeof(int) * height);
		}
	}

	~FenwickTree2D()
	{
		for (int i = 0; i < m_width; ++i) {
			delete[] m_data[i];
		}
		delete[] m_data;
	}

	void inc(int x, int y, int value)
	{
		for (auto i = x; i < m_width; i |= (i + 1)) {
			for (auto j = y; j < m_height; j |= (j + 1)) {
				m_data[i][j] += value;
			}
		}
	}

	int sum(int x, int y)
	{
		int result = 0;
		for (auto i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (auto j = y; j >= 0; j = (j & (j + 1)) - 1) {
				result += m_data[i][j];
			}
		}
		return result;
	}

	int sum(int x1, int y1, int x2, int y2)
	{
		return
			+ sum(x2,     y2)
			- sum(x2,     y1 - 1)
			- sum(x1 - 1, y2)
			+ sum(x1 - 1, y1 - 1);
	}
};

class RectCounter
{
private:
	FenwickTree2D m_data;
	int m_width;
	int m_height;

public:
	RectCounter(size_t width, size_t height) : m_data(width, height), m_width(width), m_height(height)
	{
	}

	int count(int x, int y)
	{
		return m_data.sum(0, 0, x, y);
	}

	void add(int x1, int y1, int x2, int y2)
	{
		m_data.inc(x1,     y1,      1);
		m_data.inc(x1,     y2 + 1, -1);
		m_data.inc(x2 + 1, y1,     -1);
		m_data.inc(x2 + 1, y2 + 1,  1);
	}
};

void doTask2F();

/*int main()
{
    doTask2F();
    return 0;
}*/

void doTask2F()
{
	int width;
	int height;
	int rectCount;
	int queryCount;
	scanf("%d %d %d %d", &width, &height, &rectCount, &queryCount);

	RectCounter rects(width, height);

	int x1, y1, x2, y2;
	auto i = 0;
	for (; i < rectCount; ++i) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		rects.add(x1, y1, x2, y2);
	}

	i = 0;
	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d", &x1, &y1);
		printf("%d\n", rects.count(x1, y1));
		std::cout << std::flush;
	}
}
