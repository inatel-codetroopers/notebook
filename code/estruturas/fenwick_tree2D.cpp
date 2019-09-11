#define MAXL 3001
#define MAXC 3001
ll ft[MAXL][MAXC];
int L, C;
// update(x,y,v) incrementa v na posicao (x,y) .: M[x][y] += v em
// O(log(N))
void update(int x, int y, int v) {
  for (; x <= L; x += x & -x)
    for (int yy = y; yy <= C; yy += yy & -yy)
      ft[x][yy] += v;
}

// query(x,y) retorna o somatorio da submatriz definida por
// (1,1)->(x,y) .: sum += M[i][j] para todo 1 <= i <= x e 1 <= j <= y,
// em O(log(N))
ll query(int x, int y) {
  if (x <= 0 || y <= 0)
    return 0;
  ll sum = 0;
  for (; x > 0; x -= x & -x)
    for (int yy = y; yy > 0; yy -= yy & -yy)
      sum += ft[x][yy];
  return sum;
}

// query(x1,y1,x2,y2) retorna o somatorio da submatriz definida por
// (x1,x1) -- (x2,y2) .: sum += M[i][j] para todo x1 <= i <= x2 e y1
// <= j <= y2, em O(log(N))
ll query(int x1, int y1, int x2, int y2) {
  return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) +
         query(x1 - 1, y1 - 1);
}

// A ideia de atualizar um intervalo (submatriz) e consultar um
// elemento (i,j) tambem sao validos
int main() { return 0; }