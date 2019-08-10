// Determinar o menor E tal que B^E = N (mod P), -1 se for impossivel.
// Requer: Bezout Theorem para calcular o inverso modular
ll bsgs(ll b, ll n, ll p) {
  if (n == 1) return 0;
  map<ll, int> table;
  ll m = sqrt(p) + 1, pot = 1, pot2 = 1;
  for (int j = 0; j < m; ++j) {
    if (pot == n) return j;
    table[(n * invMod(pot, p)) % p] = j;
    pot = (pot * b) % p;
  }
  for (int i = 0; i < m; ++i) {
    if (table.find(pot2) != table.end()) return i * m + table[pot2];
    pot2 = (pot * pot2) % p;
  }
  return -1;
}