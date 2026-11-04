# Minimum Operations to Make Elements Within K Subarrays Equal

![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)

## Problem

You are given an integer array `nums` and two integers, `x` and `k`. You can perform the following operation any number of times (**including zero**):

- Increase or decrease any element of nums by 1.

Return the  **minimum**  number of operations needed to have  **at least**  `k`  *non-overlapping subarrays*  of size  **exactly**  `x` in `nums`, where all elements within each subarray are equal.

 

 **Example 1:** 

 **Input:**  nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2

 **Output:**  8

 **Explanation:** 

- Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
- Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
- Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.

 **Example 2:** 

 **Input:**  nums = [9,-2,-2,-2,1,5], x = 2, k = 2

 **Output:**  3

 **Explanation:** 

- Use 3 operations to subtract 3 from nums[4]. The resulting array is [9, -2, -2, -2, -2, 5].
- Now, all elements within each subarray [-2, -2] (from indices 1 to 2) and [-2, -2] (from indices 3 to 4) are equal. Since 3 operations were used, 3 is the output.

 

 **Constraints:** 

- 2 <= nums.length <= 105
- -106 <= nums[i] <= 106
- 2 <= x <= nums.length
- 1 <= k <= 15
- 2 <= k * x <= nums.length

## Solution

**Language:** C++  
**Runtime:** 1723 ms (beats 6.25%)  
**Memory:** 480 MB (beats 6.25%)  
**Submitted:** 2026-11-04T15:42:16.700Z  

```cpp
class MedianCost {
    multiset<int> l, r;
    long long s1 = 0, s2 = 0;

public:
    void adjust() {
        while ((long long) l.size() - (long long) r.size() > 1) {
            int v = *l.rbegin();
            l.erase(prev(l.end()));
            s1 -= v;
            r.insert(v);
            s2 += v;
        }
        while (r.size() > l.size()) {
            int v = *r.begin();
            r.erase(r.begin());
            s2 -= v;
            l.insert(v);
            s1 += v;
        }
    }

    void add(int x) {
        r.insert(x);
        s2 += x;
        int y = *r.begin();
        r.erase(r.begin());
        s2 -= y;
        l.insert(y);
        s1 += y;
        adjust();
    }

    void remove(int x) {
        auto it = l.find(x);
        if (it != l.end()) {
            l.erase(it);
            s1 -= x;
        } else {
            r.erase(r.find(x));
            s2 -= x;
        }
        adjust();
    }

    long long query() {
        long long mid = *l.rbegin();
        return (long long) l.size() * mid - s1 + s2 - (long long) r.size() * mid;
    }
};

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> f(n + 1, vector<long long>(k + 1, INF));
        f[0][0] = 0;

        MedianCost mc;
        for (int i = 1; i <= n; ++i) {
            mc.add(nums[i - 1]);
            long long w = mc.query();

            for (int j = 0; j <= k; ++j) {
                f[i][j] = f[i - 1][j];
                if (j > 0 && i >= x) {
                    f[i][j] = min(f[i][j], f[i - x][j - 1] + w);
                }
            }

            if (i >= x) {
                mc.remove(nums[i - x]);
            }
        }
        return f[n][k];
    }
};
```

---

[View on LeetCode](https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/)