// Usage:
// Preprocessing in O(n log n):
//   - LCA::clear(number_of_nodes);
//   - LCA::add_edge(u, v) for every edge
//   - LCA::preprocess(number_of_nodes, root);
// Queries in O(log n):
//   - LCA::lca(u, v);

// Assumes the tree is connected. If it's not, 
// you might want to run the algorithm on every
//  component (but remember to check if the two
// nodes of a query are on the same component,
// otherwise there's no LCA).

namespace LCA {
    int tin[MAXN], tout[MAXN];
    vector<int> up[MAXN];
    vector<int> g[MAXN];
    // alternatively, you can use a global graph to save space.
    // This graph is only used inside LCA::dfs below.
    
    int L, timer;

    void clear(int n) {
        for (int i = 0; i < n; ++i) g[i].clear();
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= L; ++i)
            up[v][i] = up[up[v][i-1]][i-1];
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (to != p) dfs(to, v);
        }
        tout[v] = ++timer;
    }
    inline bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }
    int lca(int a, int b) {
        if (upper(a, b)) return a;
        if (upper(b, a)) return b;
        for (int i = L; i >= 0; --i)
            if (!upper(up[a][i], b))
                a = up[a][i];
        return up[a][0];
    }
    void preprocess(int n, int root) {
        L = 1;
        while ((1 << L) <= n) ++L;
        for (int i = 0; i < n; ++i) up[i].resize(L + 1);
        timer = 0;
        dfs(root, root);
    }
};
