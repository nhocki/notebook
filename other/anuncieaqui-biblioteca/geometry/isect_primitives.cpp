bool in_rect(pt a, pt b, pt c) {
    return sgn(c.x - min(a.x, b.x)) >= 0 && sgn(max(a.x, b.x) - c.x) >= 0 &&
        sgn(c.y - min(a.y, b.y)) >= 0 && sgn(max(a.y, b.y) - c.y) >= 0;
}
bool ps_isects(pt a, pt b, pt c) { return ccw(a,b,c) == 0 && in_rect(a,b,c); }

bool ss_isects(pt a, pt b, pt c, pt d) {
    if (ccw(a,b,c)*ccw(a,b,d) == -1 && ccw(c,d,a)*ccw(c,d,b) == -1) return true;
    return ps_isects(a, b, c) || ps_isects(a, b, d) ||
        ps_isects(c, d, a) || ps_isects(c, d, b);
}

pt parametric_isect(pt p, pt v, pt q, pt w) {
    double t = ((q-p)%w)/(v%w);
    return p + v*t;
}

pt ss_isect(pt p, pt q, pt r, pt s) {
    pt isect = parametric_isect(p, q-p, r, s-r);
    if(ps_isects(p, q, isect) && ps_isects(r, s, isect)) return isect;
    return pt(1/0.0, 1/0.0);
}
