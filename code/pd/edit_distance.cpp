//[IME] menor custo para transformar a em b, dado as operacoes de
// inserir, remover e substituir caracteres de a
int editDistance(string a, string b) {
  int cost, insertCost = 1, deletCost = 1, substCost = 1;
  int m = a.size();
  int n = b.size();
  int d[m + 1][n + 1];
  for (int i = 0; i <= m; i++)
    d[i][0] = i * deletCost;
  for (int j = 0; j <= n; j++)
    d[0][j] = j * insertCost;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++) {
      if (a[i - 1] == b[j - 1])
        cost = 0;
      else
        cost = substCost;
      d[i][j] =
          min(d[i - 1][j] + deletCost,
              min(d[i][j - 1] + insertCost, d[i - 1][j - 1] + cost));
    }
  return d[m][n];
}