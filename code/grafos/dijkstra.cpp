#define MAXV 100000
int dist[MAXV], pi[MAXV];  // dist from s and pointer to parent
vector<ii> adj[MAXV];      // edge = {v, dist}
int dijkstra(int s, int t, int n) {
  priority_queue<ii> pq;
  memset(pi, -1, sizeof pi);
  memset(dist, INF, sizeof dist);
  pq.push(ii(dist[s] = 0, s));
  while (!pq.empty()) {
    ii top = pq.top();
    pq.pop();
    int u = top.second, d = -top.first;
    if (d != dist[u]) continue;
    if (u == t) break;  // terminou antes
    rep(i, 0, (int)adj[u].size()) {
      int v = adj[u][i].F;
      int cost = adj[u][i].S;
      if (dist[v] > dist[u] + cost) {
        dist[v] = dist[u] + cost;
        pi[v] = u;
        pq.push(ii(-dist[v], v));
      }
    }
  }
  return dist[t];
}

int main() { return 0; }
