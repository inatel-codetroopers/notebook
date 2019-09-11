/**
 * fastpow() realiza exponenciacao rapida de inteiros
 * #param ll b - base da exponenciacao
 * #param ll expo - expoente
 * #param ll mod - o resultado sera calculado modulo este valor
 * #return - o valor de (b ^ p) % mod
 * #complexidade - O(log(p))
**/

ll fastpow(ll b, ll expo, ll mod) {
  ll ret = 1, pot = b % mod;
  while (expo) {
    if (expo & 1) {
      ret = (ret * pot) % mod;
    }
    pot = (pot * pot) % mod;
    expo >>= 1;
  }
  return ret;
}