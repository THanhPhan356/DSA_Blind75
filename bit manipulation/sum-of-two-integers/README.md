# Sum of Two Integers

**Problem:** [LeetCode - Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Return the sum of integers `a` and `b` without using the `+` or `-` operators in the solution. The input guarantees `-1000 <= a, b <= 1000`; negative inputs must also work.

## Approach: XOR for the sum, AND and shift for the carry

Separate binary addition into two parts:

```text
x ^ y          sum without carrying
(x & y) << 1   carry moved to the next bit position
```

For one bit, XOR gives the sum bit, while AND detects the case where both inputs are one:

| Input bits | Sum bit (XOR) | Carry bit (AND) |
| --- | --- | --- |
| `0`, `0` | `0` | `0` |
| `0`, `1` | `1` | `0` |
| `1`, `0` | `1` | `0` |
| `1`, `1` | `0` | `1` |

1. Convert the inputs to unsigned integers so shifts and wrapping arithmetic are well-defined.
2. While the second value is nonzero, compute the shifted carry before updating either operand.
3. Replace the first value with the XOR of both values.
4. Replace the second value with the carry.
5. Repeat until no carry remains, then return the first value as a signed integer.

Each iteration preserves the sum modulo the unsigned integer range. Any remaining carry moves toward higher bit positions until it disappears. On the judge's 32-bit integers, at most 32 iterations are needed. The actual mathematical result is between `-2000` and `2000`, so it fits the signed return type.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `getSum(a, b)` | Add without arithmetic addition or subtraction operators |
| Unsigned `x`, `y` | Hold the input bit patterns during carry propagation |
| `x & y` | Find positions producing a carry |
| `<< 1` | Move carries to the next bit position |
| `x ^= y` | Compute the partial sum without carrying |
| `y = carry` | Process the remaining carry in the next iteration |
| `static_cast<int>(x)` | Interpret the final result as a signed integer on the judge |

## Walkthrough

For `a = 2` and `b = 3`, use four bits for readability:

| Iteration | `x` before | `y` before | New `x = x ^ y` | New `y = (x & y) << 1` |
| --- | --- | --- | --- | --- |
| `1` | `0010` | `0011` | `0001` | `0100` |
| `2` | `0001` | `0100` | `0101` | `0000` |

No carry remains. Return `0101`, which is `5`. Both new values in each row are computed from the old operands.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `^` is bitwise XOR; `&` is bitwise AND; `<< 1` shifts left by one bit.
- Compute `carry` before changing `x`, since carry detection needs both old operands.
- Avoid left-shifting a negative signed integer. This implementation shifts only unsigned values.
- Converting a negative input to unsigned is defined modulo the unsigned range. Unsigned shifts discard bits beyond the fixed width.
- The final unsigned-to-signed conversion follows the LeetCode GCC/Clang two's-complement behavior. In C++17, an out-of-range unsigned-to-signed conversion is implementation-defined; in C++20, the conversion is specified modulo the destination width.
- Addition in `test.cpp` is only an independent oracle; `solution.cpp` contains neither arithmetic operator.
- All state is local, so one object can handle repeated calls.

## Cases to check

| Inputs | Expected result | What it checks |
| --- | --- | --- |
| `1`, `2` | `3` | No overlapping set bits |
| `2`, `3` | `5` | Carry generation |
| `0`, `0` | `0` | Immediate termination |
| `-1`, `1` | `0` | Opposite signs and a long carry chain |
| `-2`, `-3` | `-5` | Two negative operands |
| `7`, `1` | `8` | Carry through consecutive ones |
| `-1000`, `-1000` | `-2000` | Minimum possible sum |
| `1000`, `1000` | `2000` | Maximum possible sum |

Tests exhaustively compare all `4,004,001` valid input pairs against ordinary addition, reusing the same object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o sum-of-two-integers-test
./sum-of-two-integers-test
```

## Complexity

**Time:** O(w), where `w` is the integer width; O(1) for the judge's fixed 32-bit integers.\
**Auxiliary space:** O(1), using only a fixed number of integer variables.
