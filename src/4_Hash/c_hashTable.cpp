#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cmath>

const long long MUL = 1901LL;
const long long ADD = 94418953LL;
const long long MASK_50 = (1LL << 50) - 1;
const long long MASK_32 = (1LL << 32) - 1;

long long seed = 51539607551LL;

inline int rnd32()
{
	seed = (seed * MUL + ADD) & MASK_50;
	return int(seed & MASK_32);
}

inline long long rnd64()
{
	return ((long long)(rnd32()) << 32) ^ rnd32();
}

inline int rnd(int n)
{
	int result = int(rnd64() % n);
	if (result < 0)
		result += n;
	return result;
}

class HashTable
{
public:
	HashTable() :
		m_tableSizePower(DEFAULT_TABLE_SIZE_POWER),
		m_tableSize(std::pow(2, m_tableSizePower)),
		m_data(m_tableSize),
		m_itemsCount(0)
	{
		m_maxItemsCount = m_tableSize * ITEMS_COUNT_MAX_THRESHOLD;
		m_minItemsCount = m_tableSize * ITEMS_COUNT_MIN_THRESHOLD;
	}

	void put(long long key, long long value)
	{
		auto hash = getHash(key);
		auto item = m_data[hash];

		if (item) {
			while (item->next && item->key != key) {
				item = item->next;
			}
			if (item->key == key) {
				item->value = value;
			} else {
				item->next = new Item(key, value);
				++m_itemsCount;
			}
		} else {
			m_data[hash] = new Item(key, value);
			++m_itemsCount;
		}

		if (m_itemsCount >= m_maxItemsCount) {
			resize();
		}
	}

	bool get(long long key, long long& value)
	{
		auto hash = getHash(key);
		auto item = m_data[hash];

		if (item) {
			while (item->next && item->key != key) {
				item = item->next;
			}
			if (item->key == key) {
				value = item->value;
			}
		}

		return false;
	}

	bool erase(long long key)
	{
		auto hash = getHash(key);
		auto item = m_data[hash];
		
		if (item) {
			Item* prevItem = nullptr;
			while (item->next && item->key != key) {
				prevItem = item;
				item = item->next;
			}
			if (item->key == key) {
				if (prevItem) {
					prevItem->next = item->next;
				} else {
					m_data[hash] = item->next;
				}
				delete item;
				--m_itemsCount;

				if (m_itemsCount <= ITEMS_COUNT_MAX_THRESHOLD) {
					resize();
				}

				return true;
			}
		}
		return false;
	}

private:
	struct Item
	{
		int key;
		int value;
		Item* next;

		Item(int key, int value) :
			key(key), value(value), next(nullptr) { }
	};

	int getHash(long long key)
	{
		long long r0 = key * HASH_INDEX;
		return ((r0 & W_BIT) >> (32 - m_tableSizePower));
		//int hash = std::floor(m_tableSize * std::fmod(HASH_MULTIPLIER * key, 1.0));
		//return hash;
	}

	void resize()
	{
		if (m_itemsCount >= m_maxItemsCount) {
			m_tableSize *= 2;
			++m_tableSizePower;
		} else {
			m_tableSize /= 2;
			--m_tableSizePower;
		}
		
		m_maxItemsCount = m_tableSize * ITEMS_COUNT_MAX_THRESHOLD;
		m_minItemsCount = m_tableSize * ITEMS_COUNT_MIN_THRESHOLD;
		m_itemsCount = 0;

		auto oldTable = std::vector<Item*>(m_data.begin(), m_data.end());
		m_data = std::vector<Item*>(m_tableSize);

		for (auto item : oldTable) {
			while (item) {
				put(item->key, item->value);
				item = item->next;
			}
		}
	}

	const int DEFAULT_TABLE_SIZE_POWER = 7;
	const long long W_BIT = 4294967295;
	const unsigned int HASH_INDEX = 2654435769;

	const double ITEMS_COUNT_MAX_THRESHOLD = 0.75;
	const double ITEMS_COUNT_MIN_THRESHOLD = 0.5;

	int m_tableSizePower;
	int m_tableSize;
	std::vector<Item*> m_data;

	int m_itemsCount;
	int m_maxItemsCount;
	int m_minItemsCount;
};

void doTask4C()
{
	int n, m;
	std::cin >> n >> m;

	long long certificate = 1;

	HashTable table;

	for (int i = 0; i < n; i++)
	{
		int type = rnd(3);
		long long key = rnd(m);

		if (type == 0)
		{
			table.put(key, rnd(m));
		}

		if (type == 1)
		{
			long long result = 13091204281;
			table.get(key, result);
			certificate = certificate * 3 + result;
		}

		if (type == 2)
		{
			if (table.erase(key))
				certificate = certificate * 5;
			else
				certificate = certificate * 13;
		}
	}

	std::cout << certificate << std::endl;

	//auto stop = 0;
	//scanf("%d", &stop);
}

int main()
{
	doTask4C();
	return 0;
}
