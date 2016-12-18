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

	// Main algorithm
	int overlapSegmentsCount = 0;
	int goodPointsCount = 0;
	auto pointIterator = points.begin();
	for (int eventIndex = 0; eventIndex < events.size(); ++eventIndex) {
		auto& event = events[eventIndex];
		if (event.type == SegmentEvent::Type::Start) {
			if (overlapSegmentsCount < goodThreshold) {
				while (pointIterator != points.end() && *pointIterator < event.coord) {
					++pointIterator;
				}
			}
			++overlapSegmentsCount;
		} else { //SegmentEvent::Type::End
			if (overlapSegmentsCount < goodThreshold) {
				while (pointIterator != points.end() && *pointIterator <= event.coord) {
					++pointIterator;
				}
			} else if (overlapSegmentsCount == goodThreshold) {
				while (pointIterator != points.end() && *pointIterator <= event.coord) {
					++pointIterator;
					++goodPointsCount; // !!!
				}
			}
			--overlapSegmentsCount;
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
