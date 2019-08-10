// Calcula a integral de f[a, b]
typedef long double ld;

ld f(double x) {
  // return f(x)
}

ld romberg(ld a, ld b) {
  ld R[16][16], div = (b - a) / 2;
  R[0][0] = div * (f(a) + f(b));
  for (int n = 1; n <= 15; n++, div /= 2) {
    R[n][0] = R[n - 1][0] / 2;
    for (ld sample = a + div; sample < b; sample += 2 * div)
      R[n][0] += div * f(a + sample);
  }
  for (int m = 1; m <= 15; m++)
    for (int n = m; n <= 15; n++)
      R[n][m] = R[n][m - 1] +
                1 / (pow(4, m) - 1) * (R[n][m - 1] - R[n - 1][m - 1]);
  return R[15][15];
}
