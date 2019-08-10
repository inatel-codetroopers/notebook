// Permite realizar operacoes de query e update em um vetor em O(logN)
// Obs: A[] deve ser indexado em 1, nao em 0.
#define MAXN 100001
ll ft[MAXN];
ll A[MAXN];
int N;

// ATUALIZA UM INDICE i, CONSULTA UM INTERVALO (i,j)
// update(i, valor) faz A[i] += valor em log(N)
void update(int i, ll valor) {
  for (; i <= N; i += i & -i) ft[i] += valor;
}

// query(i) retorna a soma A[1] + ... + A[i] em log(N)
ll query(int i) {
  ll sum = 0;
  for (; i > 0; i -= i & -i) sum += ft[i];
  return sum;
}

// query(i,j) retorna a soma A[i] + A[i+1] + ... + A[j] em log(N)
ll query(int i, int j) { return query(j) - query(i - 1); }
// ATUALIZA UM INTERVALO (i,j), CONSULTA UM ELEMENTO i
// range_update(i,j,valor) faz A[k] += valor, para i <= k <= j em
// log(N) query(i): retorna o valor de A[i] em log(N)
void range_update(int i, int j, ll valor) {
  update(i, valor);
  update(j + 1, -valor);
}

int main() { return 0; }