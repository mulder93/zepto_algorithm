//
//  e_segmentColoring.cpp
//  zepto_algorithm
//
//  Created by Boris Tsarev on 13.04.16.
//  Copyright © 2016 Boris Tsarev. All rights reserved.
//

#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <cmath>
#include <functional>

struct SubSegment
{
    int left;
    int right;
    int color;
};

void doTask1E();

//int main()
//{
//    doTask1E();
//    return 0;
//}

void doTask1E()
{
    int segmentLength;
    int subSegmentsCount;
    scanf("%d %d", &segmentLength, &subSegmentsCount);

    std::vector<SubSegment> subSegments(subSegmentsCount);
    std::vector<int> leftSortedSubSegments(subSegmentsCount);
    std::vector<int> rightSortedSubSegments(subSegmentsCount);
    for (auto i = 0; i < subSegmentsCount; ++i) {
        SubSegment subSegment;
        scanf("%d %d %d", &subSegment.left, &subSegment.right, &subSegment.color);
        subSegments[i] = std::move(subSegment);

        leftSortedSubSegments[i] = i;
        rightSortedSubSegments[i] = i;
    }

    std::sort(leftSortedSubSegments.begin(), leftSortedSubSegments.end(), [&subSegments](int lhs, int rhs) {
        return subSegments[lhs].left < subSegments[rhs].left;
    });
    std::sort(rightSortedSubSegments.begin(), rightSortedSubSegments.end(), [&subSegments](int lhs, int rhs) {
        return subSegments[lhs].right < subSegments[rhs].right;
    });

    std::set<int, std::greater<int>> currentSubSegments;

    auto leftIterator = leftSortedSubSegments.begin();
    auto rightIterator = rightSortedSubSegments.begin();
    for (auto i = 0; i < segmentLength; ++i) {
        while (leftIterator != leftSortedSubSegments.end() && subSegments[*leftIterator].left == i) {
            currentSubSegments.insert(*leftIterator);
            ++leftIterator;
        }

        while (rightIterator != rightSortedSubSegments.end() && subSegments[*rightIterator].right == i) {
            currentSubSegments.erase(*rightIterator);
            ++rightIterator;
        }

        if (currentSubSegments.size() > 0) {
            printf("%d", subSegments[*currentSubSegments.begin()].color);
        } else {
            printf("0");
        }

        if (i != segmentLength - 1) {
            printf(" ");
        }
    }
    
    printf("\n");
}
