# Palindromic Path Queries in a Tree

![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red)

## Problem

You are given an undirected tree with `n` nodes labeled 0 to `n - 1`. This is represented by a 2D array `edges` of length `n - 1`, where `edges[i] = [ui, vi]` indicates an undirected edge between nodes `ui` and `vi`.

You are also given a string `s` of length `n` consisting of lowercase English letters, where `s[i]` represents the character assigned to node `i`.

You are also given a string array `queries`, where each `queries[i]` is either:

- "update ui c": Change the character at node ui to c. Formally, update s[ui] = c.
- "query ui vi": Determine whether the string formed by the characters on the unique path from ui to vi (inclusive) can be rearranged into a palindrome.

Return a boolean array `answer`, where `answer[j]` is `true` if the `jth` query of type `"query ui vi"​​​​​​​` can be rearranged into a  **palindrome**, and `false` otherwise.

 

 **Example 1:** 

 **Input:**  n = 3, edges = [[0,1],[1,2]], s = "aac", queries = ["query 0 2","update 1 b","query 0 2"]

 **Output:**  [true,false]

 **Explanation:** 

- "query 0 2": Path 0 → 1 → 2 gives "aac", which can be rearranged to form "aca", a palindrome. Thus, answer[0] = true.
- "update 1 b": Update node 1 to 'b', now s = "abc".
- "query 0 2": Path characters are "abc", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.

Thus, `answer = [true, false]`.

 **Example 2:** 

 **Input:**  n = 4, edges = [[0,1],[0,2],[0,3]], s = "abca", queries = ["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]

 **Output:**  [false,false,true]

 **Explanation:** 

- "query 1 2": Path 1 → 0 → 2 gives "bac", which cannot be rearranged to form a palindrome. Thus, answer[0] = false.
- "update 0 b": Update node 0 to 'b', now s = "bbca".
- "query 2 3": Path 2 → 0 → 3 gives "cba", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.
- "update 3 a": Update node 3 to 'a', s = "bbca".
- "query 1 3": Path 1 → 0 → 3 gives "bba", which can be rearranged to form "bab", a palindrome. Thus, answer[2] = true.

Thus, `answer = [false, false, true]`.

 

 **Constraints:** 

- 1 <= n == s.length <= 5 * 104
- edges.length == n - 1
- edges[i] = [ui, vi]
- 0 <= ui, vi <= n - 1
- s consists of lowercase English letters.
- The input is generated such that edges represents a valid tree.
- 1 <= queries.length <= 5 * 104​​​​​​​queries[i] = "update ui c" or queries[i] = "query ui vi" 0 <= ui, vi <= n - 1 c is a lowercase English letter.

## Solution

**Language:** C++  
**Runtime:** 342 ms (beats 71.59%)  
**Memory:** 328.2 MB (beats 46.59%)  
**Submitted:** 2026-10-29T13:17:26.117Z  

```cpp
class BinaryIndexedTree {
    int n;
    vector<int> tree;

public:
    BinaryIndexedTree(int n)
        : n(n)
        , tree(n + 1) {}

    void update(int i, int delta) {
        for (++i; i <= n; i += i & -i) {
            tree[i] ^= delta;
        }
    }

    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res ^= tree[i];
        }
        return res;
    }
};

class Solution {
    vector<vector<int>> g, up;
    vector<int> parent, depth, tin, tout, bit;
    int timer, m;

    void dfs(int u, int p) {
        parent[u] = p == -1 ? 0 : p;
        tin[u] = timer++;
        for (int v : g[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
        tout[u] = timer;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int j = 0; d; j++, d >>= 1) {
            if (d & 1) {
                u = up[j][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int j = m - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }
        return parent[u];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        g.assign(n, {});
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        parent.resize(n);
        depth.assign(n, 0);
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        dfs(0, -1);

        m = 32 - __builtin_clz(n);
        up.assign(m, vector<int>(n));
        up[0] = parent;
        for (int j = 1; j < m; j++) {
            for (int i = 0; i < n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        bit.resize(n);
        for (int i = 0; i < n; i++) {
            bit[i] = 1 << (s[i] - 'a');
        }

        BinaryIndexedTree tree(n);
        for (int i = 0; i < n; i++) {
            tree.update(tin[i], bit[i]);
            tree.update(tout[i], bit[i]);
        }

        vector<bool> ans;
        for (string& q : queries) {
            stringstream ss(q);
            string op;
            int u;
            ss >> op >> u;
            if (op == "update") {
                string c;
                ss >> c;
                int y = 1 << (c[0] - 'a');
                if (bit[u] != y) {
                    int delta = bit[u] ^ y;
                    tree.update(tin[u], delta);
                    tree.update(tout[u], delta);
                    bit[u] = y;
                }
            } else {
                int v;
                ss >> v;
                int w = lca(u, v);
                int mask = tree.query(tin[u] + 1) ^ tree.query(tin[v] + 1) ^ bit[w];
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }
        return ans;
    }
};
```

---

[View on LeetCode](https://leetcode.com/problems/palindromic-path-queries-in-a-tree/)