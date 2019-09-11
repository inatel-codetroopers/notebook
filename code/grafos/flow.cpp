// Ford-Fulkerson para fluxo maximo
#define MAXV 250
vector<int> edge[MAXV];
int cap[MAXV][MAXV];
bool vis[MAXV];

void init() {
  rep(i, 0, MAXV) edge[i].clear();
  memset(cap, 0, sizeof cap);
}

void add(int a, int b, int cap_ab, int cap_ba) {
  edge[a].pb(b), edge[b].pb(a);
  cap[a][b] += cap_ab, cap[b][a] += cap_ba;
}

int dfs(int src, int snk, int fl) {
  if (vis[src])
    return 0;
  if (snk == src)
    return fl;
  vis[src] = 1;
  rep(i, 0, edge[src].size()) {
    int v = edge[src][i];
    int x = min(fl, cap[src][v]);
    if (x > 0) {
      x = dfs(v, snk, x);
      if (!x)
        continue;
      cap[src][v] -= x;
      cap[v][src] += x;
      return x;
    }
  }
  return 0;
}

int flow(int src, int snk) {
  int ret = 0;
  while (42) {
    memset(vis, 0, sizeof vis);
    int delta = dfs(src, snk, 1 << 30);
    if (!delta)
      break;
    ret += delta;
  }
  return ret;
}
int main() { return 0; }