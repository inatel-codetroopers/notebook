// Dinic para fluxo maximo
// Grafo indexado em 1
// Inicializar maxN, maxE.
// Chamar init() com #nos, source e sink. Montar o grafo chamando
// add(a,b,c1,c2), sendo c1 cap. de a->b e c2 cap. de b->a
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define SET(c, v) memset(c, v, sizeof c)
const int maxN = 5000;
const int maxE = 70000;
const int inf = 1000000005;

int nnode, nedge, src, snk;
int Q[maxN], pro[maxN], fin[maxN], dist[maxN];
int flow[maxE], cap[maxE], to[maxE], prox[maxE];

void init(int _nnode, int _src, int _snk) {
  nnode = _nnode, nedge = 0, src = _src, snk = _snk;
  FOR(i, 1, nnode) fin[i] = -1;
}

void add(int a, int b, int c1, int c2) {
  to[nedge] = b, cap[nedge] = c1, flow[nedge] = 0,
  prox[nedge] = fin[a], fin[a] = nedge++;
  to[nedge] = a, cap[nedge] = c2, flow[nedge] = 0,
  prox[nedge] = fin[b], fin[b] = nedge++;
}

bool bfs() {
  SET(dist, -1);
  dist[src] = 0;
  int st = 0, en = 0;
  Q[en++] = src;
  while (st < en) {
    int u = Q[st++];
    for (int e = fin[u]; e >= 0; e = prox[e]) {
      int v = to[e];
      if (flow[e] < cap[e] && dist[v] == -1) {
        dist[v] = dist[u] + 1;
        Q[en++] = v;
      }
    }
  }
  return dist[snk] != -1;
}

int dfs(int u, int fl) {
  if (u == snk) return fl;
  for (int& e = pro[u]; e >= 0; e = prox[e]) {
    int v = to[e];
    if (flow[e] < cap[e] && dist[v] == dist[u] + 1) {
      int x = dfs(v, min(cap[e] - flow[e], fl));
      if (x > 0) {
        flow[e] += x, flow[e ^ 1] -= x;
        return x;
      }
    }
  }
  return 0;
}

ll dinic() {
  ll ret = 0;
  while (bfs()) {
    FOR(i, 1, nnode) pro[i] = fin[i];
    while (true) {
      int delta = dfs(src, inf);
      if (!delta) break;
      ret += delta;
    }
  }
  return ret;
}

int main() { return 0; }