// Encontra os primos no intervalo [n,m]
vector<int> ret;
void primesBetween(int n, int m) {
  ret.clear();
  vector<int> primes(m - n + 1);
  for (int i = 0; i < m - n + 1; ++i)
    primes[i] = 0;
  for (int p = 2; p * p <= m; ++p) {
    int less = (n / p) * p;
    for (int j = less; j <= m; j += p)
      if (j != p && j >= n)
        primes[j - n] = 1;
  }
  for (int i = 0; i < m - n + 1; ++i) {
    if (primes[i] == 0 && n + i != 1) {
      ret.push_back(n + i);
    }
  }
}