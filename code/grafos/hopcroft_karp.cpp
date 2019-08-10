/*Encontra o casamento bipartido maximo em O(sqrt(V)*E)
1) Chamar init(L,R) #vertices da esquerda, #vertices da direita
2) Usar addEdge(Li,Ri) para adicionar a aresta Li -> Ri
3) maxMatching() retorna o casamento maximo.
matching[Rj] -> armazena Li */

#define MAXN1 3010
#define MAXN2 3010
#define MAXM 6020
int n1, n2, edges, last[MAXN1], pre[MAXM], head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

void init(int L, int R) {
  n1 = L, n2 = R;
  edges = 0;
  fill(last, last + n1, -1);
}
void addEdge(int u, int v) {
  head[edges] = v;
  pre[edges] = last[u];
  last[u] = edges++;
}
void bfs() {
  fill(dist, dist + n1, -1);
  int sizeQ = 0;
  for (int u = 0; u < n1; ++u) {
    if (!used[u]) {
      Q[sizeQ++] = u;
      dist[u] = 0;
    }
  }
  for (int i = 0; i < sizeQ; i++) {
    int u1 = Q[i];
    for (int e = last[u1]; e >= 0; e = pre[e]) {
      int u2 = matching[head[e]];
      if (u2 >= 0 && dist[u2] < 0) {
        dist[u2] = dist[u1] + 1;
        Q[sizeQ++] = u2;
      }
    }
  }
}
bool dfs(int u1) {
  vis[u1] = true;
  for (int e = last[u1]; e >= 0; e = pre[e]) {
    int v = head[e];
    int u2 = matching[v];
    if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
      matching[v] = u1;
      used[u1] = true;
      return true;
    }
  }
  return false;
}
int maxMatching() {
  fill(used, used + n1, false);
  fill(matching, matching + n2, -1);
  for (int res = 0;;) {
    bfs();
    fill(vis, vis + n1, false);
    int f = 0;
    for (int u = 0; u < n1; ++u)
      if (!used[u] && dfs(u)) ++f;
    if (!f) return res;
    res += f;
  }
}

int main() { return 0; }
