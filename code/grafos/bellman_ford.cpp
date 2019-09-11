// Menor custo de uma origem s para todos vertices em O(V^3).
// bellman() retorna FALSE se o grafo tem ciclo com custo negativo.
// dist[v] contem o menor custo de s ate v.
#define MAXV 400

// Vertices indexados em 0.
int V, E; // #vertices, #arestas
vector<ii> adj[MAXV];
ll dist[MAXV];

bool bellman(int s) {
  rep(i, 0, V) dist[i] = INF;
  dist[s] = 0;
  rep(i, 0, V - 1) rep(u, 0, V) {
    rep(j, 0, adj[u].size()) {
      int v = adj[u][j].F, duv = adj[u][j].S;
      dist[v] = min(dist[v], dist[u] + duv);
    }
  }
  // verifica se tem ciclo com custo negativo
  rep(u, 0, V) rep(j, 0, adj[u].size()) {
    int v = adj[u][j].F, duv = adj[u][j].S;
    if (dist[v] > dist[u] + duv)
      return false;
  }
  return true;
}

int main() { return 0; }
