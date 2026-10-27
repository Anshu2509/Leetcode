# Create Grid With Exactly One Path

![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green)

## Problem

You are given two integers `m` and `n`, representing the number of rows and columns of a grid.

Construct  **any**  `m x n` grid consisting only of the characters `'.'` and `'#'`, where:

- '.' represents a free cell.
- '#' represents an obstacle cell.

A  **valid path**  is a sequence of free cells that:

- Starts at the top-left cell (0, 0).
- Ends at the bottom-right cell (m - 1, n - 1).
- Moves only: Right, from (i, j) to (i, j + 1), or Down, from (i, j) to (i + 1, j).

Return any grid such that there is  **exactly one valid path**  from the top-left cell to the bottom-right cell.

 

 **Example 1:** 

 **Input:**  m = 2, n = 3

 **Output:**  ["..#","#.."]

 **Explanation:** 

The only valid path is: `(0,0) → (0,1) → (1,1) → (1,2)`

 **Example 2:** 

 **Input:**  m = 3, n = 3

 **Output:**  ["..#","#..","##."]

 **Explanation:** 

The only valid path is: `(0,0) → (0,1) → (1,1) → (1,2) → (2,2)`

 **Example 3:** 

 **Input:**  m = 1, n = 4

 **Output:**  ["...."]

 **Explanation:** 

The only valid path is: `(0,0) → (0,1) → (0,2) → (0,3)`

 

 **Constraints:** 

- 1 <= m, n <= 25

## Solution

**Language:** C++  
**Runtime:** 2 ms (beats 45.48%)  
**Memory:** 11.2 MB (beats 50.17%)  
**Submitted:** 2026-10-27T15:49:34.712Z  

```cpp
class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> g(m, string(n, '#'));

        g[0] = string(n, '.');

        for (int i = 0; i < m; i++) {
            g[i][n - 1] = '.';
        }

        return g;
    }
};
```

---

[View on LeetCode](https://leetcode.com/problems/create-grid-with-exactly-one-path/)