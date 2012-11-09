int lowest[MAXV], num[MAXV], visited[MAXV], comp[MAXV];
int prev_edge[MAXE], last_edge[MAXV], adj[MAXE], nedges;
int cur_num, cur_comp;
stack<int> visiting;

void t_init() {
    memset(last_edge, -1, sizeof last_edge);
    nedges = 0;
}

void t_edge(int v, int w) {
    prev_edge[nedges] = last_edge[v];
    adj[nedges] = w;
    last_edge[v] = nedges++;
}

int tarjan_dfs(int v) {
    lowest[v] = num[v] = cur_num++;
    visiting.push(v);

    visited[v] = 1;
    for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
        int w = adj[i];
        if(visited[w] == 0) lowest[v] = min(lowest[v], tarjan_dfs(w));
        else if(visited[w] == 1) lowest[v] = min(lowest[v], num[w]);
    }

    if(lowest[v] == num[v]) {
        int last = -1;
        while(last != v) {
            comp[last = visiting.top()] = cur_comp;
            visited[last] = 2;
            visiting.pop();
        }
        ++cur_comp;
    }

    return lowest[v];
}

void tarjan_scc(int num_v = MAXV) {
    visiting = stack<int>();
    memset(visited, 0, sizeof visited);
    cur_num = cur_comp = 0;

    for(int i = 0; i < num_v; ++i)
        if(!visited[i])
            tarjan_dfs(i);
}
