// Returns the number of moves a knight must make
//to go from (x1, y1) to (x2, y2) in an INFINITE
// chess board.
long long knight_distance(long long x1, long long y1,
                          long long x2, long long y2) {
    long long x = abs(x2 - x1), y = abs(y2 - y1);    
    if (x > y) swap(x, y);
    assert(x <= y);
    if (x == 0 and y == 1) return 3;
    if (x == 2 and y == 2) return 4;
    long long d = max((y + 1) / 2, (x + y + 2) / 3);
    if (d % 2 != (x + y) % 2) d++;
    return d;
}