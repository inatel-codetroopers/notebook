// Usar com LCA

const int MAX = 1e5+5;
vector<int> adj[MAX];
int range[MAX][2];

void dfs(int u, int p) {
    range[u][0] = ++cnt;
    for(auto v : adj[u])
        if(v != p) dfs(v, u);
    range[u][1] = cnt;
}
