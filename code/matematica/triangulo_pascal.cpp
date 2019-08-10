// Calcula os numeros binomiais (N,K) = N!/(K!(N-K)!). (N,K)
// representa o numero de maneiras de criar um subconjunto de tamanho
// K dado um conjunto de tamanho N. A ordem dos elementos nao
// importa.
const int MAXN = 50;
long long C[MAXN][MAXN];
void calc_pascal() {
  memset(C, 0, sizeof(C));
  for (int i = 0; i < MAXN; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j)
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
  }
}
// Pascal triangle elements:
C(33, 16) = 1.166.803.110 [int limit] C(34, 17) =
    2.333.606.220 [unsigned int limit] C(66, 33) =
        7.219.428.434.016.265.740 [int64_t limit] C(67, 33) =
            14.226.520.737.620.288.370 [uint64_t limit]
    // Fatorial
    12 ! = 479.001.600 [(unsigned)int limit] 20 ! =
        2.432.902.008.176.640.000 [(unsigned)int64_t limit]