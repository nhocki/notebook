bool point_circle(pt p, circle c) {
    return cmp(abs(p - c.c), c.r) <= 0;
}

double ps_distance(pt p, pt a, pt b) {
    p = p - a; b = b - a;
    double coef = min(max((b||p)/(b||b), TYPE(0)), TYPE(1));
    return abs(p - b*coef);
}

pt circumcenter(pt a, pt b, pt c) {
    return parametric_isect((b+a)/2, (b-a)*I, (c+a)/2, (c-a)*I);
}

bool compy(pt a, pt b) {
    return cmp(a.y, b.y) ? cmp(a.y, b.y) < 0 : cmp(a.x, b.x) < 0;
}
bool compx(pt a, pt b) { return a < b; }
