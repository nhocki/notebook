int prev_edge[MAXE], v[MAXE], w[MAXE], last_edge[MAXV];
int type[MAXV], label[MAXV], first[MAXV], mate[MAXV], nedges;
bool g_flag[MAXV], g_souter[MAXV];

void g_init() {
    nedges = 0;
    memset(last_edge, -1, sizeof last_edge);
}

void g_edge(int a, int b, bool rev = false) {
    prev_edge[nedges] = last_edge[a];
    v[nedges] = a;
    w[nedges] = b;
    last_edge[a] = nedges++;

    if(!rev) return g_edge(b, a, true);
}

void g_label(int v, int join, int edge, queue<int>& outer) {
    if(v == join) return;
    if(label[v] == -1) outer.push(v);

    label[v] = edge;
    type[v] = 1;
    first[v] = join;

    g_label(first[label[mate[v]]], join, edge, outer);
}

void g_augment(int _v, int _w) {
    int t = mate[_v];
    mate[_v] = _w;

    if(mate[t] != _v) return;
    if(label[_v] == -1) return;

    if(type[_v] == 0) {
        mate[t] = label[_v];
        g_augment(label[_v], t);
    } else if(type[_v] == 1) {
        g_augment(v[label[_v]], w[label[_v]]);
        g_augment(w[label[_v]], v[label[_v]]);
    }
}

int gabow(int n) {
    memset(mate, -1, sizeof mate);
    memset(first, -1, sizeof first);

    int ret = 0;
    for(int z = 0; z < n; ++z) {
        if(mate[z] != -1) continue;

        memset(label, -1, sizeof label);
        memset(type, -1, sizeof type);
        memset(g_souter, 0, sizeof g_souter);

        label[z] = -1; type[z] = 0;

        queue<int> outer;
        outer.push(z);

        bool done = false;
        while(!outer.empty()) {
            int x = outer.front(); outer.pop();

            if(g_souter[x]) continue;
            g_souter[x] = true;

            for(int i = last_edge[x]; i != -1; i = prev_edge[i]) {
                if(mate[w[i]] == -1 && w[i] != z) {
                    mate[w[i]] = x;
                    g_augment(x, w[i]);
                    ++ret;

                    done = true;
                    break;
                }

                if(type[w[i]] == -1) {
                    int v = mate[w[i]];
                    if(type[v] == -1) {
                        type[v] = 0;
                        label[v] = x;
                        outer.push(v);

                        first[v] = w[i];
                    }
                    continue;
                }

                int r = first[x], s = first[w[i]];
                if(r == s) continue;

                memset(g_flag, 0, sizeof g_flag);
                g_flag[r] = g_flag[s] = true;

                while(r != -1 || s != -1) {
                    if(s != -1) swap(r, s);
                    r = first[label[mate[r]]];
                    if(r == -1) continue;
                    if(g_flag[r]) break; g_flag[r] = true;
                }

                g_label(first[x], r, i, outer);
                g_label(first[w[i]], r, i, outer);

                for(int c = 0; c < n; ++c)
                    if(type[c] != -1 && first[c] != -1 && type[first[c]] != -1)
                        first[c] = r;
            }
            if(done) break;
        }
    }
    return ret;
}
