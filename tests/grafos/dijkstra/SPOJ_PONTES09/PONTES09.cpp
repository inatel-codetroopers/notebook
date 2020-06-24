/**
 * https://br.spoj.com/problems/PONTES09/
 */

#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)

#define F first
#define S second

typedef long long ll;

const int INF = 0x3f3f3f3f;

/**
 * Encontra o menor caminho (custo) de uma origem para todos os outros
 * vertices. Apos a execucao de dijkstra(), em dist[X] ficara
 * armazenado o menor custo de um caminho partindo de src ate X. Em
 * pi[X] fica o vertice anterior a X no menor caminho de src ate X:
 * src, ... , pi[ pi[X] ], pi[X],  X
 *
 * @param[in] src Vertice de origem para o menor caminho.
 * @return void
 * @complexidade ~ O( (V+E)log(V) )
 */

#define MAXV 1000 + 10
typedef long long cost_t; // tipo de variavel para o custo da aresta

int V, E;
vector<pair<int, cost_t> > adj[MAXV];
cost_t dist[MAXV];
int pi[MAXV];

void dijkstra(int src) {
  priority_queue< pair<cost_t, int> > queue;

  memset(dist, INF, sizeof(dist));
  // don't use memset if cost_t is double

  dist[src] = 0;
  queue.push( {dist[src], src});

  while (!queue.empty()) {
    pair<cost_t, int> top = queue.top();
    queue.pop();

    int u = top.second;
    ll d = -top.first;
    
    if (d != dist[u]) continue;

    rep(i, 0, (int)adj[u].size()) {
      int v = adj[u][i].F;
      cost_t cost_uv = adj[u][i].S;

      if (dist[u] + cost_uv < dist[v]) {
        dist[v] = dist[u] + cost_uv;
        pi[v] = u;
        queue.push( {-dist[v], v} );
      }
    }
  }
}

int main() {
  /*
  Neste problema existem V + 2 vertices

  0 = origem
  1...V = pilares
  V+1 = destino
  */

  cin >> V >> E;
  rep(i, 0, E) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  // encontra o menor caminho da origem 0 para todos os outros
  dijkstra(0);

  // menor caminho até o vertice (V + 1).
  cout << dist[V + 1] << endl;

  return 0;
}
