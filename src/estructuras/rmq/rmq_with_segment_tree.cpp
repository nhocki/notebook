// Usage:
// N - Set to size of the array.
// height - Fill with the data you want to run RMQ on.
//
// You might want to redefine the "better" function if
// you are using a different comparison operator (For 
// example, to solve Range Maximum Query)
//
//
// SegmentTree::build(0, 0, N - 1); // Preprocess
// SegmentTree::get(0, 0, N - 1, i, j); // Returns the index
//                                      // of the smallest value
//                                      // in range [i, j]
//

int height[MAXN];
int N;

namespace SegmentTree {
    int tree[1 << 18];
    
    int better(int a, int b) {
        assert(0 <= a and a < N and 0 <= b and b < N);
        return height[a] <= height[b] ? a : b;
    }
    
    int build(int u, int l, int r) {
        if (l == r) return tree[u] = l;
        int m = (l + r) / 2;
        int a = build(2*u+1, l, m);
        int b = build(2*u+2, m+1, r);
        return tree[u] = better(a, b);
    }
    
    // Returns the INDEX of the best element in range [p, q]
    int get(int u, int l, int r, int p, int q) {
        assert(l <= p and q <= r and p <= q);
        if (l == p and r == q) return tree[u];
        int m = (l + r) / 2;
        if (q <= m) return get(2*u+1, l, m, p, q);
        if (m + 1 <= p) return get(2*u+2, m+1, r, p, q);
        int a = get(2*u+1, l, m, p, m);
        int b = get(2*u+2, m+1, r, m+1, q);
        return better(a, b);
    }
};

