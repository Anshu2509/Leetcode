# Find Subtree Sizes After Changes

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow)

## Problem

You are given a tree rooted at node 0 that consists of `n` nodes numbered from `0` to `n - 1`. The tree is represented by an array `parent` of size `n`, where `parent[i]` is the parent of node `i`. Since node 0 is the root, `parent[0] == -1`.

You are also given a string `s` of length `n`, where `s[i]` is the character assigned to node `i`.

We make the following changes on the tree  **one**  time  **simultaneously**  for all nodes `x` from `1` to `n - 1`:

- Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].
- If node y does not exist, do nothing.
- Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.

Return an array `answer` of size `n` where `answer[i]` is the  **size**  of the subtree rooted at node `i` in the  **final**  tree.

 

Original
C++
 **Example 1:** 

 **Input:**  parent = [-1,0,0,1,1,1], s = "abaabc"

 **Output:**  [6,3,1,1,1,1]

 **Explanation:** 

The parent of node 3 will change from node 1 to node 0.

 **Example 2:** 

 **Input:**  parent = [-1,0,4,0,1], s = "abbba"

 **Output:**  [5,2,1,1,1]

 **Explanation:** 

The following changes will happen at the same time:

- The parent of node 4 will change from node 1 to node 0.
- The parent of node 2 will change from node 4 to node 1.

 

 **Constraints:** 

- n == parent.length == s.length
- 1 <= n <= 105
- 0 <= parent[i] <= n - 1 for all i >= 1.
- parent[0] == -1
- parent represents a valid tree.
- s consists only of lowercase English letters.

## Solution

**Language:** C++  
**Runtime:** 239 ms (beats 93.67%)  
**Memory:** 196.9 MB (beats 97.47%)  
**Submitted:** 2026-11-21T16:20:13.436Z  

```cpp
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = s.size();
        vector<int> g[n];
        vector<int> d[26];
        for (int i = 1; i < n; ++i) {
            g[parent[i]].push_back(i);
        }
        vector<int> ans(n);
        auto dfs = [&](this auto&& dfs, int i, int fa) -> void {
            ans[i] = 1;
            int idx = s[i] - 'a';
            d[idx].push_back(i);
            for (int j : g[i]) {
                dfs(j, i);
            }
            int k = d[idx].size() > 1 ? d[idx][d[idx].size() - 2] : fa;
            if (k >= 0) {
                ans[k] += ans[i];
            }
            d[idx].pop_back();
        };
        dfs(0, -1);
        return ans;
    }
};
```

---

[View on LeetCode](https://leetcode.com/problems/find-subtree-sizes-after-changes/)