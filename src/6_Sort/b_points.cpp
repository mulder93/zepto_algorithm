#include <cstdio>
#include <vector>
#include <algorithm>

struct SegmentEvent
{
	enum class Type
	{
		Start,
		End,
	};

	long long coord;
	Type type;

	SegmentEvent(long long coord, Type type) : coord(coord), type(type) { }
	SegmentEvent() : coord(0), type(Type::Start) { }
};

void doTask6B()
{
	// Read segments count
	int segmentsCount = 0;
	scanf("%d", &segmentsCount);

	// Read segment events
	std::vector<SegmentEvent> events(segmentsCount * 2);
	for (int i = 0; i < segmentsCount; ++i) {
		auto& startedEvent = events[i * 2];
		startedEvent.type = SegmentEvent::Type::Start;
		scanf("%I64d", &startedEvent.coord);

		auto& endedEvent = events[i * 2 + 1];
		endedEvent.type = SegmentEvent::Type::End;
		scanf("%I64d", &endedEvent.coord);
	}

	// Sort events by coord and by type
	std::sort(events.begin(), events.end(), [](const SegmentEvent& lhs, const SegmentEvent& rhs) {
		if (lhs.coord == rhs.coord) {
			return lhs.type == SegmentEvent::Type::Start && rhs.type == SegmentEvent::Type::End;
		} else {
			return lhs.coord < rhs.coord;
		}
	});

	// Read points count
	int pointsCount = 0;
	scanf("%d", &pointsCount);

	// Read points
	std::vector<long long> points(pointsCount);
	for (int i = 0; i < pointsCount; ++i) {
		scanf("%I64d", &points[i]);
	}

	// Sort points by coord
	std::sort(points.begin(), points.end());

	// Read threshold
	int goodThreshold = 0;
	scanf("%d", &goodThreshold);

	// Merge segments
	std::vector<SegmentEvent> mergedEvents;
	int overlapCount = 0;
	for (auto& event : events) {
		if (event.type == SegmentEvent::Type::Start) {
			++overlapCount;
			if (overlapCount == goodThreshold) {
				mergedEvents.push_back(event);
			}
		} else {
			if (overlapCount == goodThreshold) {
				mergedEvents.push_back(event);
			}
			--overlapCount;
		}
	}

	// Main algorithm
	int goodPointsCount = 0;
	auto pointIterator = points.begin();
	for (auto& event : mergedEvents) {
		if (event.type == SegmentEvent::Type::Start) {
			while (pointIterator != points.end() && *pointIterator < event.coord) {
				++pointIterator;
			}
		} else {
			while (pointIterator != points.end() && *pointIterator <= event.coord) {
				++pointIterator;
				++goodPointsCount;
			}
		}
	}

	printf("%d", goodPointsCount);

	//auto stop = 0;
	//scanf("%d", &stop);
}

int main()
{
	doTask6B();
	return 0;
}
