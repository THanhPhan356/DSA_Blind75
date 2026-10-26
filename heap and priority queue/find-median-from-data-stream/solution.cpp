#include <functional>
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> lower;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper;

public:
    MedianFinder() = default;

    void addNum(int num) {
        if (lower.empty() || num <= lower.top()) {
            lower.push(num);
        } else {
            upper.push(num);
        }

        if (lower.size() > upper.size() + 1) {
            upper.push(lower.top());
            lower.pop();
        } else if (upper.size() > lower.size() + 1) {
            lower.push(upper.top());
            upper.pop();
        }
    }

    double findMedian() {
        if (lower.size() == upper.size()) {
            return (static_cast<double>(lower.top()) + upper.top()) / 2.0;
        }
        return lower.size() > upper.size() ? lower.top() : upper.top();
    }
};
