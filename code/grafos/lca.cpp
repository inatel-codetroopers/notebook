/*Lowest Common Ancestor (LCA) entre dois vertices A, B de uma arvore.
LCA(A,B) = ancestral mais proximo de A adj B. O codigo abaixo tambem
calcula a menor aresta do caminho entre A adj B. Para saber quantas
arestas tem entre A adj B basta fazer:
level[A]+level[B]-2*level[lca(A,B)]
Pode-se modificar para retorna a
distancia entre A adj B. Como usar: (1) ler a arvore em adj[] adj W[],
chamar doit(raiz), passando a raiz da arvore. Indexar em 0 os vertices
(2) A funcao retorna o LCA adj a menor aresta entre A adj B.
*/

#define MAXV 101000
const int maxl = 20;      // profundidade maxima 2^(maxl) > MAXV
int pai[MAXV][maxl + 1];  // pai[v][i] = pai de v subindo 2^i arestas
int dist[MAXV][maxl + 1]; // dist[v][i] = menor aresta de v subindo
                          // 2^i arestas
int level[MAXV];          // level[v] = #arestas de v ate a raiz

int N, M;                         // numero de vertices adj arestas
vector<pair<int, int>> adj[MAXV]; // {v,custo}

void dfs(int v, int p, int peso) {
  level[v] = level[p] + 1;
  pai[v][0] = p;
  dist[v][0] = peso; // aresta de v--pai[v]
  for (int i = 1; i <= maxl; i++) {
    pai[v][i] = pai[pai[v][i - 1]][i - 1]; // subindo 2^i arestas
    dist[v][i] = min(dist[v][i - 1], dist[pai[v][i - 1]][i - 1]);
  }
  rep(i, 0, adj[v].size()) {
    int viz = adj[v][i].F;
    int cost = adj[v][i].S;
    if (viz == p)
      continue;
    dfs(viz, v, cost);
  }
}

void doit(int root) {
  level[root] = 0;
  for (int i = 0; i <= maxl; i++)
    pai[root][i] = root, dist[root][i] = INF;
  rep(i, 0, adj[root].size()) {
    int viz = adj[root][i].F;
    int cost = adj[root][i].S;
    dfs(viz, root, cost);
  }
}

pair<int, int> lca(int a, int b) {
  int menor = INF; // valor da menor aresta do caminho a->b
  if (level[a] < level[b])
    swap(a, b);

  for (int i = maxl; i >= 0; i--) {
    if (level[pai[a][i]] >= level[b]) {
      menor = min(menor, dist[a][i]);
      a = pai[a][i];
    }
  }
  if (a != b) {
    for (int i = maxl; i >= 0; i--) {
      if (pai[a][i] != pai[b][i]) {
        menor = min(menor, min(dist[a][i], dist[b][i]));
        a = pai[a][i];
        b = pai[b][i];
      }
    }
    // ultimo salto
    menor = min(menor, min(dist[a][0], dist[b][0]));
    a = pai[a][0];
    b = pai[b][0];
  }
  return make_pair(a, menor);
}

int main() { return 0; }
