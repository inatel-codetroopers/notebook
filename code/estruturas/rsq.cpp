// Range Sum Query: retorna a soma do intervalo de um array. Permite
// consultas e updates em O(logN). ATENCAO: Array A[] deve ser
// indexado em 0;
#define MAXN 500000
int N; // #number of elements in A[]
int A[MAXN], T[4 * MAXN];
int neutro = 0;

// combina o resultado de dois segmentos
int combine(int sumLeft, int sumRight) { return sumLeft + sumRight; }

// chamar build() apos preencher o vetor A[]. O(N)
void build(int no = 1, int a = 0, int b = N - 1) {
  if (a == b) {
    T[no] = a;
  } else {
    int m = (a + b) / 2;
    int esq = 2 * no;
    int dir = esq + 1;
    build(esq, a, m);
    build(dir, m + 1, b);
    T[no] = combine(T[esq], T[dir]);
  }
}

// update(pos, valor) faz A[pos] += valor em O(logN)
void update(int pos, int valor, int no = 1, int a = 0, int b = N - 1) {
  if (a > pos || b < pos)
    return;
  if (a == b && a == pos) {
    A[pos] += valor;
    T[no] += valor;
    return;
  }
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;
  update(pos, valor, esq, a, m);
  update(pos, valor, dir, m + 1, b);
  T[no] = combine(T[esq], T[dir]);
}

// query(i,j) retorna a soma do intervalo [i,j] em O(logN)
int query(int i, int j, int no = 1, int a = 0, int b = N - 1) {
  if (a > j || b < i)
    return neutro;
  if (a >= i && b <= j)
    return T[no];
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;

  int sumLeft = query(i, j, esq, a, m);
  int sumRight = query(i, j, dir, m + 1, b);
  return combine(sumLeft, sumRight);
}

int main() {
  // ler N e A[] (A indexado em 0)
  // build() para montar a arvore
  return 0;
}