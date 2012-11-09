typedef long double Double;

struct Point {
    Double x, y, z;
    Point(){}
    Point(Double x, Double y, Double z) : x(x), y(y), z(z) {}
                    
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y, z - p.z);
    }    
    
    Double length() const {
        return sqrtl(*this * *this);
    }

    // Dot product
    Double operator * (const Point &p) const {
        return x*p.x + y*p.y + z*p.z;
    }

    // Cross product
    Point operator ^ (const Point &v) const {
        return Point(y*v.z - v.y*z, -x*v.z + v.x*z, x*v.y - v.x*y);
    }
    
    void normalize() {
        Double d = length();
        x /= d; y /= d; z /= d;
    }
};

// Scalar times vector product
Point operator * (Double t, const Point &p) {
    return Point(t * p.x, t * p.y, t * p.z);
}

// Returns the shortest distance from point p to the segment
// from a to b.
// This works on 2D and 3D.
Double distance_point_to_segment(const Point &p, const Point &a,
                                 const Point &b) {
    Point u = b - a;
    Point v = p - a;
    Double t = (u * v) / (u * u);
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    // Actual closest point is a + t*(b - a).
    Point boom = a + t*u;
    return (boom - p).length();
}

// Returns the shortest distance between any point in the segment
// from a1 to b1 and any point in the segment from a2 to b2.
// Works in 2D and 3D.
Double distance_between_segments(const Point &a1, const Point &b1, 
                                 const Point &a2, const Point &b2){
    Point u = b1 - a1;
    Point v = b2 - a2;
    Point w = a1 - a2;

    Double a = u * u;
    Double b = u * v;
    Double c = v * v;
    Double d = u * w;
    Double e = v * w;
    
    Double den = a*c - b*b;
    Double t1, t2;

    if (cmp(den, 0.0) == 0) { // the lines are parallel
        t1 = 0;
        t2 = d / b;
    } else {
        t1 = (b * e - c * d) / den;
        t2 = (a * e - b * d) / den;
    }
    // The shortest distance between the two infinite lines happens
    // from:
    //   - On segment 1: p = a1 + t1 * (b1 - a1)
    //   - On segment 2: q = a2 + t2 * (b2 - a2)
    if (0 <= t1 and t1 <= 1 and 0 <= t2 and t2 <= 1) {
        // We were lucky, the closest distance between the two
        // infinite lines happens right inside both segments.
        Point p = a1 + t1 * u;
        Point q = a2 + t2 * v;
        return (p - q).length();
    } else {
        Double ans = distance_point_to_segment(a2, a1, b1);
        ans = min(ans, distance_point_to_segment(b2, a1, b1));
        ans = min(ans, distance_point_to_segment(a1, a2, b2));
        ans = min(ans, distance_point_to_segment(b1, a2, b2));        
        return ans;
    }
}

// Returns the shortest distance from point p to the plane defined
// by the three points [a, b, c].
// The distance is signed, and is == 0 if the point lies on the 
// plane, > 0 if the point is on one side of the plane and < 0 if
// the point is on the other side.
// Intended to use on 3D.
Double signed_distance_point_to_plane(const Point &p,
                 const Point &a, const Point &b, const Point &c) {
    Point n = (b - a) ^ (c - a);
    n.normalize();
    // If n * n == 0, at least two of the
    // triangle points are collinear and there's
    // no single plane defined by them.
    assert(cmp(n * n, 0) > 0);
    return (n * (p - a)) / (n * n);
}

// Returns the shortest distance from point p to the triangle
// defined by points t1, t2 and t3.
// Works in 2D and 3D.
Double distance_point_to_triangle(const Point &p,
            const Point &t1, const Point &t2, const Point &t3) {
    Point u = t2 - t1;
    Point v = t3 - t1;
    Point n = u ^ v; // plane normal

    // If n * n == 0, at least two of the
    // triangle points are collinear and there's
    // no single plane defined by them.
    assert( cmp(n * n, 0) > 0 );
        
    Double s = -(n * (p - t1)) / (n * n);
    // The intersection point between the plane and
    // its perpendicular line passing through p is at
    // p + s * n. This is the closest point to p that
    // lies on the plane.
    Point boom = p + s * n;
    
    // Let's check if boom lies inside the triangle.
    Point w = boom - t1;
    Point nv = n ^ v;
    Double a2 = (w * nv) / (u * nv);
    Point nu = n ^ u;
    Double a3 = (w * nu) / (v * nu);
    Double a1 = 1 - a2 - a3;
    
    // Here we have found the barycentric coordinates of point
    // boom on the plane.
    // That means that boom == a1*t1 + a2*t2 + a3*t3.
    if (0 <= a1 and a1 <= 1 and 0 <= a2 and a2 <= 1 and 
        0 <= a3 and a3 <= 1) {
        // The point is striclty inside the triangle or on its
        // border, so just return the distance from p to the
        // intersection point.
        return (boom - p).length();
    } else { 
        // The point is on the plane, but outside the triangle,
        // so the shortest distance is with one of the borders
        // of the triangle.
        Double ans = distance_point_to_segment(p, t1, t2);
        ans = min(ans, distance_point_to_segment(p, t2, t3));
        ans = min(ans, distance_point_to_segment(p, t3, t1));
        return ans;
    }
}