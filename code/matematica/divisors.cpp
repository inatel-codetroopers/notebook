// Retorna todos os divisores naturais de N em O(sqrt(N)).
vector<ll> divisores(ll N) {
  vector<ll> divisors;
  for (ll div = 1, k; div * div <= N; ++div) {
    if (N % div == 0) {
      divisors.push_back(div);
      k = N / div;
      if (k != div) divisors.push_back(k);
    }
  }
  // caso precise ordenado
  sort(divisors.begin(), divisors.end());
  return divisors;
}