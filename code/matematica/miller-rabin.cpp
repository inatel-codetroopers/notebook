// Teste probabilistico de primalidade
bool miller_rabin(ll n, ll base) {
  if (n <= 1)
    return false;
  if (n % 2 == 0)
    return n == 2;
  ll s = 0, d = n - 1;
  while (d % 2 == 0)
    d /= 2, ++s;
  ll base_d = fastpow(base, d, n);
  if (base_d == 1)
    return true;
  ll base_2r = base_d;
  for (ll i = 0; i < s; ++i) {
    if (base_2r == 1)
      return false;
    if (base_2r == n - 1)
      return true;
    base_2r = base_2r * base_2r % n;
  }
  return false;
}
bool isprime(ll n) {
  if (n == 2 || n == 7 || n == 61)
    return true;
  return miller_rabin(n, 2) && miller_rabin(n, 7) &&
         miller_rabin(n, 61);
}