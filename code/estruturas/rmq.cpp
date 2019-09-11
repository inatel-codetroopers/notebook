// Range Minimum Query: idx do menor elemento num intervalo de um
// array. Permite consultas e updates no array em O(logN).  ATENCAO:
// Array A[] deve ser indexado em 0;
#define MAXN 500000
int A[MAXN], T[4 * MAXN];
int N; // #number of elements in A[]
int neutro = -1;

// combina o resultado de dois segmentos
int combine(int p1, int p2) {
  if (p1 == -1)
    return p2;
  if (p2 == -1)
    return p1;
  if (A[p1] <= A[p2])
    return p1;
  else
    return p2;
}

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

// Modifica A[i] em O(logN), neste caso A[i] = v
void update(int i, int v, int no = 1, int a = 0, int b = N - 1) {
  if (a > i || b < i)
    return;
  if (a == i && b == i) {
    A[i] = v;
    T[no] = i; // desnecessario ;p
    return;
  }
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;
  update(i, v, esq, a, m);
  update(i, v, dir, m + 1, b);
  T[no] = combine(T[esq], T[dir]);
}

// Retorna o idx k do menor valor A[k] no intervalo [i,j] em O(logN)
int query(int i, int j, int no = 1, int a = 0, int b = N - 1) {
  if (a > j || b < i)
    return neutro;
  if (a >= i && b <= j)
    return T[no];
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;

  int p1 = query(i, j, esq, a, m);
  int p2 = query(i, j, dir, m + 1, b);
  return combine(p1, p2);
}

int main() { return 0; }