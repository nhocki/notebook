int w[MAXV][MAXV], s[MAXV], rem[MAXV], remx[MAXV];
int mx[MAXV], my[MAXV], lx[MAXV], ly[MAXV];

void add(int x, int n) {
    s[x] = true;
    for(int y = 0; y < n; y++)
        if(rem[y] != -INF && rem[y] > lx[x] + ly[y] - w[x][y])
            rem[y] = lx[x] + ly[y] - w[x][y], remx[y] = x;
}

int kuhn_munkres(int n) {
    for(int i = 0; i < n; i++) mx[i] = my[i] = -1, lx[i] = ly[i] = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            ly[j] = max(ly[j], w[i][j]);

    for(int i = 0; i < n; i++) {
        memset(s, 0, sizeof s); memset(rem, 0x3f, sizeof rem);

        int st;
        for(st = 0; st < n; st++) if(mx[st] == -1) { add(st, n); break; }
        while(mx[st] == -1) {
            int miny = -1;
            for(int y = 0; y < n; y++)
                if(rem[y] != -INF && (miny == -1 || rem[miny] >= rem[y]))
                    miny = y;

            if(rem[miny]) {
                for(int x = 0; x < n; x++) if(s[x]) lx[x] -= rem[miny];
                for(int y = 0, d = rem[miny]; y < n; y++)
                    if(rem[y] == -INF) ly[y] += d; else rem[y] -= d;
            }

            if(my[miny] == -1) {
                int cur = miny;
                while(remx[cur] != st) {
                    int pmate = mx[remx[cur]];
                    my[cur] = remx[cur], mx[my[cur]] = cur;
                    my[pmate] = -1; cur = pmate;
                }
                my[cur] = remx[cur], mx[my[cur]] = cur;
            } else
                add(my[miny], n), rem[miny] = -INF;
        }
    }

    int ret = 0;
    for(int i = 0; i < n; i++)
        ret += w[i][mx[i]];
    return ret;
}
