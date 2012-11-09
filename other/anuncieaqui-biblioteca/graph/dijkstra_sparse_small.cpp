int dist[MAXV], last_edge[MAXV], d_visited[MAXV];
int prev_edge[MAXE], weight[MAXE], adj[MAXE];
int nedges;
priority_queue<pair<int, int> > d_q;

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
    memset(d_visited, 0, sizeof d_visited);
    d_q.push(make_pair(dist[s] = 0, s));

    while(!d_q.empty()) {
        int v = d_q.top().second; d_q.pop();
        if(d_visited[v]) continue; d_visited[v] = true;

        for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
            int w = adj[i], new_dist = dist[v] + weight[i];
            if(new_dist < dist[w])
                d_q.push(make_pair(-(dist[w] = new_dist), w));
        }
    }
}

