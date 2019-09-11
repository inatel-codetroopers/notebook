// RSQ agora com queries e updates em intervalos. Precisa de Lazy
// Propagation. Array A[] deve ser indexado em 0. Nem sempre o array
// que sera modificado armazena apenas um valor, nesse caso usamos
// struct para representar cada no.
#define MAXN 500000
ll A[MAXN], tree[4 * MAXN], lazy[4 * MAXN];
int N;
int neutro = 0;

// funcao que realiza o merge de um intervalo, pode ser *, -, min,
// max, etc...
int combine(int segEsq, int segDir) { return segEsq + segDir; }

void build(int no = 1, int a = 0, int b = N - 1) {
  if (a == b) {
    tree[no] = A[a];
    return;
  }
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;
  build(esq, a, m);
  build(dir, m + 1, b);
  tree[no] = combine(tree[esq], tree[dir]);
}

void propagate(int no, int a, int b) {
  if (lazy[no] != 0) {
    // esta parte depende do problema, neste caso queremos adicionar o
    // valor lazy[no] no intervalo [a,b], mas estamos atualizando
    // apenas o noh que representa este intervalo
    tree[no] += (b - a + 1) * lazy[no];
    if (a != b) {
      lazy[2 * no] += lazy[no];
      lazy[2 * no + 1] += lazy[no];
    }
    lazy[no] = 0;
  }
}

// update(i,j,v) faz A[k] += v, para i <= k <= j, em log(N)
void update(int i, int j, ll v, int no = 1, int a = 0, int b = N - 1) {
  if (lazy[no])
    propagate(no, a, b);
  if (a > j || b < i)
    return;
  if (a >= i && b <= j) {
    lazy[no] += v; // atualiza apenas a flag da raiz da subarvore
    propagate(no, a, b);
    return;
  }
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;
  update(i, j, v, esq, a, m);
  update(i, j, v, dir, m + 1, b);
  tree[no] = combine(tree[esq], tree[dir]);
}

// query(i,j) retorna o somatorio A[i] + A[i+1] + ... + A[j]
ll query(int i, int j, int no = 1, int a = 0, int b = N - 1) {
  if (lazy[no])
    propagate(no, a, b);
  if (a > j || b < i)
    return neutro;
  if (a >= i && b <= j)
    return tree[no];
  int m = (a + b) / 2;
  int esq = 2 * no;
  int dir = esq + 1;
  ll q1 = query(i, j, esq, a, m);
  ll q2 = query(i, j, dir, m + 1, b);
  return combine(q1, q2);
}

int main() { return 0; }