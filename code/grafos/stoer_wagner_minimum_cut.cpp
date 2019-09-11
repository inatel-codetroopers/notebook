/*
Retorna o corte minimo do grafo
(Conjunto de arestas que caso seja removido, desconecta o grafo)
Input: n = #vertices, g[i][j] = custo da aresta (i->j)
Output: Retorna o corte minimo
Complexidade: O(N^3)
*/

// Maximum number of vertices in the graph
#define NN 101
// Maximum edge weight (MAXW * NN * NN must fit into an int)
#define MAXW 110

// Adjacency matrix and some internal arrays
int g[NN][NN], v[NN], w[NN], na[NN], n;
bool a[NN];
int stoer_wagner() {
  // init the remaining vertex set
  for (int i = 0; i < n; i++)
    v[i] = i;
  // run Stoer-Wagner
  int best = MAXW * n * n;
  while (n > 1) {
    // initialize the set A and vertex weights
    a[v[0]] = true;
    for (int i = 1; i < n; i++) {
      a[v[i]] = false;
      na[i - 1] = i;
      w[i] = g[v[0]][v[i]];
    }
    // add the other vertices
    int prev = v[0];
    for (int i = 1; i < n; i++) {
      // find the most tightly connected non-A vertex
      int zj = -1;
      for (int j = 1; j < n; j++)
        if (!a[v[j]] && (zj < 0 || w[j] > w[zj]))
          zj = j;
      // add it to A
      a[v[zj]] = true;
      // last vertex?
      if (i == n - 1) {
        // remember the cut weight
        best = min(best, w[zj]);

        // merge prev and v[zj]
        for (int j = 0; j < n; j++)
          g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
        v[zj] = v[--n];
        break;
      }
      prev = v[zj];
      // update the weights of its neighbours
      for (int j = 1; j < n; j++)
        if (!a[v[j]])
          w[j] += g[v[zj]][v[j]];
    }
  }
  return best;
}

int main() { return 0; }