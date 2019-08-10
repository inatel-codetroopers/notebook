// Maior subsequencia crescente
#define MAX_N 100
int vet[MAX_N], P[MAX_N], N;
void reconstruct_print(int end) {
  int x = end;
  stack<int> s;
  while (P[x] >= 0) {
    s.push(vet[x]);
    x = P[x];
  }
  printf("%d", vet[x]);
  while (!s.empty()) {
    printf(", %d", s.top());
    s.pop();
  }
}
int lis() {
  int L[MAX_N], L_id[MAX_N];
  int li = 0, lf = 0;  // lis ini, lis end
  rep(i, 0, N) {
    int pos = lower_bound(L, L + li, vet[i]) - L;
    L[pos] = vet[i];
    L_id[pos] = i;
    P[i] = pos ? L_id[pos - 1] : -1;
    if (pos + 1 > li) {
      li = pos + 1;
      lf = i;
    }
  }
  reconstruct_print(lf);
  return li;
}