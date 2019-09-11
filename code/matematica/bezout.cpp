// Determina a solucao da equacao a*x+b*y = gcd(a, b), onde a e b sao
// dois numeros naturais. Como chamar: egcd(a, b), Retorna: a tupla
// {gcd(a, b), x, y}.  Determina tambem o Inverso Modular.
struct Triple {
  ll d, x, y;
  Triple(ll q, ll w, ll e) : d(q), x(w), y(e) {}
};
Triple egcd(ll a, ll b) {
  if (!b)
    return Triple(a, 1, 0);
  Triple q = egcd(b, a % b);
  return Triple(q.d, q.y, q.x - a / b * q.y);
}
// Retorna o inverso modular de A modulo N
// O inverso modular de um numero A em relacao a N eh um numero X tal
// que (A*X)%N = 1
ll invMod(ll a, ll n) {
  Triple t = egcd(a, n);
  if (t.d > 1)
    return 0;
  return (t.x % n + n) % n;
}