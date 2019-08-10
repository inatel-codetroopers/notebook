// Ordenacao topologia baseado em BFS. Ideia: Processar os vertices
// que nao tem aresta chegando neles. Apos processar, remover as
// arestas dele para seus vizinhos. Os vizinhos que nao tiverem mais
// arestas chegando sao inseridos na fila para serem processados
// depois.
#define MAXV 100001
vector<int> adj[MAXV];
vector<int> ordem;
void topo_sort(int N) {
  queue<int> q;
  // para mudar a ordem que os vertices sao processados pode-se se
  // usar uma priority_queue, outra estrutura para ordenar os vertices
  vector<int> in_degree(N, 0);

  rep(i, 0, N) rep(j, 0, adj[i].size())
    in_degree[adj[i][j]]++;

  rep(i, 0, N) if (in_degree[i] == 0) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ordem.push_back(u);
    rep(i, 0, adj[u].size()) {
      int v = adj[u][i];
      in_degree[v]--;
      if (in_degree[v] == 0) q.push(v);
    }
  }
  if (ordem.size() != N) {
    // grafo contem ciclos, nao eh um DAG
  }
}
int main() { return 0; }