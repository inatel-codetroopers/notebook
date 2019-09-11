// Dado uma sequencia formada por uma funcao f(.) e uma semente x0.
// f(x0), f(f(x0)), ..., f(f(...f(x0))), ela pode ser ciclica. Este
// algoritmo retorna o tamanho do ciclo e o valor xi que o inicia.
ii brent_cycle(int x) {
  int p = 1, length = 1, t = x, start = 0;
  int h = f(x);
  while (t != h) {
    if (p == length) {
      t = h;
      p *= 2;
      length = 0;
    }
    h = f(h);
    ++length;
  }
  t = h = x;
  for (int i = length; i != 0; --i)
    h = f(h);
  while (t != h) {
    t = f(t);
    h = f(h);
    ++start;
  }
  return ii(start, length);
}