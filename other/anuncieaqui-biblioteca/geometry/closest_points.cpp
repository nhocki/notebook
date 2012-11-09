pair<pt, pt> closest_points_rec(vector<pt>& px, vector<pt>& py) {
    pair<pt, pt> ret;
    double d;

    if(px.size() <= 3) {
        double best = 1e10;
        for(int i = 0; i < px.size(); ++i)
            for(int j = i + 1; j < px.size(); ++j)
                if(dist(px[i], px[j]) < best) {
                    ret = make_pair(px[i], px[j]);
                    best = dist(px[i], px[j]);
                }

        return ret;
    }

    pt split = px[(px.size() - 1)/2];
    vector<pt> qx, qy, rx, ry;
    for(int i = 0; i < px.size(); ++i)
        if(px[i] <= split) qx.push_back(px[i]);
        else rx.push_back(px[i]);

    for(int i = 0; i < py.size(); ++i)
        if(py[i] <= split) qy.push_back(py[i]);
        else ry.push_back(py[i]);

    ret = closest_points_rec(qx, qy);
    pair<pt, pt> rans = closest_points_rec(rx, ry);
    double delta = dist(ret.first, ret.second);

    if((d = dist(rans.first, rans.second)) < delta) {
        delta = d;
        ret = rans;
    }

    vector<pt> s;
    for(int i = 0; i < py.size(); ++i)
        if(cmp(abs(py[i].x - split.x), delta) <= 0)
            s.push_back(py[i]);

    for(int i = 0; i < s.size(); ++i)
        for(int j = 1; j <= 7 && i + j < s.size(); ++j)
            if((d = dist(s[i], s[i+j])) < delta) {
                delta = d;
                ret = make_pair(s[i], s[i+j]);
            }

    return ret;
}

pair<pt, pt> closest_points(vector<pt> pts) {
    if(pts.size() == 1) return make_pair(pt(-INF, -INF), pt(INF, INF));

    sort(pts.begin(), pts.end());
    for(int i = 0; i + 1 < pts.size(); ++i)
        if(pts[i] == pts[i+1])
            return make_pair(pts[i], pts[i+1]);

    vector<pt> py = pts;
    sort(py.begin(), py.end(), compy);
    return closest_points_rec(pts, py);
}
