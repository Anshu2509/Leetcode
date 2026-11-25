# Smallest Unique Subarray

![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)

## Problem

You are given an integer array `nums`.

Find the  **minimum** length of a subarray that is  **not**   **identical**  to any other  **subarray**  in `nums`.

Return an integer denoting the  **minimum possible length**  of such a  **subarray**.

Two  **subarrays**  are considered identical if they have the same length and the same elements in corresponding positions.

 

Original
Python3
 **Example 1:** 

 **Input:**  nums = [3,3,3]

 **Output:**  3

 **Explanation:** 

- Subarrays of length 1: [3] → appears 3 times
- Subarrays of length 2: [3, 3] → appears 2 times
- Subarrays of length 3: [3, 3, 3] → appears once

The subarray `[3, 3, 3]` is unique, so the smallest unique subarray length is 3.

 **Example 2:** 

 **Input:**  nums = [2,1,2,3,3]

 **Output:**  1

 **Explanation:** 

Subarrays of length 1:

- [2] → appears 2 times
- [1] → appears once
- [3] → appears 2 times
The subarray `[1]` is unique, so the smallest unique subarray length is 1.

 **Example 3:** 

 **Input:**  nums = [1,1,2,2,1]

 **Output:**  2

 **Explanation:** 

Subarrays of length 1:

- [1] → appears 3 times
- [2] → appears 2 times

Subarrays of length 2:

- [1, 1] → appears once
- [1, 2] → appears once
- [2, 2] → appears once
- [2, 1] → appears once
There is at least one subarray of length 2 that is unique, so the smallest unique subarray length is 2.

 

 **Constraints:** 

- 1 <= nums.length <= 105
- 1 <= nums[i] <= 105

## Solution

**Language:** Python  
**Runtime:** 4159 ms (beats 7.27%)  
**Memory:** 41.8 MB (beats 65.45%)  
**Submitted:** 2026-11-25T11:36:48.719Z  

```py
class Solution:
    def smallestUniqueSubarray(self, nums: list[int]) -> int:
        self.nums = nums

        self.base = 19
        self.modulo = 10**9 + 7
        self.powers = [1] * (len(nums) + 1)

        self.hash_values: dict[int, int] = dict()

        min_possible_len = len(nums)  # Base case.

        min_len, max_len = 1, len(nums)  # For binary search usage.

        while min_len <= max_len:
            mid_len = (min_len + max_len) // 2

            if self._check_uniqueness(mid_len):
                if mid_len < min_possible_len:
                    min_possible_len = mid_len
                max_len = mid_len - 1

            else:
                min_len = mid_len + 1

        return min_possible_len

    def _check_uniqueness(self, subarray_len: int) -> bool:
        # Only need to reset leftmost power to 1 before usage.
        self.powers[0] = 1  # Because powers are calculated by bottom-up.

        for idx in range(1, len(self.nums) + 1):
            self.powers[idx] = (self.powers[idx - 1] * self.base) % self.modulo

        current_hash = 0
        for idx in range(subarray_len):
            current_hash *= self.base
            current_hash += self.nums[idx]
            current_hash %= self.modulo

        self.hash_values.clear()  # Clear before usage.
        self.hash_values[current_hash] = 1

        for idx in range(1, len(self.nums) - subarray_len + 1):
            # Window shifts: deduct leftmost num's share from hash value.
            current_hash -= self.powers[subarray_len - 1] * self.nums[idx - 1]

            # Integrate newly added num's share into hash value.
            current_hash *= self.base
            current_hash += self.nums[idx + subarray_len - 1]
            current_hash %= self.modulo

            if current_hash not in self.hash_values.keys():
                self.hash_values.update({current_hash: 0})
            self.hash_values[current_hash] += 1

        return 1 in self.hash_values.values()
```

---

[View on LeetCode](https://leetcode.com/problems/smallest-unique-subarray/)