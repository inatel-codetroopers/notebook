// Encotra componentes conexos. Mesmo que Tarjan
#define MAXV 100000
#define DFS_WHITE 0
vector<int> adj[2][MAXV]; // adj[0][] original, adj[1][] transposto
vector<int> S, dfs_num;
int N, numSCC, SCC[MAXV];

void Kosaraju(int u, int t, int comp) {
  dfs_num[u] = 1;
  if (t == 1)
    SCC[u] = comp;
  for (int j = 0; j < (int)adj[t][u].size(); j++) {
    int v = adj[t][u][j];
    if (dfs_num[v] == DFS_WHITE)
      Kosaraju(v, t, comp);
  }
  S.push_back(u);
}
void doit() { // chamar na main
  S.clear();
  dfs_num.assign(N, DFS_WHITE);
  for (int i = 0; i < N; i++)
    if (dfs_num[i] == DFS_WHITE)
      Kosaraju(i, 0, -1);
  numSCC = 0;
  dfs_num.assign(N, DFS_WHITE);
  for (int i = N - 1; i >= 0; i--)
    if (dfs_num[S[i]] == DFS_WHITE) {
      Kosaraju(S[i], 1, numSCC);
      numSCC++;
    }
  printf("There are %d SCCs\n", numSCC);
}

int main() { return 0; }