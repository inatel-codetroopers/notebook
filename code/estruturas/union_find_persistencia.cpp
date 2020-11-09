int pai[MAX_N+1];
int tam[MAX_N+1];
int his[MAX_N+1];
int tempo;

void init() {
  tempo = 0;
  for (int i = 1; i <= MAX_N; ++i) {
    pai[i] = i;
    tam[i] = 1;
    his[i] = 0;
  }
}

int find(int x, int t) {
  if (pai[x] == x) return x;
  if (his[x] > t) return x;
  return find(pai[x], t);
}

void merge(int u, int v) {
  tempo += 1;
  int a = find(u, tempo);
  int b = find(v, tempo);
  if (tam[a] > tam[b]) swap(a, b);
  pai[a] = b;
  his[a] = tempo;
  tam[b] += tam[a];
}
