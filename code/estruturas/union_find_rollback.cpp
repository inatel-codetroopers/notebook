int pai[MAX];
int tam[MAX];
stack<pair<int, int>> old_pai;
stack<pair<int, int>> old_tam;

void init() {
  for (int i = 1; i <= MAX; ++i) {
    pai[i] = i;
    tam[i] = 1;
  }
}

int find(int x) {
  if (pai[x] == x) return x;
  else return find(pai[x]);
}

void merge(int u, int v) {
  int a = find(u);
  int b = find(v);
  if (tam[a] > tam[b]) swap(a, b);
  old_pai.emplace(a, pai[a]);
  old_tam.emplace(b, tam[b]);
  pai[a] = b;
  tam[b] += tam[a];
}

void rollback() {
  pai[old_pai.top().first] = old_pai.top().second;
  tam[old_tam.top().first] = old_tam.top().second;
  old_pai.pop();
  old_tam.pop();
}
