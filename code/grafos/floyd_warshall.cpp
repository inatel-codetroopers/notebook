#define MAXV 401
int adj[MAXV][MAXV], path[MAXV][MAXV];
int n, m; // #vertices, #arestas
// adj[u][v] = custo de {U->V}
// path[u][v] = k .: K vem logo apos U no caminho ate V
void read_graph() {
  memset(adj, INF, sizeof adj); // para menor caminho
  rep(i, 0, n) adj[i][i] = 0;   // para menor caminho
  int u, v, w;
  rep(i, 0, m) {
    cin >> u >> v >> w;
    adj[u][v] = w;
    path[u][v] = v;
  }
}
void floyd() {
  rep(k, 0, n) rep(i, 0, n)
      rep(j, 0, n) if (adj[i][k] + adj[k][j] < adj[i][j]) {
    adj[i][j] = adj[i][k] + adj[k][j];
    path[i][j] = path[i][k];
  }
}
vector<int> findPath(int s, int d) {
  vector<int> Path;
  Path.pb(s);
  while (s != d) {
    s = path[s][d];
    Path.pb(s);
  }
  return Path;
}

/*Aplicacoes:
1-Encontrar o fecho transitivo (saber se U consegue visitar V)
.: adj[u][v] |= (adj[u][k] & adj[k][v]);
   (inicializar adj com 0)

2-Minimizar a maior aresta do caminho entre U e V
.: adj[u][v] = min(adj[u][v], max(adj[u][k], adj[k][v]));
   (inicializar adj com INF)

3-Maximizar a menor aresta do caminho entre U e V
.: adj[u][v] = max(adj[u][v], min(adj[u][k], adj[k][u]));
   (inicializar adj com -INF)*/

int main() { return 0; }
