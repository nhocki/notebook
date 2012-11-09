int dist[MAXV], last_edge[MAXV];
int prev_edge[MAXE], weight[MAXE], adj[MAXE];
int nedges;
heap d_h;

void d_init() {
    nedges = 0;
    memset(last_edge, -1, sizeof last_edge);
}

void d_edge(int v, int w, int eweight) {
    prev_edge[nedges] = last_edge[v];
    weight[nedges] = eweight;
    adj[nedges] = w;
    last_edge[v] = nedges++;
}

void dijkstra(int s, int num_nodes = MAXV) {
    memset(dist, 0x3f, sizeof dist);
    d_h.init(num_nodes);
    d_h.decrease_key(s, dist[s] = 0);

    while(d_h.size > 0) {
        int v = d_h.extract_min();

        for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
            int w = adj[i], new_dist = dist[v] + weight[i];
            if(new_dist < dist[w])
                d_h.decrease_key(w, dist[w] = new_dist);
        }
    }
}

