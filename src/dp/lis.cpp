// Longest Increasing Subsequence.
// O(n log n)

const int INF  = 1 << 30 - 1;

int main(){
  int n;
  while(scanf("%d", &n) == 1){
    vector<long> S(n);
    vector<long> M(n+1, INF);
    for (int i = 0; i < n; ++i) scanf("%ld", &S[i]);
    M[0] = 0;
    int m = 0;
    for (int i = 0; i < S.size(); ++i){
      int d = upper_bound(M.begin(), M.begin() + n, S[i]) - M.begin();
      if (S[i] != M[d-1]){
        M[d] = S[i];
        m = max(m,d);
        parent[S[i]] = M[d-1];
      }
    }
    printf("%d\n", max(1, m));
  }
  return 0;
}