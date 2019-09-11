/*Encontra o casamento bipartido maximo/minimo com peso nas arestas
Criar o grafo:
Hungarian G(L, R, ehMaximo)
L = #vertices a esquerda
R = #vertices a direita
ehMaximo = variavel booleana que indica se eh casamento maximo ou
minimo

Adicionar arestas:
G.add_edge(x,y,peso)
x = vertice da esquerda no intervalo [0,L-1]
y = vertice da direita no intervalo [0,R-1]
peso = custo da aresta
obs: tomar cuidado com multiplas arestas.

Resultado:
match_value = soma dos pesos dos casamentos
pairs = quantidade de pares (x-y) casados
xy[x] = vertice y casado com x
yx[y] = vertice x casado com y

Complexidade do algoritmo: O(V^3)
Problemas resolvidos: SCITIES (SPOJ)
 */

struct Hungarian {
  enum { MAXN = 150, INF = 0x3f3f3f3f };
  int cost[MAXN][MAXN];
  int xy[MAXN], yx[MAXN];
  bool S[MAXN], T[MAXN];
  int lx[MAXN], ly[MAXN], slack[MAXN], slackx[MAXN], prev[MAXN];
  int match_value, pairs;
  bool ehMaximo;
  int n;

  Hungarian(int L, int R, bool _ehMaximo = true) {
    n = max(L, R);
    ehMaximo = _ehMaximo;
    if (ehMaximo)
      memset(cost, 0, sizeof cost);
    else
      memset(cost, INF, sizeof cost);
  }

  void add_edge(int x, int y, int peso) {
    if (!ehMaximo)
      peso *= (-1);
    cost[x][y] = peso;
  }

  int solve() {
    match_value = 0;
    pairs = 0;
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    init_labels();
    augment();
    for (int x = 0; x < n; ++x)
      match_value += cost[x][xy[x]];
    return match_value;
  }

  void init_labels() {
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int x = 0; x < n; ++x)
      for (int y = 0; y < n; ++y)
        lx[x] = max(lx[x], cost[x][y]);
  }

  void augment() {
    if (pairs == n)
      return;
    int x, y, root;
    int q[MAXN], wr = 0, rd = 0;
    memset(S, false, sizeof(S));
    memset(T, false, sizeof(T));
    memset(prev, -1, sizeof(prev));
    for (x = 0; x < n; ++x)
      if (xy[x] == -1) {
        q[wr++] = root = x;
        prev[x] = -2;
        S[x] = true;
        break;
      }
    for (y = 0; y < n; ++y) {
      slack[y] = lx[root] + ly[y] - cost[root][y];
      slackx[y] = root;
    }
    while (true) {
      while (rd < wr) {
        x = q[rd++];
        for (y = 0; y < n; ++y)
          if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
            if (yx[y] == -1)
              break;
            T[y] = true;
            q[wr++] = yx[y];
            add(yx[y], x);
          }
        if (y < n)
          break;
      }
      if (y < n)
        break;
      update_labels();
      wr = rd = 0;
      for (y = 0; y < n; ++y)
        if (!T[y] && slack[y] == 0) {
          if (yx[y] == -1) {
            x = slackx[y];
            break;
          } else {
            T[y] = true;
            if (!S[yx[y]]) {
              q[wr++] = yx[y];
              add(yx[y], slackx[y]);
            }
          }
        }
      if (y < n)
        break;
    }
    if (y < n) {
      ++pairs;
      for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
        ty = xy[cx];
        yx[cy] = cx;
        xy[cx] = cy;
      }
      augment();
    }
  }

  void add(int x, int prevx) {
    S[x] = true;
    prev[x] = prevx;
    for (int y = 0; y < n; ++y)
      if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
        slack[y] = lx[x] + ly[y] - cost[x][y];
        slackx[y] = x;
      }
  }

  void update_labels() {
    int x, y, delta = INF;
    for (y = 0; y < n; ++y)
      if (!T[y])
        delta = min(delta, slack[y]);
    for (x = 0; x < n; ++x)
      if (S[x])
        lx[x] -= delta;
    for (y = 0; y < n; ++y)
      if (T[y])
        ly[y] += delta;
    for (y = 0; y < n; ++y)
      if (!T[y])
        slack[y] -= delta;
  }

  int casouComX(int x) { return xy[x]; }

  int casouComY(int y) { return yx[y]; }
};

// O codigo abaixo resolve o problema scities (Spoj)
int main() {
  int casos;
  cin >> casos;
  while (casos--) {
    int L, R;
    cin >> L >> R;
    Hungarian G(L, R, true);

    int x, y, w, aux[L][R];
    memset(aux, 0, sizeof aux);
    while (scanf("%d %d %d", &x, &y, &w) != EOF) {
      if (x == 0 && y == 0 && w == 0)
        break;
      aux[x - 1][y - 1] += w;
    }
    for (int x = 0; x < L; x++) {
      for (int y = 0; y < R; y++) {
        if (aux[x][y] != 0) {
          G.add_edge(x, y, aux[x][y]);
        }
      }
    }
    printf("%d\n", G.solve());
  }
  return 0;
}
