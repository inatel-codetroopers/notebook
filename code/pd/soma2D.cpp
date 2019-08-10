/*Retorna o somatorio dos elementos de uma submatriz em O(1).
 * Submatriz definida por canto superior esquerdo (x1,y1) e  canto
 * inferior direito (x2,y2) .: x1 <= x2 && y1 <= y2 */
#define MAXN 3000
int N, M;                         // linhas colunas
long long V[MAXN + 2][MAXN + 2];  // matriz da entrada
long long S[MAXN + 2][MAXN + 2];  // matriz com as somas acumuladas

// precomputa as somas em O(N*M)
void precal() {
  rep(x, 0, N) rep(y, 0, M) {
    S[x][y] = V[x][y];
    if (x > 0) S[x][y] += S[x - 1][y];
    if (y > 0) S[x][y] += S[x][y - 1];
    if (x > 0 && y > 0) S[x][y] -= S[x - 1][y - 1];
  }
}
// retorna a soma da submatriz em O(1)
long long sum(int x1, int y1, int x2, int y2) {
  long long soma = S[x2][y2];
  if (x1 > 0) soma -= S[x1 - 1][y2];
  if (y1 > 0) soma -= S[x2][y1 - 1];
  if (x1 > 0 && y1 > 0) soma += S[x1 - 1][x1 - 1];
  return soma;
}