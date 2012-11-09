double p_signedarea(vector<pt>& pol) {
    double ret = 0;
    for(int i = 0; i < pol.size(); ++i)
        ret += pol[i] % pol[g_mod(i+1, pol.size())];
    return ret/2;
}

int point_polygon(pt p, vector<pt>& pol) {
    int n = pol.size(), count = 0;

    for(int i = 0; i < n; ++i) {
        int i1 = g_mod(i+1, n);
        if (ps_isects(pol[i], pol[i1], p)) return -1;
        else if(((sgn(pol[i].y - p.y) == 1) != (sgn(pol[i1].y - p.y) == 1)) &&
                ccw(pol[i], p, pol[i1]) == sgn(pol[i].y - pol[i1].y)) ++count;
    }
    return count % 2;
}
