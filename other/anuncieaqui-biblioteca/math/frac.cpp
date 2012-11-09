struct frac {
    long long num, den;
    frac(long long num = 0, long long den = 1) { set_val(num, den); }

    void set_val(long long _num, long long _den) {
        num = _num/__gcd(_num, _den);
        den = _den/__gcd(_num, _den);
        if(den < 0) { num *= -1; den *= -1; }
    }

    void operator*=(frac f) { set_val(num * f.num, den * f.den); }
    void operator+=(frac f) { set_val(num * f.den + f.num * den, den * f.den); }
    void operator-=(frac f) { set_val(num * f.den - f.num * den, den * f.den); }
    void operator/=(frac f) { set_val(num * f.den, den * f.num); }
};

bool operator==(frac a, frac b) { return a.num * b.den == b.num * a.den; }
bool operator!=(frac a, frac b) { return !(a == b); }
bool operator<(frac a, frac b) { return a.num * b.den < b.num * a.den; }
bool operator<=(frac a, frac b) { return (a == b) || (a < b); }
bool operator>(frac a, frac b) { return !(a <= b); }
bool operator>=(frac a, frac b) { return !(a < b); }
frac operator/(frac a, frac b) { frac ret = a; ret /= b; return ret; }
frac operator*(frac a, frac b) { frac ret = a; ret *= b; return ret; }
frac operator+(frac a, frac b) { frac ret = a; ret += b; return ret; }
frac operator-(frac a, frac b) { frac ret = a; ret -= b; return ret; }
frac operator-(frac f) { return 0 - f; }

std::ostream& operator<<(std::ostream& o, const frac f) {
    o << f.num << "/" << f.den;
    return o;
}

