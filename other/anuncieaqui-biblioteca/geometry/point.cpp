typedef double TYPE;
const TYPE EPS = 1e-9, INF = 1e9;

inline int sgn(TYPE a) { return a > EPS ? 1 : (a < -EPS ? -1 : 0); }
inline int cmp(TYPE a, TYPE b) { return sgn(a - b); }

struct pt {
    TYPE x, y;
    pt(TYPE x = 0, TYPE y = 0) : x(x), y(y) { }

    bool operator==(pt p) { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }
    bool operator<(pt p) const {
        return cmp(x, p.x) ? cmp(x, p.x) < 0 : cmp(y, p.y) < 0;
    }
    bool operator<=(pt p) { return *this < p || *this == p; }
    TYPE operator||(pt p) { return x*p.x + y*p.y; }
    TYPE operator%(pt p) { return x*p.y - y*p.x; }
    pt operator~() { return pt(x, -y); }
    pt operator+(pt p) { return pt(x + p.x, y + p.y); }
    pt operator-(pt p) { return pt(x - p.x, y - p.y); }
    pt operator*(pt p) { return pt(x*p.x - y*p.y, x*p.y + y*p.x); }
    pt operator/(TYPE t) { return pt(x/t, y/t); }
    pt operator/(pt p) { return (*this * ~p)/(p||p); }
};
const pt I = pt(0,1);

struct circle {
    pt c; TYPE r;
    circle(pt c, TYPE r) : c(c), r(r) { }
};

TYPE norm(pt a) { return a||a; }
TYPE abs(pt a) { return sqrt(a||a); }
TYPE dist(pt a, pt b) { return abs(a - b); }
TYPE area(pt a, pt b, pt c) { return (a-c)%(b-c); }
int ccw(pt a, pt b, pt c) { return sgn(area(a, b, c)); }
pt unit(pt a) { return a/abs(a); }
double arg(pt a) { return atan2(a.y, a.x); }
pt f_polar(TYPE mod, double ang) { return pt(mod * cos(ang), mod * sin(ang)); }
inline int g_mod(int i, int n) { if(i == n) return 0; return i; }

ostream& operator<<(ostream& o, pt p) {
    return o << "(" << p.x << "," << p.y << ")";
}
