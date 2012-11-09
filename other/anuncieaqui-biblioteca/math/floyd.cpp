pair<int, int> floyd(int x0) {
    int t = f(x0), h = f(f(x0)), start = 0, length = 1;
    while(t != h)
        t = f(t), h = f(f(h));

    h = t; t = x0;
    while(t != h)
        t = f(t), h = f(h), ++start;

    h = f(t);
    while(t != h)
        h = f(h), ++length;

    return make_pair(start, length);
}
