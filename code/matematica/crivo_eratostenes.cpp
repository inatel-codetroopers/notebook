bitset<10000005> bs;
vector<int> primos;
void crivo(ll limite = 10000000LL) { // calcula primos ate limite
  primos.clear();
  bs.set();
  bs[0] = bs[1] = 0;
  for (ll i = 2; i <= limite; i++)
    if (bs[i]) {
      for (ll j = i * i; j <= limite; j += i)
        bs[j] = 0;
      primos.push_back(i);
    }
}
bool isPrime(ll N, ll limite) {
  if (N <= limite)
    return bs[N];
  for (int i = 0; i < (int)primos.size(); i++)
    if (N % primos[i] == 0)
      return false;
  return true;
}