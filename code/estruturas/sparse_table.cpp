/*
Resolve problemas de consulta a intervalos (RSQ, RMQ etc) de um vetor
estatico, ou seja, os valores nao sofrem update.
Alterar a funcao comb() de acordo (min, max, soma etc)
Pre-processamento O(NlogN) e consulta em O(1).
N = tamanho do vetor a[]
a[] deve ser indexado em 0
*/
const int MAXN = (1e6 + 1);
#define LOGN (21)
int st[MAXN][LOGN];
int N, a[MAXN];

int comb(int left, int right) { return min(left, right); }

void SparseTable() {
  rep(k, 0, LOGN) for (int i = 0; (i + (1 << k) - 1) < N; i++)
      st[i][k] =
          k ? comb(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]) : a[i];
}

int query(int l, int r) {
  int k = log2(r - l + 1);
  return comb(st[l][k], st[r - (1 << k) + 1][k]);
}