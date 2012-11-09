int term[N]; map<char, int> next[N]; int T[N]; int cnt = 1;
void add(string s, int it){
  int node = 0;
  f(i, 0, s.size()){
    char c = s[i];
    if(!next[node].count(c)) term[cnt] = 0, next[node][c] = cnt, cnt++;
    node = next[node][c];
  }
  term[node] = 1 << it;
}
void aho(){
  queue<int> q;
  for(char c = 'a'; c <= 'z'; c++)
    if(next[0].count(c)) q.push(next[0][c]), T[next[0][c]] = 0;
    else next[0][c] = 0;

  while(!q.empty()){
    int u = q.front(); q.pop();
    for(char c = 'a'; c <= 'z'; c++) if(next[u].count(c)){
      int v = next[u][c];
      int x = T[u];
      while(!next[x].count(c)) x = T[x];
      x = next[x][c];
      T[v] = x;
      q.push(v);
      term[v] |= term[x];
    }
  }
}

