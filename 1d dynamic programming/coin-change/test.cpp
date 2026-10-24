#include <cassert>
#include <climits>
#include <queue>
#include "solution.cpp"

int bfs(const std::vector<int>& coins, int amount) {
    std::vector<int> distance(amount + 1, -1);
    std::queue<int> pending;
    distance[0] = 0;
    pending.push(0);
    while (!pending.empty()) {
        int sum = pending.front();
        pending.pop();
        if (sum == amount) return distance[sum];
        for (int coin : coins) {
            if (coin <= amount - sum && distance[sum + coin] == -1) {
                distance[sum + coin] = distance[sum] + 1;
                pending.push(sum + coin);
            }
        }
    }
    return -1;
}

int main() {
    Solution solution;
    auto check = [&](std::vector<int> coins, int amount, int expected) {
        const auto original = coins;
        assert(solution.coinChange(coins, amount) == expected);
        assert(coins == original);
    };

    check({1, 2, 5}, 11, 3);
    check({2}, 3, -1);
    check({1}, 0, 0);
    check({1, 3, 4}, 6, 2);
    check({5, 2, 1}, 11, 3);
    check({7}, 7, 1);
    check({4, 6}, 7, -1);
    check({INT_MAX}, 1, -1);
    check({INT_MAX, 1}, 2, 2);
    check({1}, 10000, 10000);
    check({2}, 9999, -1);

    for (int mask = 1; mask < (1 << 7); ++mask) {
        std::vector<int> coins;
        for (int coin = 1; coin <= 7; ++coin) {
            if (mask & (1 << (coin - 1))) coins.push_back(coin);
        }
        for (int amount = 0; amount <= 30; ++amount) {
            check(coins, amount, bfs(coins, amount));
        }
    }
}
