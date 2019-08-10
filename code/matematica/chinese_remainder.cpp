// crt() retorna um  X tal que X = a[i] (mod m[i]). Exemplo: Para a[]
// = {1, 2, 3} e m[] = {5, 6, 7} .: X = 206. Requer: Bezout Theorem
// para calcular o inverso modular
#define MAXN 1000
int n;
ll a[MAXN], m[MAXN];
ll crt() {
  ll M = 1, x = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i)
    x += a[i] * invMod(M / m[i], m[i]) * (M / m[i]);
  return (((x % M) + M) % M);
}