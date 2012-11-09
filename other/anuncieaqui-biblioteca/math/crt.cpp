struct t {
    long long a, b; int g;
    t(long long a, long long b, int g) : a(a), b(b), g(g) { }
    t swap() { return t(b, a, g); }
};

t egcd(int p, int q) {
    if(q == 0) return t(1, 0, p);

    t t2 = egcd(q, p % q);
    t2.a -= t2.b * (p/q);
    return t2.swap();
}

int crt(int a, int p, int b, int q) {
    t t2 = egcd(p, q); t2.a %= p*q; t2.b %= p*q;
    assert(t2.g == 1);
    int ret = ((b * t2.a)%(p*q) * p + (a * t2.b)%(p*q) * q) % (p*q);
    return ret >= 0 ? ret : ret + p*q;
}
