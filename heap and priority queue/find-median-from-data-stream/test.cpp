#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include "solution.cpp"

void checkStream(const std::vector<int>& stream) {
    MedianFinder finder;
    std::vector<int> sorted;

    for (int num : stream) {
        finder.addNum(num);
        sorted.push_back(num);
        std::sort(sorted.begin(), sorted.end());

        const auto middle = sorted.size() / 2;
        const double expected = sorted.size() % 2 == 1
            ? sorted[middle]
            : (static_cast<double>(sorted[middle - 1]) + sorted[middle]) / 2.0;
        assert(finder.findMedian() == expected);
        assert(finder.findMedian() == expected);
    }
}

int main() {
    checkStream({1, 2, 3});
    checkStream({7, 1, 3, 5});
    checkStream({1, 2, 3, 4, 5, 6});
    checkStream({6, 5, 4, 3, 2, 1});
    checkStream({4, 4, 4, 4});
    checkStream({-5, -1, -3, 0, 2});
    checkStream({INT_MAX, INT_MAX, INT_MIN, INT_MIN, 0});
    checkStream({INT_MIN, INT_MIN, INT_MAX, INT_MAX});

    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(-100000, 100000);
    std::vector<int> stream;
    for (int i = 0; i < 1000; ++i) {
        stream.push_back(distribution(generator));
    }
    checkStream(stream);
}
