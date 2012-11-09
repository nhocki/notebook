typedef vector<int> poly;

poly mult(const poly& p, const poly& q) {
    int sz = p.size(), half = sz/2;
    assert(sz == q.size() && !(sz&(sz-1)));

    if(sz <= 64) {
        poly ret(2*sz);
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                ret[i+j] += p[i] * q[j];
        return ret;
    }

    poly p1(p.begin(), p.begin() + half), p2(p.begin() + half, p.end());
    poly q1(q.begin(), q.begin() + half), q2(q.begin() + half, q.end());
    poly p1p2(half), q1q2(half);
    for(int i = 0; i < half; i++)
        p1p2[i] = p1[i] + p2[i], q1q2[i] = q1[i] + q2[i];

    poly low = mult(p1, q1), high = mult(p2, q2), mid = mult(p1p2, q1q2);
    for(int i = 0; i < sz; i++)
        mid[i] -= high[i] + low[i];

    low.resize(2*sz);
    for(int i = 0; i < sz; i++)
        low[i+half] += mid[i], low[i+sz] += high[i];

    return low;
}
