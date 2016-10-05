#include <cstdio>
#include <vector>

class PersistentStack
{
public:
	PersistentStack() : m_versionHeads(1, { 0, 0 })
	{
		// Initially stack contains one version (version '0') with null head
	}

	void push(int version, int value)
	{
		m_versionHeads.emplace_back(version, value);
	}

	void pop(int version)
	{
		auto& head = m_versionHeads[version];
		printf("%d\n", head.value);
		m_versionHeads.push_back(m_versionHeads[head.prev]);
	}

private:
	struct Item
	{
		int prev;
		int value;

		Item(int prev, int value) : prev(prev), value(value) { }
	};

	std::vector<Item> m_versionHeads;
};

void doTask3E()
{
	auto queriesCount = 0;
	scanf("%d", &queriesCount);

	PersistentStack stack;

	auto version = 0;
	auto value = 0;
	for (auto i = 0; i < queriesCount; ++i) {
		scanf("%d %d", &version, &value);
		if (value > 0) {
			stack.push(version, value);
		} else {
			stack.pop(version);
		}
	}
}

/*int main()
{
	doTask3E();
	return 0;
}*/
