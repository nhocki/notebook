pt pivot;

bool hull_comp(pt a, pt b) {
    int turn = ccw(a, b, pivot);
    return turn == 1 || (turn == 0 && cmp(norm(a-pivot), norm(b-pivot)) < 0);
}

vector<pt> hull(vector<pt> pts) {
    if(pts.size() <= 1) return pts;
    vector<pt> ret;

    int mini = 0;
    for(int i = 1; i < pts.size(); ++i)
        if(pts[i] < pts[mini])
            mini = i;

    pivot = pts[mini];
    swap(pts[0], pts[mini]);
    sort(pts.begin() + 1, pts.end(), hull_comp);

    ret.push_back(pts[0]);
    ret.push_back(pts[1]);
    int sz = 2;

    for(int i = 2; i < pts.size(); ++i) {
        while(sz >= 2 && ccw(ret[sz-2], ret[sz-1], pts[i]) <= 0)
            ret.pop_back(), --sz;
        ret.push_back(pts[i]), ++sz;
    }

    return ret;
}
