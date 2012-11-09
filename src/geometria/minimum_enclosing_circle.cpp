// Complexity is O(n) (expected)

const int MAXN = 100005;

struct Point {
    double x,y; Point(){} Point(double x, double y) : x(x), y(y){}
    double length() const { return sqrtl(x*x + y*y); }
};

Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}
Point operator / (const Point &a, double s) {
    return Point(a.x / s, a.y / s);
}   
double operator ^ (const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double operator * (const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

// Real algorithm starts below
typedef pair<Point, double> Circle;

bool in_circle(Circle c, Point p){
    return cmp((p - c.first).length(), c.second) <= 0;
}

Point circumcenter(Point p, Point q, Point r) {
    Point a = p - r, b = q - r;
    Point c = Point(a * (p + r) / 2, b * (q + r) / 2);
    double x = c ^ Point(a.y, b.y);
    double y = Point(a.x, b.x) ^ c;
    double d = a ^ b;
    return Point(x, y) / d;
}

Point T[MAXN];

// Fill T with the points and call spanning_circle(n).
Circle spanning_circle(int n) {
    random_shuffle(T, T + n);
    Circle ans(Point(0, 0), -INFINITY);
    for (int i = 0; i < n; i++) {
        if (!in_circle(ans, T[i])) {
            ans = Circle(T[i], 0);
            for (int j = 0; j < i; j++) {
                if (!in_circle(ans, T[j])) {
                    ans = Circle( (T[i] + T[j]) / 2, 
                                  (T[i] - T[j]).length() / 2);
                    for (int k = 0; k < j; k++) {
                        if (!in_circle(ans, T[k])) {
                            Point o = circumcenter(T[i], T[j],
                                                   T[k]);
                            ans = Circle(o, (o - T[k]).length());
                        }
                    }
                }
            }
        }
    }
    return ans;
}
