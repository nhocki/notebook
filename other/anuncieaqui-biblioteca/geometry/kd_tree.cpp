int tree[4*MAXSZ], val[4*MAXSZ];
TYPE split[4*MAXSZ];
vector<pt> pts;

void kd_recurse(int root, int left, int right, bool x) {
    if(left == right) {
        tree[root] = left;
        val[root] = 1;
        return;
    }

    int mid = (right+left)/2;
    nth_element(pts.begin() + left, pts.begin() + mid,
                pts.begin() + right + 1, x ? compx : compy);
    split[root] = x ? pts[mid].x : pts[mid].y;

    kd_recurse(2*root+1, left, mid, !x);
    kd_recurse(2*root+2, mid+1, right, !x);

    val[root] = val[2*root+1] + val[2*root+2];
}

void kd_build() {
    memset(tree, -1, sizeof tree);
    kd_recurse(0, 0, pts.size() - 1, true);
}

int kd_query(int root, TYPE a, TYPE b, TYPE c, TYPE d, TYPE ca = -INF,
             TYPE cb = INF, TYPE cc = -INF, TYPE cd = INF, bool x = true) {
    if(a <= ca && cb <= b && c <= cc && cd <= d)
        return val[root];

    if(tree[root] != -1)
        return a <= pts[tree[root]].x && pts[tree[root]].x <= b &&
            c <= pts[tree[root]].y && pts[tree[root]].y <= d ? val[root] : 0;

    int ret = 0;
    if(x) {
        if(a <= split[root])
            ret += kd_query(2*root+1, a, b, c, d, ca, split[root], cc, cd, !x);
        if(split[root] <= b)
            ret += kd_query(2*root+2, a, b, c, d, split[root], cb, cc, cd, !x);
    } else {
        if(c <= split[root])
            ret += kd_query(2*root+1, a, b, c, d, ca, cb, cc, split[root], !x);
        if(split[root] <= d)
            ret += kd_query(2*root+2, a, b, c, d, ca, cb, split[root], cd, !x);
    }
    return ret;
}

pt kd_neighbor(int root, pt a, bool x) {
    if(tree[root] != -1)
        return a == pts[tree[root]] ? pt(INF, INF) : pts[tree[root]];

    TYPE num = x ? a.x : a.y;
    int term = num <= split[root] ? 1 : 2;
    pt ret;

    TYPE d = norm(a - (ret = kd_neighbor(2*root + term, a, !x)));
    if((split[root] - num)*(split[root] - num) < d) {
        pt ret2 = kd_neighbor(2*root + 3 - term, a, !x);
        if(norm(a - ret2) < d)
            ret = ret2;
    }

    return ret;
}
