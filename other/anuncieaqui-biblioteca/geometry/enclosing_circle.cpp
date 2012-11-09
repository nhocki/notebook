circle enclosing_circle(vector<pt>& pts) {
    srand(unsigned(time(0)));
    random_shuffle(pts.begin(), pts.end());

    circle c(pt(), -1);
    for(int i = 0; i < pts.size(); ++i) {
        if(point_circle(pts[i], c)) continue;
        c = circle(pts[i], 0);
        for(int j = 0; j < i; ++j) {
            if(point_circle(pts[j], c)) continue;
            c = circle((pts[i] + pts[j])/2, abs(pts[i] - pts[j])/2);
            for(int k = 0; k < j; ++k) {
                if(point_circle(pts[k], c)) continue;
                pt center = circumcenter(pts[i], pts[j], pts[k]);
                c = circle(center, abs(center - pts[i])/2);
            }
        }
    }
    return c;
}
