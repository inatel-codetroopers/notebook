/*
 * Encontra o custo do menor caminho uma origem para todos os outros
 * vertices do grafo.
 * So pode ser aplicado em grafos que nao possuem ciclos com peso
 * negativo.
 * Em dist[X] ficara armazenado o custo do menor caminho de src ate X;
 * e em pi[X] ficara o vertice anterior a X neste caminho.
 * Exemplo: src ->, ... , pi[ pi[X] ] -> pi[X] -> X
 * Complexidade O( (V+E)log(V) )
*/

#define MAXV 100000+10    // quantidade maxima de vertices
typedef long long cost_t; // tipo de variavel para o custo da aresta

int V, E;
vector<pair<int, cost_t> > adj[MAXV];
cost_t dist[MAXV];
int pi[MAXV];

void dijkstra(int src) {
  priority_queue< pair<cost_t, int> > PQ;

  memset(dist, INF, sizeof(dist));
  // nao utilize memset se cost_f for double, use um for

  dist[src] = 0;
  PQ.push( make_pair(dist[src], src));

  while (!PQ.empty()) {
    pair<cost_t, int> top = PQ.top();
    PQ.pop();

    int u = top.second;
    cost_t d = -top.first;
    
    if (d != dist[u]) continue;

    rep(i, 0, (int)adj[u].size()) {
      int v = adj[u][i].F;
      cost_t cost_uv = adj[u][i].S;

      if (dist[u] + cost_uv < dist[v]) {
        dist[v] = dist[u] + cost_uv;
        pi[v] = u;
        PQ.push( make_pair(-dist[v], v) );
      }
    }
  }
}