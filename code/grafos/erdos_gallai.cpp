// Determina se existe um grafo tal que b[i] eh o grau do i-esimo
// vertice. Vertices indexado em 1. Apenas armazenar em b[1...N] e
// chamar EGL()
long long b[100005], n;
long long dmax, dmin, dsum, num_degs[100005];

bool basic_graphical_tests() {  // Sort and perform some simple tests
                                // on the sequence
  int p = n;
  memset(num_degs, 0, (n + 1) * sizeof(long long));

  dmax = dsum = n = 0;
  dmin = p;
  for (int d = 1; d <= p; d++) {
    if (b[d] < 0 || b[d] >= p)
      return false;
    else if (b[d] > 0) {
      if (dmax < b[d]) dmax = b[d];
      if (dmin > b[d]) dmin = b[d];
      dsum = dsum + b[d];
      n++;
      num_degs[b[d]]++;
    }
  }
  if (dsum % 2 || dsum > n * (n - 1)) return false;
  return true;
}
bool EGL() {
  long long k, sum_deg, sum_nj, sum_jnj, run_size;

  if (!basic_graphical_tests()) return false;
  if (n == 0 || 4 * dmin * n >= (dmax + dmin + 1) * (dmax + dmin + 1))
    return true;

  k = sum_deg = sum_nj = sum_jnj = 0;
  for (int dk = dmax; dk >= dmin; dk--) {
    if (dk < k + 1) return true;

    if (num_degs[dk] > 0) {
      run_size = num_degs[dk];
      if (dk < k + run_size) run_size = dk - k;
      sum_deg += run_size * dk;

      for (int v = 0; v < run_size; v++) {
        sum_nj += num_degs[k + v];
        sum_jnj += (k + v) * num_degs[k + v];
      }
      k += run_size;
      if (sum_deg > k * (n - 1) - k * sum_nj + sum_jnj) return false;
    }
  }
  return true;
}
int main() { return 0; }