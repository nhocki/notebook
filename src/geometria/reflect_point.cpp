// Reflects point p to the other side of the infinite line that
// passes through a and b. It's assumed that a != b.
Point reflect(Point p, const Point &a, const Point &b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double u = (dx * (p.x - a.x) + (p.y - a.y) * dy) / 
                        (dx * dx + dy * dy);
    Point v; // Intersection
    v.x = a.x + u * dx;
    v.y = a.y + u * dy;
    
    p.x += 2*(v.x - p.x);
    p.y += 2*(v.y - p.y);
    return p;
}
