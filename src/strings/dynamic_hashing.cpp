// N = size of the array. It is assumed that elements are
//     indexed from 1 to N, inclusive.
// B = the base for the hash. Must be > 0.
// P = The modulo for the hash. Must be > 0. Doesn't need
//     to be prime.
int N, B, P;

int tree[MAXN], base[MAXN];

void precomputeBases() {
    base[0] = 1;
    for (int i = 1; i <= N + 1; ++i) {
        base[i] = (1LL * base[i - 1] * B) % P;
    }
}

inline int mod(long long a) {
    int ans = a % P;
    if (ans < 0) ans += P;
    return ans;
}

// Usually you don't want to use this function directly,
// use 'put' below instead.
void add(int at, int what) {
    what = mod(what);
    int seen = 0;
    for (at++; at <= N + 1; at += at & -at) {
        tree[at] += (1LL * what * base[seen]) % P;
        tree[at] = mod(tree[at]);
        seen += at & -at;
    }
}

// Returns the hash for subarray [1..at].
int query(int at) {
    int ans = 0, seen = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += (1LL * tree[at] * base[seen]) % P;
        ans = mod(ans);
        seen += at & -at;
    }
    return ans;
}

// Returns the hash for subarray [i..j]. That hash is:
//   a[i]*B^(j-i+1) + a[i+1]*Bˆ(j-i) + a[i+2]*B^(j-i-1) + ...
// + a[j-2]*B^2 + a[j-1]*B^1 + a[j]*B^0 (mod P)
int hash(int i, int j) {
    assert(i <= j);
    int ans = query(j) - (1LL * query(i-1) * base[j-i+1]) % P;
    return mod(ans);
}

// Changes the number or char at position 'at' for 'what'.
void put(int at, int what) {
    add(at, -hash(at, at) + what);
}
