const int MAX = 1e5+5;
vector<int> adj[MAX];
vector<int> lvl[MAX];
int range[MAX][2];
int p[MAX][21];
int h[MAX], cnt;

void dfs(int u, int pp) {
    p[u][0] = pp;
    h[u] = h[pp] + 1;
    range[u][0] = ++cnt;
    lvl[h[u]].pb(cnt);
    REP(i, 1, 20)
        p[u][i] = p[p[u][i-1]][i-1];
    for(auto v : adj[u]) dfs(v, u);
    range[u][1] = cnt;
}

int ancestor(int u, int H) {
    PER(i, 20, 0)
        if(H & (1<<i))
            u = p[u][i];
    return u;
}
