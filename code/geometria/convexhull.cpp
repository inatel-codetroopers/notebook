/*Encontra o convex hull de um conjunto de pontos.
pivot: Ponto base para a criacao do convex hull;
radial_lt(): Ordena os pontos em sentido anti-horario (ccw).
Input: Conjunto de pontos 2D;
Output: Conjunto de pontos do convex hull, no sentido anti-horario;

(1)Se for preciso manter pontos colineares na borda do convex hull, essa
parte evita que eles sejam removidos;
*/

point pivot;
bool radial_lt(point a, point b) {
  int R = ccw(pivot, a, b);
  if (R == 0) // sao colineares
    return (pivot - a) * (pivot - a) < (pivot - b) * (pivot - b);
  else
    return (R == 1); // 1 se A esta a direita de (pivot->B)
}
vector<point> convexhull(vector<point> &T) {
  // Se for necessario remover pontos duplicadados
  sort(T.begin(), T.end()); // ordena por x e por y
  T.resize(unique(T.begin(), T.end()) - T.begin());

  int tam = 0, n = T.size();
  vector<point> U; // convex hull

  int idx = min_element(T.begin(), T.end()) - T.begin();
  // nesse caso, pivot = ponto com menor x, depois menor y
  pivot = T[idx];
  swap(T[0], T[idx]);
  sort(++T.begin(), T.end(), radial_lt);

  /*(1)*/ int k;
  for (k = n - 2; k >= 0 && ccw(T[0], T[n - 1], T[k]) == 0; k--)
    ;
  reverse((k + 1) + all(T)); /*(1)*/

  // troque <= por < para manter pontos colineares na borda
  for (int i = 0; i < T.size(); i++) {
    while (tam > 1 && ccw(U[tam - 2], U[tam - 1], T[i]) <= 0)
      U.pop_back(), tam--;
    U.pb(T[i]);
    tam++;
  }
  return U;
}
