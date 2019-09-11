typedef complex<double> comp;
const int MAX_N = 1 << 20;
int rev[MAX_N];
comp roots[MAX_N];

void preCalc(int N, int BASE) {
  for (int i = 1; i < N; ++i)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (BASE - 1));
  int NN = N >> 1;
  roots[NN] = comp(1, 0);
  roots[NN + 1] = comp(cos(2 * PI / N), sin(2 * PI / N));
  for (int i = 2; i < NN; ++i)
    roots[NN + i] = roots[NN + i - 1] * roots[NN + 1];
  for (int i = NN - 1; i > 0; --i)
    roots[i] = roots[2 * i];
}

void fft(vector<comp> &a, bool invert) {
  int N = a.size();
  if (invert)
    rep(i, 0, N) a[i] = conj(a[i]);
  rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < N; k *= 2) {
    for (int i = 0; i < N; i += 2 * k) {
      rep(j, 0, k) {
        comp B = a[i + j + k] * roots[k + j];
        a[i + j + k] = a[i + j] - B;
        a[i + j] = a[i + j] + B;
      }
    }
  }
  if (invert)
    rep(i, 0, a.size()) a[i] /= N;
}

vector<comp> multiply_real(vector<comp> a, vector<comp> b,
                           vector<comp> c) {
  int n = a.size();
  int m = b.size();

  int base = 0, N = 1;
  while (N < n + m - 1)
    base++, N <<= 1;
  preCalc(N, base);

  a.resize(N, comp(0, 0));
  c.resize(N);

  rep(i, 0, b.size()) a[i] = comp(real(a[i]), real(b[i]));
  fft(a, 0);
  rep(i, 0, N) {
    int j = (N - i) & (N - 1);
    c[i] = (a[i] * a[i] - conj(a[j] * a[j])) * comp(0, -0.25);
  }
  fft(c, 1);
  return c;
}