int last_edge[MAXV], ek_visited[MAXV], ek_prev[MAXV], ek_capres[MAXV];
int prev_edge[MAXE], cap[MAXE], flow[MAXE], adj[MAXE];
int nedges;

void ek_init() {
    nedges = 0;
    memset(last_edge, -1, sizeof last_edge);
}

void ek_edge(int v, int w, int capacity, bool r = false) {
    prev_edge[nedges] = last_edge[v];
    cap[nedges] = capacity;
    adj[nedges] = w;
    flow[nedges] = 0;
    last_edge[v] = nedges++;

    if(!r) ek_edge(w, v, 0, true);
}

queue<int> ek_q;

inline int rev(int i) { return i ^ 1; }

int ek_bfs(int src, int sink, int num_nodes) {
    memset(ek_visited, 0, sizeof(int) * num_nodes);

    ek_q = queue<int>();
    ek_q.push(src);
    ek_capres[src] = 0x3f3f3f3f;

    while(!ek_q.empty()) {
        int v = ek_q.front(); ek_q.pop();
        if(v == sink) return ek_capres[sink];
        ek_visited[v] = 2;

        for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
            int w = adj[i], new_capres = min(cap[i] - flow[i], ek_capres[v]);
            if(new_capres <= 0) continue;

            if(!ek_visited[w]) {
                ek_prev[w] = rev(i);
                ek_capres[w] = new_capres;

                ek_visited[w] = 1;
                ek_q.push(w);
            }
        }
    }
    return 0;
}

int edmonds_karp(int src, int sink, int num_nodes = MAXV) {
    int ret = 0, new_flow;

    while((new_flow = ek_bfs(src, sink, num_nodes)) > 0) {
        int cur = sink;
        while(cur != src) {
            flow[ek_prev[cur]] -= new_flow;
            flow[rev(ek_prev[cur])] += new_flow;
            cur = adj[ek_prev[cur]];
        }
        ret += new_flow;
    }
    return ret;
}

