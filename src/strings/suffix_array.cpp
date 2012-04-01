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

////////////////////////////////////////////////////////////////

// Applications:

// lcp(x,y) = min(lcp(x,x+1), lcp(x+1, x+2), ... , lcp(y-1, y))

void number_of_different_substrings(){
  // If you have the i-th smaller suffix, Si,
  //    it's length will be |Si| = n - sa[i]
  // Now, lcp[i] stores the number of
  //     common letters between Si and Si-1
  //     (s.substr(sa[i]) and s.substr(sa[i-1]))
  // so, you have |Si| - lcp[i] different strings
  //    from these two suffixes => n - lcp[i] - sa[i]
  for(int i = 0; i < n; ++i) ans += n - sa[i] - lcp[i];
}

void number_of_repeated_substrings(){
  // Number of substrings that appear at least twice in the text.
  // The trick is that all 'spare' substrings that can give us 
  // Lcp(i - 1, i) can be obtained by Lcp(i - 2, i - 1) 
  // due to the ordered nature of our array.
  // And the overall answer is 
  // Lcp(0, 1) + 
  //     Sum(max[0, Lcp(i, i - 1) - Lcp(i - 2, i - 1)])
  //     for 2 <= i < n
  // File Recover 
  int cnt = lcp[1];
  for(int i=2; i < n; ++i){
    cnt += max(0, lcp[i] - lcp[i-1]);
  }
}


void repeated_m_times(int m){
  // Given a string s and an int m, find the size
  // of the biggest substring repeated m times (find the rightmost pos)
  // if a string is repeated m+1 times, then it's repeated m times too
  // The answer is the maximum, over i, of the longest common prefix
  // between suffix i+m-1 in the sorted array.
  int length = 0, position = -1, t;
  for (int i = 0; i <= n-m; ++i){
    if ((t = getLcp(i, i+m-1, n)) > length){
      length = t;
      position = sa[i];
    } else if (t == length) { position = max(position, sa[i]); }
  }
  // Here you'll get the rightmost position
  // (that means, the last time the substring appears)
  for (int i = 0; i < n; ){
    if (sa[i] + length > n) { ++i; continue; }
    int ps = 0, j = i+1;
    while (j <n && lcp[j] >= length){
      ps = max(ps, sa[j]);
      j++;
    }
    if(j - i >= m) position = max(position, ps);
    i = j;
  }
  if(length != 0)
    printf("%d %d\n", length, position);
  else
    puts("none");
}


void smallest_rotation(){
  // Reads a string of lenght k. Then just double it (s = s+s) 
  // and find the suffix array.
  // The answer is the smallest i for which s.size() - sa[i] >= k
  // If you want the first appearence (and not the string)
  // you'll need the second cycle
  int best = 0;
  for (int i=0; i < n; ++i){
    if (n - sa[i] >= k){
      //Find the first appearence of the string
      while (n - sa[i] >= k){
        if(sa[i] < sa[best] && sa[i] != 0) best = i;
        i++;
      }
      break;
    }
  }
  if (sa[best] == k) puts("0");
  else printf("%d\n", sa[best]);
}