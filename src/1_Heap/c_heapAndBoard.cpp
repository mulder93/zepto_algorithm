//
//  c_heapAndBoard.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 29.03.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <functional>
#include <cmath>
#include <cctype>

const int MAX_COMMAND_LENGTH = 20;
const int M = 5;

template <typename ItemType, typename KeyType = size_t>
class Heap
{
    using Comparator = std::function<bool(const ItemType&, const ItemType&)>;
    using KeyGetter = std::function<KeyType(const ItemType&)>;

private:
    std::vector<ItemType> m_items;
    ItemType m_default;

    Comparator m_comparator;
    KeyGetter m_keyGetter;

    std::unordered_map<KeyType, size_t> m_indexes;

private:
    int getParentIndex(size_t index)
    {
        if (index < 1) {
            return -1;
        } else {
            return std::floor((index - 1) / 2);
        }
    }

    size_t getFirstChildIndex(size_t index)
    {
        return 2 * index + 1;
    }

    size_t getSecondChildIndex(size_t index)
    {
        return 2 * index + 2;
    }

    void bubbleFromBack()
    {
        if (m_items.size() < 1) {
            return;
        }

        auto index = m_items.size() - 1;
        int parentIndex = getParentIndex(index);
        while (parentIndex >= 0) {
            bool needSwap = m_comparator(m_items[index], m_items[parentIndex]);
            if (needSwap) {
                std::swap(m_items[index], m_items[parentIndex]);
                if (m_keyGetter) {
                    m_indexes[m_keyGetter(m_items[index])] = index;
                    m_indexes[m_keyGetter(m_items[parentIndex])] = parentIndex;
                }
                index = parentIndex;
                parentIndex = getParentIndex(index);
            } else {
                break;
            }
        }
    }

    void siftDown(size_t index, size_t heapSize)
    {
        auto childIndex = getFirstChildIndex(index);
        while (childIndex < heapSize) {
            auto secondChildIndex = getSecondChildIndex(index);
            if (secondChildIndex < heapSize && m_comparator(m_items[secondChildIndex], m_items[childIndex])) {
                childIndex = secondChildIndex;
            }

            if (m_comparator(m_items[childIndex], m_items[index])) {
                std::swap(m_items[childIndex], m_items[index]);
                if (m_keyGetter) {
                    m_indexes[m_keyGetter(m_items[childIndex])] = childIndex;
                    m_indexes[m_keyGetter(m_items[index])] = index;
                }
                index = childIndex;
                childIndex = getFirstChildIndex(index);
            } else {
                break;
            }
        }
    }

public:
    Heap(const Comparator& comparator = std::greater<ItemType>(), const KeyGetter& keyGetter = nullptr)
    {
        m_comparator = comparator;
        m_keyGetter = keyGetter;
    }

    size_t size() const
    {
        return m_items.size();
    }

    const ItemType& operator[](size_t index) const
    {
        return m_items[index];
    }

    const ItemType& getTop() const
    {
        if (m_items.size() > 0) {
            return m_items[0];
        } else {
            return m_default;
        }
    }

    void setTop(const ItemType& item, bool heapify = true)
    {
        if (m_items.size() > 0) {
            m_items[0] = item;
            if (m_keyGetter) {
                m_indexes[m_keyGetter(item)] = 0;
            }
            if (heapify) {
                siftDown(0);
            }
        } else {
            m_items.push_back(item);
            if (m_keyGetter) {
                m_indexes[m_keyGetter(item)] = 0;
            }
        }
    }

    void pushBack(const ItemType& item, bool heapify = true)
    {
        m_items.push_back(item);
        if (m_keyGetter) {
            m_indexes[m_keyGetter(item)] = m_items.size() - 1;
        }
        if (heapify) {
            bubbleFromBack();
        }
    }

    void siftDown(size_t index)
    {
        siftDown(index, m_items.size());
    }

    bool contains(const KeyType& key) const
    {
        return m_keyGetter && m_indexes.find(key) != m_indexes.end();
    }

    void remove(const KeyType& key, bool heapify = true)
    {
        if (contains(key)) {
            auto index = m_indexes[key];

            if (m_items.size() > 0 && index < m_items.size()) {
                bool shouldHeapify = false;
                if (m_items.size() > 1 && index < m_items.size() - 1) {
                    m_indexes.erase(m_keyGetter(m_items[index]));
                    m_items[index] = m_items.back();
                    m_indexes[m_keyGetter(m_items[index])] = index;
                    shouldHeapify = true;
                } else {
                    m_indexes.erase(m_keyGetter(m_items.back()));
                }
                m_items.pop_back();

                if (shouldHeapify && heapify) {
                    siftDown(index);
                }
            }
        }
    }

    void heapify()
    {
        for (auto i = std::floor(m_items.size() / 2); i >= 0; --i) {
            siftDown(i);
        }
    }

    void sort()
    {
        if (m_items.size() <= 1) {
            return;
        }

        auto heapSize = m_items.size();
        while (heapSize > 1) {
            std::swap(m_items[0], m_items[heapSize - 1]);
            if (m_keyGetter) {
                m_indexes[m_keyGetter(m_items[0])] = 0;
                m_indexes[m_keyGetter(m_items[heapSize - 1])] = heapSize - 1;
            }
            --heapSize;
            siftDown(0, heapSize);
        }
    }

    void print()
    {
        if (m_items.size() > 0) {
            for (auto item : m_items) {
                printf("%d\t", item.value);
            }
            printf("\n");
            for (auto item : m_items) {
                printf("^\t");
            }
            printf("\n");
            for (auto item : m_items) {
                printf("|\t");
            }
            printf("\n");
            for (auto item : m_items) {
                printf("%d\t", item.num);
            }
            printf("\n");

            for (auto pair : m_indexes) {
                printf("key %d - index %d\n", pair.first, pair.second);
            }
            printf("\n");
        } else {
            printf("-");
            printf("\n");
        }
    }
};

struct BoardItem
{
    size_t num;
    int value;

    BoardItem() : num(0), value(0) { }
    BoardItem(size_t num, int value) : num(num), value(value) { }

    bool operator<(const BoardItem& other) const
    {
        return value < other.value;
    }
    bool operator>(const BoardItem& other) const
    {
        return value > other.value;
    }
};

enum class Command
{
    Add,
    Find,
    Delete
};

void doTask1C();
int readValue(char* buf);
Command readCommand(char* buf);
void addItem(int value, int itemNum, Heap<BoardItem>& minMItems, Heap<BoardItem>& otherItems);
void findItem(int value, Heap<BoardItem>& minMItems, std::vector<int>& found);
void deleteItem(int value, Heap<BoardItem>& minMItems, Heap<BoardItem>& otherItems);

//int main(int argc, const char* argv[])
//{
//    doTask1C();
//    return 0;
//}

void doTask1C()
{
    auto keyGetter = [](const BoardItem& item) {
        return item.num;
    };

    Heap<BoardItem> minMItems(std::greater<BoardItem>(), keyGetter);
    Heap<BoardItem> otherItems(std::less<BoardItem>(), keyGetter);

    int size;
    scanf("%d", &size);

    int itemNum = 1;
    std::vector<int> found;
    for (int i = 0; i < size; ++i) {
        char buf[MAX_COMMAND_LENGTH + 1];
        scanf("%s", buf);

        auto value = readValue(buf);
        auto command = readCommand(buf);

        switch (command) {
            case Command::Add:
                addItem(value, itemNum, minMItems, otherItems);
                ++itemNum;
                break;

            case Command::Find:
                findItem(value, minMItems, found);
                break;

            case Command::Delete:
                deleteItem(value, minMItems, otherItems);
                break;
        }
    }

    for (auto item : found) {
        printf("%d\n", item);
    }
}

int readValue(char* buf)
{
    int value = 0;
    for (int j = 0; j <= MAX_COMMAND_LENGTH; ++j) {
        if (isdigit(buf[j]) || buf[j] == '-' || buf[j] == '+') {
            value = atoi(&buf[j]);
            break;
        }
    }
    return value;
}

Command readCommand(char* buf)
{
    switch (buf[0]) {
        case 'A':
            return Command::Add;
        case 'F':
            return Command::Find;
        case 'D':
            return Command::Delete;
        default:
            return Command::Add;
    }
}

void addItem(int value, int itemNum, Heap<BoardItem>& minMItems, Heap<BoardItem>& otherItems)
{
    BoardItem item(itemNum, value);
    if (minMItems.size() >= M) {
        if (item < minMItems.getTop()) {
            otherItems.pushBack(minMItems.getTop());
            minMItems.setTop(item);
        } else {
            otherItems.pushBack(item);
        }
    } else {
        minMItems.pushBack(item);
    }
}

void findItem(int value, Heap<BoardItem>& minMItems, std::vector<int>& found)
{
    if (minMItems.size() >= value) {
        minMItems.sort();
        found.emplace_back(minMItems[value - 1].value);
        minMItems.heapify();
    }
}

void deleteItem(int value, Heap<BoardItem>& minMItems, Heap<BoardItem>& otherItems)
{
    if (minMItems.contains(value)) {
        minMItems.remove(value);
        if (otherItems.size() > 0) {
            auto transferNum = otherItems.getTop().num;
            minMItems.pushBack(otherItems.getTop());
            otherItems.remove(transferNum);
        }
    } else {
        otherItems.remove(value);
    }
}
