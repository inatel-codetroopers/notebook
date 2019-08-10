const int MAX = 100010;
int gap, tam, sa[MAX], pos[MAX], lcp[MAX], tmp[MAX];

bool sufixCmp(int i, int j) {
  if (pos[i] != pos[j]) return pos[i] < pos[j];
  i += gap, j += gap;
  return (i < tam && j < tam) ? pos[i] < pos[j] : i > j;
}
void buildSA(char s[]) {
  tam = strlen(s);
  for (int i = 0; i < tam; i++) sa[i] = i, pos[i] = s[i], tmp[i] = 0;

  for (gap = 1;; gap *= 2) {
    sort(sa, sa + tam, sufixCmp);
    tmp[0] = 0;
    for (int i = 0; i < tam - 1; i++)
      tmp[i + 1] = tmp[i] + sufixCmp(sa[i], sa[i + 1]);
    for (int i = 0; i < tam; i++) pos[sa[i]] = tmp[i];
    if (tmp[tam - 1] == tam - 1) break;
  }
}
ll buildLCP(char s[]) {
  ll sum = 0;
  for (int i = 0, k = 0; i < tam; i++) {
    if (pos[i] == tam - 1) continue;
    for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k];) k++;
    lcp[pos[i] + 1] = k;
    sum += k;
    if (k > 0) k--;
  }
  return sum;
}
void PrintAll(char s[]) {
  printf("SA\ttam\tLCP\tSuffix\n");
  rep(i, 0, tam) printf("%2d\t%2d\t%2d\t%s\n", sa[i], tam - sa[i],
                        lcp[i], s + sa[i]);
}
ll num_subs(ll m) { return (ll)tam * (tam + 1) / 2 - m; }
ll num_subsrn() {
  ll ret = 0;
  rep(i, 1, tam) if (lcp[i] > lcp[i - 1]) ret += lcp[i] - lcp[i - 1];
  return ret;
}
void printans(char s[], int n) {
  int maior = 0, id = -1;
  rep(i, 0, tam) if (lcp[i] > n && lcp[i] > maior) maior = lcp[i],
                                                   id = i;
  if (id == -1)
    printf("*");
  else
    rep(i, sa[id], sa[id] + maior) printf("%c", s[i]);
  printf("\n");
}

char s[MAX];
int main() {
  while (1) {
    scanf("%s", s);
    if (s[0] == '*') break;

    buildSA(s);
    ll m = buildLCP(s);

    PrintAll(s);  // printa sa, lcp, suffixs
    // printf("%lld\n", num_subs(m)); //numero de substrings nao
    // repetidas printf("%lld\n", num_subsrn()); //numero de substrings
    // que se repete printans(s, 2); //maior substring de tamanho maior
    // ou igual a n que se repete
  }
}