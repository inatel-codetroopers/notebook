// Verifica se dado duas arvores, desconsiderando o rotulo dos
// vertices, elas tem a mesma forma.
typedef vector<int> vi;
#define sz(a) (int)a.size()
#define fst first
#define snd second

struct tree {
  int n;
  vector<vi> adj;
  tree(int n) : n(n), adj(n) {}
  void add_edge(int src, int dst) {
    adj[src].pb(dst);
    adj[dst].pb(src);
  }
  vi centers() {
    vi prev;
    int u = 0;
    for (int k = 0; k < 2; ++k) {
      queue<int> q;
      prev.assign(n, -1);
      q.push(prev[u] = u);
      while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto i : adj[u]) {
          if (prev[i] >= 0)
            continue;
          q.push(i);
          prev[i] = u;
        }
      }
    }
    vi path = {u};
    while (u != prev[u])
      path.pb(u = prev[u]);
    int m = sz(path);
    if (m % 2 == 0)
      return {path[m / 2 - 1], path[m / 2]};
    else
      return {path[m / 2]};
  }
  vector<vi> layer;
  vi prev;
  int levelize(int r) {
    prev.assign(n, -1);
    prev[r] = n;
    layer = {{r}};
    while (true) {
      vi next;
      for (auto u : layer.back()) {
        for (int v : adj[u]) {
          if (prev[v] >= 0)
            continue;
          prev[v] = u;
          next.pb(v);
        }
      }
      if (next.empty())
        break;
      layer.pb(next);
    }
    return sz(layer);
  }
};

bool isomorphic(tree S, int s, tree T, int t) {
  if (S.n != T.n)
    return false;
  if (S.levelize(s) != T.levelize(t))
    return false;
  vector<vi> longcodeS(S.n + 1), longcodeT(T.n + 1);
  vi codeS(S.n), codeT(T.n);
  for (int h = S.layer.size() - 1; h >= 0; h--) {
    map<vi, int> bucket;
    for (int u : S.layer[h]) {
      sort(all(longcodeS[u]));
      bucket[longcodeS[u]] = 0;
    }
    for (int u : T.layer[h]) {
      sort(all(longcodeT[u]));
      bucket[longcodeT[u]] = 0;
    }
    int id = 0;
    for (auto &p : bucket)
      p.snd = id++;
    for (int u : S.layer[h]) {
      codeS[u] = bucket[longcodeS[u]];
      longcodeS[S.prev[u]].pb(codeS[u]);
    }
    for (int u : T.layer[h]) {
      codeT[u] = bucket[longcodeT[u]];
      longcodeT[T.prev[u]].pb(codeT[u]);
    }
  }
  return codeS[s] == codeT[t];
}

bool isomorphic(tree S, tree T) {
  auto x = S.centers(), y = T.centers();
  if (sz(x) != sz(y))
    return false;
  if (isomorphic(S, x[0], T, y[0]))
    return true;
  return sz(x) > 1 and isomorphic(S, x[1], T, y[0]);
}

int main() {
  int N, u, v;
  cin >> N;
  tree A(N + 2), B(N + 2);
  rep(i, 0, N - 1) {
    scanf("%d %d", &u, &v);
    u--, v--;
    A.add_edge(u, v);
  }
  rep(i, 1, N) {
    scanf("%d %d", &u, &v);
    u--, v--;
    B.add_edge(u, v);
  }
  puts(isomorphic(A, B) ? "S" : "N");
}