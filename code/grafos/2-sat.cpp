#define MAXV 100001
// 2-sat - Codigo do problema X-Mart
// vertices indexado em 1
vector<int> adj[2 * MAXV];
vector<int> radj[2 * MAXV];
int seen[2 * MAXV], comp[2 * MAXV], order[2 * MAXV], ncomp, norder;
int N;  // #variaveis
int n;  // #vertices

#define NOT(x) ((x <= N) ? (x + N) : (x - N))
#define quero 1
void add_edge(int a, int b, int opcao) {
  if (a > b) swap(a, b);
  if (b == 0) return;
  if (a == 0) {
    if (opcao == quero)
      adj[NOT(b)].pb(b);
    else
      adj[b].pb(NOT(b));
  } else {  // normal...
    if (opcao == quero) {
      adj[NOT(a)].pb(b);
      adj[NOT(b)].pb(a);
    } else {
      a = NOT(a);
      b = NOT(b);
      adj[NOT(a)].pb(b);
      adj[NOT(b)].pb(a);
    }
  }
}
void init() {
  rep(i, 0, n + 1) {
    adj[i].clear();
    radj[i].clear();
  }
}
void dfs1(int u) {
  seen[u] = 1;
  rep(i, 0, adj[u].size()) if (!seen[adj[u][i]]) dfs1(adj[u][i]);
  order[norder++] = u;
}
void dfs2(int u) {
  seen[u] = 1;
  rep(i, 0, radj[u].size()) if (!seen[radj[u][i]]) dfs2(radj[u][i]);
  comp[u] = ncomp;
}
void strongly_connected_components() {
  rep(v, 1, n + 1) rep(i, 0, (int)adj[v].size()) radj[adj[v][i]].pb(
      v);

  norder = 0;
  memset(seen, 0, sizeof seen);
  rep(v, 1, n + 1) if (!seen[v]) dfs1(v);

  ncomp = 0;
  memset(seen, 0, sizeof seen);
  for (int i = n - 1, u = order[n - 1]; i >= 0; u = order[--i])
    if (!seen[u]) {
      dfs2(u);
      ncomp++;
    }
}
bool sat2() {
  strongly_connected_components();
  rep(i, 1, n + 1) if (comp[i] == comp[NOT(i)]) return false;
  return true;
}
int main() {
  int Clientes;
  while (cin >> Clientes >> N) {
    if (Clientes == 0 && N == 0) break;
    n = 2 * N;
    init();
    int u, v;
    rep(i, 0, Clientes) {
      scanf("%d %d", &u, &v);
      add_edge(u, v, quero);
      scanf("%d %d", &u, &v);
      add_edge(u, v, !quero);
    }
    sat2() ? printf("yes\n") : printf("no\n");
  }
  return 0;
}