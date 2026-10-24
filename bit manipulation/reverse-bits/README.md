# Reverse Bits

**Problem:** [LeetCode - Reverse Bits](https://leetcode.com/problems/reverse-bits/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Reverse all 32 bit positions of the input integer. Leading zeros are part of the representation. The current LeetCode problem uses a signed integer and guarantees that `n` is even and `0 <= n <= 2^31 - 2`.

## Approach: read from the right and append to the result

1. Copy the input into an unsigned 32-bit variable and initialize `result = 0`.
2. Repeat exactly 32 times.
3. Shift `result` left by one to make room for a new bit.
4. Extract the rightmost input bit with `bits & 1u` and append it with bitwise OR.
5. Shift `bits` right by one to expose the next input bit.
6. Return the reversed result.

After `k` iterations, the result contains the lowest `k` original bits in reverse order. Reading all 32 positions therefore reverses the complete representation. Do not stop when `bits` becomes zero: the remaining leading zeros still need to be appended to the result.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `reverseBits(n)` | Return the integer represented by the reversed 32 bits |
| `std::uint32_t bits` | Store the input with unsigned shift behavior |
| `result << 1` | Make room at the right of the result |
| `bits & 1u` | Extract the next bit, either zero or one |
| Bitwise OR `\|` | Place that bit in the cleared position |
| `bits >>= 1` | Advance to the next input bit |
| `i < 32` | Include every bit, even leading zeros |

## Walkthrough

A four-bit illustration makes the same operation easier to follow. The actual code always performs 32 iterations.

```text
Input: 1100

Read rightmost bit    Result after shift and append
0                     0000
0                     0000
1                     0001
1                     0011
```

For the actual 32-bit input `12`, the result is `805306368`:

```text
00000000000000000000000000001100
00110000000000000000000000000000
```

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `&` extracts a bit; `|` inserts it. These are bitwise operators, not `&&` or `||`.
- `<< 1` shifts left by one position; `>> 1` shifts right by one position.
- `1u` is an unsigned integer literal.
- Use unsigned storage while shifting to avoid signed-shift pitfalls.
- The current even-input constraint ensures the reversed highest bit is zero, so the result fits a positive signed 32-bit integer or zero. Converting the result back to `int` is safe under this contract.
- Older unsigned versions of this problem may use `uint32_t reverseBits(uint32_t n)`; adapt the public signature and return type to that judge rather than using signed output for arbitrary 32-bit patterns.
- The input is passed by value; all state is local for repeated calls.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `43261596` | `964176192` | Mixed bits from the first example |
| `2147483644` | `1073741822` | Many adjacent set bits |
| `0` | `0` | All zero bits |
| `2` | `1073741824` | Leading zeros must be processed |
| `2^k`, with `1 <= k <= 30` | `2^(31-k)` | Individual bit positions |
| `2147483646` | `2147483646` | Maximum valid input and symmetric pattern |
| `0x55555554` | `0x2AAAAAAA` | Alternating bits |

Tests compare all even inputs through `65534` and 1000 deterministic random valid inputs against a reference that reverses a 32-character binary string. They also check that reversing twice restores the input. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o reverse-bits-test
./reverse-bits-test
```

## Complexity

**Time:** O(32), or O(1) for a fixed-width integer.\
**Auxiliary space:** O(1), storing the remaining bits, result, and loop counter.
