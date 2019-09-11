// Conjuntos Disjuntos. Inicialmente cada elemento eh lider de seu
// proprio conjunto. Operacoes de join(u,v) fazem com que os conjuntos
// que u e v pertencem se unam. find(u) retorna o lider do conjunto
// que u esta contido.
#define MAXV 100000
int V, pai[MAXV], rnk[MAXV], size[MAXV];

void init() { rep(i, 0, V) pai[i] = i, rnk[i] = 0, size[i] = 1; }

int find(int v) {
  if (v != pai[v])
    pai[v] = find(pai[v]);
  return pai[v];
}

void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;

  if (rnk[u] < rnk[v])
    swap(u, v);
  pai[v] = u; // add v no conjunto de u
  size[u] += size[v];
  if (rnk[u] == rnk[v])
    rnk[u]++;
}

bool same_set(int u, int v) { return find(u) == find(v); }

int main() { return 0; }