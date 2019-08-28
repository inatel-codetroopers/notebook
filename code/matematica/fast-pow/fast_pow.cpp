// Calcula (B^P)%MOD em O(logP). Calcula o inverso modular de b(modulo
// mod) se mod for primo. Basta fazer invB = fastpow(b,mod-2,mod)
ll fastpow(ll b, ll p, ll mod) {
  ll ret = 1;
  for (ll pot = b; p > 0; p >>= 1, pot = (pot * pot) % mod)
    if (p & 1) ret = (ret * pot) % mod;
  return ret;
}