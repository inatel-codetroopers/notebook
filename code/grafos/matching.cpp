// Encontra o casamento bipartido maximo. Set de vertices X e Y.
// x = [0,X-1], y = [0,Y-1]. match[y] = x - contem quem esta casado
// com y. Teorema de Konig - Num grafo bipartido, o matching eh igual
// ao minimum vertex cover. Complexidade O(nm)
#define MAXV 1000
vector<int> adj[MAXV];
int match[MAXV], V, X, Y;
bool vis[MAXV];

int aug(int v) {
  if (vis[v])
    return 0;
  vis[v] = true;
  rep(i, 0, adj[v].size()) {
    int r = adj[v][i];
    if (match[r] == -1 || aug(match[r])) {
      match[r] = v; // augmenting path
      return 1;
    }
  }
  return 0;
}
int matching(int X, int Y) {
  int V = X + Y;
  rep(i, 0, V) match[i] = -1;
  int mcbm = 0;
  rep(i, 0, X) {
    rep(j, 0, X) vis[j] = false;
    mcbm += aug(i);
  }
  return mcbm;
}
