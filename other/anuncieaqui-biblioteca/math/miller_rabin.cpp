int fastpow(int base, int d, int n) {
    int ret = 1;
    for(long long pow = base; d > 0; d >>= 1, pow = (pow * pow) % n)
        if(d & 1)
            ret = (ret * pow) % n;
    return ret;
}

bool miller_rabin(int n, int base) {
    if(n <= 1) return false;
    if(n % 2 == 0) return n == 2;

    int s = 0, d = n - 1;
    while(d % 2 == 0) d /= 2, ++s;

    int base_d = fastpow(base, d, n);
    if(base_d == 1) return true;
    int base_2r = base_d;

    for(int i = 0; i < s; ++i) {
        if(base_2r == 1) return false;
        if(base_2r == n - 1) return true;
        base_2r = (long long)base_2r * base_2r % n;
    }

    return false;
}

bool isprime(int n) {
    if(n == 2 || n == 7 || n == 61) return true;
    return miller_rabin(n, 2) && miller_rabin(n, 7) && miller_rabin(n, 61);
}
