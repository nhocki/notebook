bool cut[MAXV];
int mincut(int s, int t) {
    memset(flow, 0, sizeof flow);
    memset(cut, 0, sizeof cut);
    int ret = dinic(s, t);

    queue<int> q;
    q.push(s); cut[s] = true;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
            int w = adj[i];
            if(cap[i] - flow[i] && !cut[w])
                cut[w] = true, q.push(w);
        }
    }

    return ret;
}

int up[MAXV], val[MAXV];
void gomory_hu(int n) {
    memset(up, 0, sizeof up);
    for(int i = 1; i < n; i++) {
        val[i] = mincut(i, up[i]);
        for(int j = i+1; j < n; j++)
            if(cut[j] && up[j] == up[i])
                up[j] = i;
    }
}
