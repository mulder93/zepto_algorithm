#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

class FenwickSumPerstistentTree
{
private:
	struct VersionValuePair
	{
		int version;
		int value;

		VersionValuePair() : version(0), value(0)
		{
		}

		VersionValuePair(int version, int value) : version(version), value(value)
		{
		}

		bool operator<(const VersionValuePair& other)
		{
			return version < other.version;
		}

		bool operator<(int version)
		{
			return this->version < version;
		}
	};

	class PersistentValue
	{
	private:
		std::vector<VersionValuePair> m_data;

	public:
		int get(int version)
		{
			if (m_data.size() == 0) {
				return 0;
			}

			auto lower = std::lower_bound(m_data.begin(), m_data.end(), version);
			if (lower == m_data.end()) { // no version greater 'version'. Take last value
				return m_data.back().value;
			} else if (lower->version == version) { // we have exactly 'version' value
				return lower->value;
			} else if (lower != m_data.begin()) { // take first version lower 'version'
				--lower;
				return lower->value;
			} else { // no changes before 'version'
				return 0;
			}
		}

		void inc(int version, int delta)
		{
			if (m_data.size() > 0 && m_data.back().version == version) {
				m_data.back().value += delta;
			} else if (m_data.size() > 0) {
				m_data.emplace_back(version, m_data.back().value + delta);
			} else {
				m_data.emplace_back(version, delta);
			}
		}
	};

	std::vector<PersistentValue> m_data;

public:
	FenwickSumPerstistentTree(size_t size) : m_data(size)
	{
	}

	void inc(int pos, int value, int version)
	{
		for (; pos < m_data.size(); pos |= (pos + 1)) {
			m_data[pos].inc(version, value);
		}
	}

	int sum(int pos, int version)
	{
		int result = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
			result += m_data[pos].get(version);
		}
		return result;
	}

	int sum(int left, int right, int version)
	{
		return sum(right, version) - sum(left - 1, version);
	}

	int getValue(int pos, int version)
	{
		return sum(pos, version) - sum(pos - 1, version);
	}

	void setValue(int pos, int value, int version)
	{
		inc(pos, value - getValue(pos, version), version);
	}
};

struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;
};

void doTask2F()
{
	int width;
	int height;
	int rectCount;
	int queryCount;
	scanf("%d %d %d %d", &height, &width, &rectCount, &queryCount);

	std::vector<Rect> rectsLeft;
	std::vector<Rect> rectsRight;
	auto i = 0;
	for (; i < rectCount; ++i) {
		Rect rect;
		scanf("%d %d %d %d", &rect.x1, &rect.y1, &rect.x2, &rect.y2);
		rectsLeft.push_back(rect);
		rectsRight.push_back(std::move(rect));
	}

	std::sort(rectsLeft.begin(), rectsLeft.end(), [](const Rect& lhs, const Rect& rhs) {
		return lhs.y1 < rhs.y1;
	});
	std::sort(rectsRight.begin(), rectsRight.end(), [](const Rect& lhs, const Rect& rhs) {
		return lhs.y2 < rhs.y2;
	});

	FenwickSumPerstistentTree data(height);
	auto leftIterator = rectsLeft.begin();
	auto rightIterator = rectsRight.begin();
	for (i = 0; i < width; ++i) {
		while (leftIterator != rectsLeft.end() && leftIterator->y1 == i) {
			data.inc(leftIterator->x1, 1, i);
			data.inc(leftIterator->x2 + 1, -1, i);
			++leftIterator;
		}
		while (rightIterator != rectsRight.end() && rightIterator->y2 == i - 1) {
			data.inc(rightIterator->x1, -1, i);
			data.inc(rightIterator->x2 + 1, 1, i);
			++rightIterator;
		}
	}

	i = 0;
	int x = 0;
	int y = 0;
	for (auto i = 0; i < queryCount; ++i) {
		scanf("%d %d", &x, &y);
		printf("%d\n", data.sum(x, y));
		std::cout << std::flush;
	}
}

int main()
{
	doTask2F();
	return 0;
}
