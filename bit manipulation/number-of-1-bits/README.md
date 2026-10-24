# Number of 1 Bits

**Problem:** [LeetCode - Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Return the number of set bits (bits equal to `1`) in the binary representation of `n`, also called its Hamming weight. The current problem guarantees `1 <= n <= 2^31 - 1`.

## Approach: clear the lowest set bit

Use Brian Kernighan's algorithm: each application of `n & (n - 1)` removes exactly the lowest set bit.

Subtracting one changes the lowest `1` to `0` and all trailing zeros to ones. Higher bits remain unchanged. ANDing the original number with this result clears that lowest `1` while preserving all higher bits.

```text
n       = 1100
n - 1   = 1011
AND     = 1000
```

1. Initialize `count = 0`.
2. While `n` is nonzero, replace it with `n & (n - 1)`.
3. Increment `count` for the bit just removed.
4. Return `count` when no set bits remain.

Every iteration removes one original set bit, so the number of iterations equals the answer. The algorithm skips zero bits instead of inspecting every bit position.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `hammingWeight(n)` | Return the number of set bits |
| `count` | Count removed set bits |
| `n != 0` | Continue while any set bit remains |
| `n &= n - 1` | Clear the lowest remaining set bit |
| `++count` | Record one removed bit |

## Walkthrough

For `n = 11`, whose binary representation is `1011`:

| Iteration | `n` before | `n - 1` | `n & (n - 1)` | Count |
| --- | --- | --- | --- | --- |
| `1` | `1011` | `1010` | `1010` | `1` |
| `2` | `1010` | `1001` | `1000` | `2` |
| `3` | `1000` | `0111` | `0000` | `3` |

Return `3`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `&` is bitwise AND; `&&` is logical AND and cannot replace it here.
- `n &= n - 1` means `n = n & (n - 1)`.
- The argument is passed by value, so changing `n` does not change the caller's integer.
- The current LeetCode signature uses `int n`. This implementation assumes nonnegative input; negative signed integers are outside its contract.
- The loop checks `n` before subtracting, so zero also returns zero without subtraction.
- State is local, allowing repeated calls on the same object.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `11` (`1011`) | `3` | Multiple set bits |
| `128` (`10000000`) | `1` | Zeros below a single set bit |
| `2147483645` | `30` | Large input with one missing bit |
| `2147483647` | `31` | All 31 permitted bits set |
| Any `2^k`, with `0 <= k <= 30` | `1` | Each individual bit position |
| `0x55555555` | `16` | Alternating bit pattern |
| `0` | `0` | Extra boundary case outside the positive-input constraint |

Tests compare all integers from `1` through `65535` and 1000 deterministic random positive 32-bit signed integers against `std::bitset<32>::count()`. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o number-of-1-bits-test
./number-of-1-bits-test
```

## Complexity

**Time:** O(k), where `k` is the number of set bits; at most 31 iterations under the stated constraints, so O(1) for this fixed-width input.\
**Auxiliary space:** O(1), storing only a counter and the local integer.
