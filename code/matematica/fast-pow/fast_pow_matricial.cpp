/**
 * fastpow() realiza exponenciacao rapida de matrizes
 * #param matrix_t M - matriz a ser elevada
 * #param ll expo - expoente
 * #param ll mod - o resultado sera calculado modulo este valor
 * #return - o resultado de (M ^ expo) % mod
 * #complexidade - O(size^3 * log(expo))
**/

#define MAX (ChangeMe) // Max size of square matrix

struct matrix_t {
  ll m[MAX][MAX];
  int sz;
  matrix_t(int _sz) {
    memset(m, 0, sizeof(m));
    sz = _sz;
  }
  matrix_t multiply(const matrix_t other, ll mod) {
    matrix_t ret(other.sz);
    rep(i, 0, sz) rep(j, 0, sz) {
      ret.m[i][j] = 0;
      rep(k, 0, sz) ret.m[i][j] =
          (ret.m[i][j] + (m[i][k] * other.m[k][j]) % mod) % mod;
    }
    return ret;
  }
};

matrix_t fastpow(matrix_t M, ll expo, ll mod) {
  matrix_t ret(M.sz);
  // Identity matrix
  rep(i, 0, ret.sz) rep(j, 0, ret.sz) ret.m[i][j] = (i == j);

  while (expo) {
    if (expo & 1)
      ret = ret.multiply(M, mod);
    M = M.multiply(M, mod);
    expo >>= 1;
  }
  return ret;
}