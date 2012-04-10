// Assumes gcd(a, n) == 1 and a > 0.
// Returns v such that a * v == 1 (mod n).
long long mod_inverse(long long a, long long n) {
    long long i = n, v = 0, d = 1;
    while (a > 0) {
        long long t = i / a, x = a;
        a = i % x;
        i = x;
        x = d;
        d = v - t * x;
        v = x;
    }
    v %= n;
    if (v < 0) v += n;
    return v;
}
