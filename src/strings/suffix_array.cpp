// Complexity: O(n log n)

//Usage: Call SuffixArray::compute(s), where s is the
//       string you want the Suffix Array for.
 
//Output:
// sa   = The suffix array. Contains the n suffixes of s sorted
//        in lexicographical order. Each suffix is represented
//        as a single integer (the position in the string
//        where it starts).
// rank = The inverse of the suffix array. rank[i] = the index
//        of the suffix s[i..n) in the pos array. (In other
//        words, sa[i] = k <==> rank[k] = i).
//        With this array, you can compare two suffixes in O(1):
//        Suffix s[i..n) is smaller than s[j..n) if and
//        only if rank[i] < rank[j].
// lcp  = The length of the longest common prefix between two
//        consecutive suffixes:
//        lcp[i] = lcp(s + sa[i], s + sa[i-1]). lcp[0] = 0.

namespace SuffixArray {
    int t, rank[MAXN], sa[MAXN], lcp[MAXN];

    bool compare(int i, int j){
        return rank[i + t] < rank[j + t];
    }
    
    void build(const string &s){
        int n = s.size();
        int bc[256];
        for (int i = 0; i < 256; ++i) bc[i] = 0;
        for (int i = 0; i < n; ++i) ++bc[s[i]];
        for (int i = 1; i < 256; ++i) bc[i] += bc[i-1];
        for (int i = 0; i < n; ++i) sa[--bc[s[i]]] = i;
        for (int i = 0; i < n; ++i) rank[i] = bc[s[i]];
        for (t = 1; t < n; t <<= 1){
            for (int i = 0, j = 1; j < n; i = j++){
                while (j < n && rank[sa[j]] == rank[sa[i]]) j++;
                if (j - i == 1) continue;
                int *start = sa + i, *end = sa + j;
                sort(start, end, compare);
                int first = rank[*start + t], num = i, k;
                for(; start < end; rank[*start++] = num){
                    k = rank[*start + t];
                    if (k != first and (i > first or k >= j))
                        first = k, num = start - sa;
                }
            }
        }
        // Remove this part if you don't need the LCP
        int size = 0, i, j;
        for(i = 0; i < n; i++) if (rank[i] > 0) {
            j = sa[rank[i] - 1];
            while(s[i + size] == s[j + size]) ++size;
            lcp[rank[i]] = size;
            if (size > 0) --size;
        }
        lcp[0] = 0;
    }
};