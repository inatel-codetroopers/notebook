// Calcula exponenciacao de matrizes de forma eficiente. fastExp()
// calcula M[][] ^ n, e armazena o resultado em ans[][]. Eh util
// para resolver recorrencias lineares do tipo 
// F(n) = M * F(n-1)  =>  F(n) = (M^n)*F[0]
const int M = 2; 
ll mod = 1e9 + 7;
int sz = 2;
ll mat[M][M], ans[M][M], tmp[M][M];

// multiplica as matrizes a[][] e b[][] e armazena em a[][] o
// resultado
void mult(ll a[][M], ll b[][M]) {
  rep(i, 0, sz) rep(j, 0, sz) {
    tmp[i][j] = 0;
    rep(k, 0, sz) tmp[i][j] += a[i][k] * b[k][j];
    tmp[i][j] %= mod;
  }
  memcpy(a, tmp, sizeof tmp);
}

// calcula mat ^ n
void fastExp(ll ans[][M], ll n) {
  // inicializar mat, neste caso a matriz para calculo de fibonacci
  mat[0][0] = mat[0][1] = mat[1][0] = 1;
  mat[1][1] = 0;
  // matriz identidade
  rep(i, 0, sz) rep(j, 0, sz) ans[i][j] = (i == j);
  while (n) {
    if (n & 1) mult(ans, mat);
    n >>= 1;
    mult(mat, mat);
  }
  // n-\'esino termo de fibonacci
  // cout << ans[1][0]*fib(1) + ans[1][1] * fib(0) << "\n";
}