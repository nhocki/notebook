typedef long double Double;
typedef vector <Point> Polygon;

// This is not standard intersection because it returns false
// when the intersection point is exactly the t=1 endpoint of
// the segment. This is OK for this algorithm but not for general
// use.
bool segment_line_intersection(Double x0, Double y0,
    Double x1, Double y1, Double x2, Double y2,
    Double x3, Double y3, Double &x, Double &y){
        
    Double t0 = (y3-y2)*(x0-x2) - (x3-x2)*(y0-y2);
    Double t1 = (x1-x0)*(y2-y0) - (y1-y0)*(x2-x0);
    Double det =(y1-y0)*(x3-x2) - (y3-y2)*(x1-x0);
    
    if (fabs(det) < EPS){
        //Paralelas
        return false;
    }else{
        t0 /= det;
        t1 /= det;
        if (cmp(0, t0) <= 0 and cmp(t0, 1) < 0){
            x = x0 + t0 * (x1-x0);
            y = y0 + t0 * (y1-y0);
            return true;
        }
        return false;
    }
}

// Returns the polygons that result of cutting the CONVEX
// polygon p by the infinite line that passes through (x0, y0)
// and (x1, y1).
// The returned value has either 1 element if this line
// doesn't cut the polygon at all (or barely touches it)
// or 2 elements if the line does split the polygon.
vector<Polygon> split(const Polygon &p, Double x0, Double y0,
                      Double x1, Double y1) {
    int hits = 0, side = 0;
    Double x, y;
    vector<Polygon> ans(2);
 
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        if (segment_line_intersection(p[i].x, p[i].y,
            p[j].x, p[j].y,   x0, y0, x1, y1,   x, y)) {
            hits++;
            ans[side].push_back(p[i]);
            if (cmp(p[i].x, x) != 0 or cmp(p[i].y, y) != 0) {
                ans[side].push_back(Point(x, y));
            }
            side ^= 1;
            ans[side].push_back(Point(x, y));
        } else {
            ans[side].push_back(p[i]);
        }
    }
    return hits < 2 ? vector<Polygon>(1, p) : ans;
}
