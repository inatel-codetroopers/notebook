#define MAXV 100010
vector<int> adj[MAXV];
int V;
int dfs_num[MAXV], dfs_low[MAXV], vis[MAXV], SCC[MAXV];
int dfsCounter, numSCC;
vector<int> S; // global variables

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = dfsCounter++; // dfs_low[u] <= dfs_num[u]
  S.push_back(u); // stores u in a vector based on order of
                  // visitation
  vis[u] = 1;
  rep(i, 0, adj[u].size()) {
    int v = adj[u][i];
    if (dfs_num[v] == -1)
      tarjanSCC(v);
    if (vis[v]) // condition for update
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
  if (dfs_low[u] == dfs_num[u]) { // if this is a root (start) of an SCC
    while (true) {
      int v = S.back();
      S.pop_back();
      vis[v] = 0;
      SCC[v] = numSCC; // wich SCC this vertex belong
      if (u == v)
        break;
    }
    numSCC++;
  }
}

int main() {
  // read graph
  rep(i, 0, V) {
    dfs_num[i] = -1;
    dfs_low[i] = vis[i] = 0;
    SCC[i] = -i;
  }
  dfsCounter = numSCC = 0;
  rep(i, 0, V) if (dfs_num[i] == -1) tarjanSCC(i);
  rep(i, 0, V) printf("vertice %d, componente %d\n", i, SCC[i]);
  return 0;
}