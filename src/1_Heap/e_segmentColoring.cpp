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

struct SubSegment
{
    unsigned int left;
    unsigned int right;
    unsigned int color;
};

void doTask1E();

int main()
{
    doTask1E();
    return 0;
}

void doTask1E()
{
    unsigned int segmentLength;
    unsigned int subSegmentsCount;
    scanf("%u %u", &segmentLength, &subSegmentsCount);

    std::vector<SubSegment> subSegments(subSegmentsCount);
    std::vector<unsigned int> leftSortedSubSegments(subSegmentsCount);
    std::vector<unsigned int> rightSortedSubSegments(subSegmentsCount);
    for (auto i = 0; i < subSegmentsCount; ++i) {
        SubSegment subSegment;
        scanf("%u %u %u", &subSegment.left, &subSegment.right, &subSegment.color);
        subSegments[i] = std::move(subSegment);

        leftSortedSubSegments[i] = i;
        rightSortedSubSegments[i] = i;
    }

    std::sort(leftSortedSubSegments.begin(), leftSortedSubSegments.end(), [&subSegments](unsigned int lhs, unsigned int rhs) {
        return subSegments[lhs].left <= subSegments[rhs].left;
    });
    std::sort(rightSortedSubSegments.begin(), rightSortedSubSegments.end(), [&subSegments](unsigned int lhs, unsigned int rhs) {
        return subSegments[lhs].right <= subSegments[rhs].right;
    });

    std::set<unsigned int, std::greater<unsigned int>> currentSubSegments;

    auto leftIterator = leftSortedSubSegments.begin();
    auto rightIterator = rightSortedSubSegments.begin();
    for (auto i = 0; i < segmentLength; ++i) {
        while (leftIterator != leftSortedSubSegments.end() && subSegments[*leftIterator].left == i) {
            currentSubSegments.emplace(*leftIterator);
            ++leftIterator;
        }

        while (rightIterator != rightSortedSubSegments.end() && subSegments[*rightIterator].right == i) {
            currentSubSegments.erase(*rightIterator);
            ++rightIterator;
        }

        if (currentSubSegments.size() > 0) {
            printf("%u", subSegments[*currentSubSegments.begin()].color);
        } else {
            printf("0");
        }

        if (i != segmentLength - 1) {
            printf(" ");
        }
    }
    
    printf("\n");
}
