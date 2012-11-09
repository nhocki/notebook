vector<pt> pts, tree[MAXSZ];
vector<TYPE> xs;
vector<int> lnk[MAXSZ][2];

int rt_recurse(int root, int left, int right) {
    lnk[root][0].clear(); lnk[root][1].clear(); tree[root].clear();

    if(left == right) {
        vector<pt>::iterator it;
        it = lower_bound(pts.begin(), pts.end(), pt(xs[left], -INF));
        for(; it != pts.end() && cmp(it->x, xs[left]) == 0; ++it)
            tree[root].push_back(*it);
        return tree[root].size();
    }

    int mid = (left + right)/2, cl = 2*root + 1, cr = cl + 1;
    int sz1 = rt_recurse(cl, left, mid);
    int sz2 = rt_recurse(cr, mid + 1, right);

    lnk[root][0].reserve(sz1+sz2+1);
    lnk[root][1].reserve(sz1+sz2+1);
    tree[root].reserve(sz1+sz2);

    int l = 0, r = 0, llink = 0, rlink = 0; pt last;
    while(l < sz1 || r < sz2) {
        if(r == sz2 || (l < sz1 && compy(tree[cl][l], tree[cr][r])))
            tree[root].push_back(last = tree[cl][l++]);
        else tree[root].push_back(last = tree[cr][r++]);

        while(llink < sz1 && compy(tree[cl][llink], last))
            ++llink;
        while(rlink < sz2 && compy(tree[cr][rlink], last))
            ++rlink;

        lnk[root][0].push_back(llink);
        lnk[root][1].push_back(rlink);
    }

    lnk[root][0].push_back(tree[cl].size());
    lnk[root][1].push_back(tree[cr].size());

    return tree[root].size();
}

void rt_build() {
    sort(pts.begin(), pts.end());
    xs.clear();
    for(int i = 0; i < pts.size(); ++i) xs.push_back(pts[i].x);
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    rt_recurse(0, 0, xs.size() - 1);
}

int rt_query(int root, int l, int r, TYPE a, TYPE b, TYPE c, TYPE d,
             int posl = -1, int posr = -1) {
    if(root == 0 && posl == -1) {
        posl = lower_bound(tree[0].begin(), tree[0].end(), pt(a, c), compy)
            - tree[0].begin();
        posr = upper_bound(tree[0].begin(), tree[0].end(), pt(b, d), compy)
            - tree[0].begin();
    }

    if(posl == posr) return 0;
    if(a <= xs[l] && xs[r] <= b)
        return posr - posl;

    int mid = (l+r)/2, ret = 0;
    if(cmp(a, xs[mid]) <= 0)
        ret += rt_query(2*root+1, l, mid, a, b, c, d,
                        lnk[root][0][posl], lnk[root][0][posr]);
    if(cmp(xs[mid+1], b) <= 0)
        ret += rt_query(2*root+2, mid+1, r, a, b, c, d,
                        lnk[root][1][posl], lnk[root][1][posr]);
    return ret;
}
