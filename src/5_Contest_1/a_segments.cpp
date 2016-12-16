#include <cstdio>
#include <vector>
#include <algorithm>

struct Segment
{
	int left;
	int right;
};

void doTask5A()
{
	int segmentsCount;
	scanf("%d", &segmentsCount);

	std::vector<Segment> segments(segmentsCount);

	for (auto i = 0; i < segmentsCount; ++i) {
		Segment segment;
		scanf("%d %d", &segment.left, &segment.right);
		segments[i] = std::move(segment);
	}

	std::sort(segments.begin(), segments.end(), [](const Segment& lhs, const Segment& rhs) {
		return lhs.left < rhs.left;
	});

	std::vector<Segment> mergedSegments;
	auto segmentEnd = 0;

	for (auto& segment : segments) {
		if (segment.left > segmentEnd) {
			if (mergedSegments.size() > 0) {
				mergedSegments.back().right = segmentEnd;
			}
			segmentEnd = segment.right;

			Segment newSegment;
			newSegment.left = segment.left;
			mergedSegments.push_back(std::move(newSegment));
		} else if (segment.left <= segmentEnd) {
			segmentEnd = std::max(segment.right, segmentEnd);
		}
	}

	if (mergedSegments.size() > 0) {
		mergedSegments.back().right = segmentEnd;
	}

	printf("%d\n", mergedSegments.size());
	for (auto& segment : mergedSegments) {
		printf("%d %d\n", segment.left, segment.right);
	}
	
	//auto stop = 0;
	//scanf("%d", &stop);
}

//int main()
//{
//	doTask5A();
//	return 0;
//}
