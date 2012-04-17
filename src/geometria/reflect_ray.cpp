// Reflects the ray that goes in direction dir on the infinite
// line that passes through a and b.
Point reflect_ray(const Point &dir,const Point &a,const Point &b){
    Point n(b.y - a.y, a.x - b.x); // normal
    long double length = sqrt(n.x * n.x + n.y * n.y);
    n.x /= length, n.y /= length;
    long double dot = 2 * (dir.x * n.x + dir.y * n.y);
    Point new_dir = dir;
    new_dir.x -= dot * n.x, new_dir.y -= dot * n.y;
    return new_dir;
}
