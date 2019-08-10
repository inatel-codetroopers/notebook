// Encontra maior soma contigua positiva num vetor em O(N). {s,f}
// contem o intervalo de maior soma.
int Kadane1D(int vet[], int N, int &s, int &f) {
  int ret = -INF, sum, saux;
  sum = s = f = saux = 0;
  rep(i, 0, N) {
    sum += vet[i];
    if (sum > ret) {
      ret = sum;
      s = saux;
      f = i;
    }
    if (sum < 0) {
      sum = 0;
      saux = i + 1;
    }
  }
  return ret;
}