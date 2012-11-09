int last_edge[MAXV], prev_edge[MAXE], adj[MAXE], nedges;
int up[MAXV], subtree[MAXV], path[MAXV], offset[MAXV], depth[MAXV];
int nump, numv, psize[MAXV], pfirst[MAXV], walk[MAXV];

struct stree {
    vector<int> data;
    int sz;

    explicit stree(int tsz) : sz(1) {
        while(sz < tsz) sz *= 2;
        data.resize(2*sz);
    }

    int query(int a, int b, int root, int l, int r) {
        if(l == a && r == b) return data[root];
        int mid = (l+r)/2, ans = 0;
        if(a <= mid) ans = max(ans, query(a, min(b, mid), 2*root+1, l, mid));
        if(b > mid) ans = max(ans, query(max(a, mid+1), b, 2*root+2, mid+1, r));
        return ans;
    }
    int query(int a, int b) { return a<=b ? query(a, b, 0, 0, sz-1) : 0; }

    void update(int pos, int val, int root, int l, int r) {
        if(l == r) { data[root] = val; return; }
        int mid = (l+r)/2;
        if(pos <= mid) update(pos, val, 2*root+1, l, mid);
        else update(pos, val, 2*root+2, mid+1, r);
        data[root] = max(data[2*root+1], data[2*root+2]);
    }
    void update(int pos, int val) { update(pos, val, 0, 0, sz-1); }
};

void hl_init(int n) {
    memset(last_edge, -1, sizeof(int) * n);
    nedges = 0;
}

void hl_edge(int a, int b, bool rev = false) {
    prev_edge[nedges] = last_edge[a];
    adj[nedges] = b;
    last_edge[a] = nedges++;

    if(!rev) hl_edge(b, a, true);
}

vector<stree> segtree;
void heavy_light() {
    memset(up, -1, sizeof up);
    stack<int> s; if(last_edge[0] != -1) s.push(last_edge[0]);

    walk[0] = depth[0] = up[0] = 0; numv = subtree[0] = 1;
    while(!s.empty()) {
        int i = s.top(), v = adj[i^1], w = adj[i];
        if(up[w] == -1) {
            up[w] = v; depth[w] = depth[v]+1; subtree[w] = 1;
            walk[numv++] = w; s.push(last_edge[w]);
        } else {
            s.pop(); if(up[w] == v) subtree[v] += subtree[w];
            if(prev_edge[i] != -1) s.push(prev_edge[i]);
        }
    }

    pfirst[0] = path[0] = offset[0] = 0; nump = psize[0] = 1;
    for(int i = 1; i < numv; i++) {
        int v = walk[i], p = up[v];
        if(2*subtree[v] < subtree[p] || p == 0)
            offset[v] = 0, path[v] = nump, pfirst[nump] = v, psize[nump++] = 1;
        else
            offset[v] = offset[p]+1, path[v] = path[p], psize[path[v]]++;
    }

    segtree.clear(); segtree.reserve(nump);
    for(int i = 0; i < nump; i++) segtree.push_back(stree(psize[i]));
}

int lca(int v, int w) {
    int fpv = pfirst[path[v]], fpw = pfirst[path[w]];
    while(v != 0 && w != 0 && fpv != fpw) {
        if(depth[up[fpv]] > depth[up[fpw]]) swap(v, w), swap(fpv, fpw);
        w = up[fpw]; fpw = pfirst[path[w]];
    }
    return depth[v] < depth[w] ? v : w;
}
