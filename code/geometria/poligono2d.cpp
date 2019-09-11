/*Poligono eh representado como um array de pontos T[i] sao os vertices
do poligono. Existe uma aresta que conecta T[i] com T[i+1], e T[size-1]
com T[0]. Logo assume-se que T[0] != T[size-1]
Poligono simples: Aquele em que as arestas nao se interceptam. Convexo:
O angulo interno de T[i] com T[i-1] e T[i+1] <= 180. Concavo: Existe
algum i que nao satisfaz a condicao anterior*/

/* Retorna a area com sinal de um poligono T. Se area > 0, T esta
 * listado na ordem CCW */
double signedArea(const polygon &T) {
  double area = 0;
  int n = T.size();
  if (n < 3)
    return 0;
  rep(i, 0, n) area += cross(T[i], T[(i + 1) % n]);
  return (area / 2.0);
}

/* Retorna a area de um poligono T. (pode ser concavo ou convexo) em
 * O(N)*/
double poly_area(const polygon &T) { return fabs(signedArea(T)); }

/* Retorna a centroide de um poligono T em O(N)*/
point centroide(const polygon &T) {
  int n = T.size();
  double sgnArea = signedArea(T);

  point c = point(0, 0);
  rep(i, 0, n) {
    int k = (i + 1) % n;
    c = c + (T[i] + T[k]) * cross(T[i], T[k]);
  }
  c = c / (sgnArea * 6.0);
  return c;
}

/* Retorna o perimetro do poligono T. (pode n funcionar como esperado se
 * o poligono for uma linha reta (caso degenerado))*/
double poly_perimeter(polygon &T) {
  double perimeter = 0;
  int n = T.size();
  if (n < 3)
    return 0;
  rep(i, 0, n) perimeter += abs(T[i] - T[(i + 1) % n]);
  return perimeter;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool isSimple(const polygon &p) { // nao testado
  for (int i = 0; i < p.size(); i++) {
    for (int k = i + 1; k < p.size(); k++) {
      int j = (i + 1) % p.size();
      int l = (k + 1) % p.size();
      if (i == l || j == k)
        continue;
      if (seg_intersect(p[i], p[j], p[k], p[l]))
        return false;
    }
  }
  return true;
}

// Retorna True se T for convexo. O(N)
bool isConvex(polygon &T) {
  int n = T.size();
  if (n < 3)
    return false;

  int giro = 0;
  rep(i, 0, n) { // encontra um giro valido
    int t = ccw(T[i], T[(i + 1) % n], T[(i + 2) % n]);
    if (t != 0)
      giro = t;
  }
  if (giro == 0)
    return false; // todos pontos sao colineares

  rep(i, 0, n) {
    int t = ccw(T[i], T[(i + 1) % n], T[(i + 2) % n]);
    if (t != 0 && t != giro)
      return false;
  }
  return true;
}

//	Determina se P pertence a T, funciona para convexo ou concavo
// -1 borda, 0 fora, 1 dentro. O(N)
int in_poly(point p, polygon &T) {
  double a = 0;
  int N = T.size();
  rep(i, 0, N) {
    if (between(p, T[i], T[(i + 1) % N]))
      return -1;
    a += arg(T[i], p, T[(i + 1) % N]);
  }
  return cmp(a) != 0;
}

// determina se P pertence a B, funciona APENAS para convexo
bool PointInConvexPolygon(point P, const polygon &B) {
  int ini = 1, fim = B.size() - 2, mid, pos = -1;
  int giro = -1; // sentido horario
  while (ini <= fim) {
    mid = (ini + fim) / 2;
    int aux = ccw(B[0], B[mid], P);
    if (aux == giro) {
      pos = mid;
      ini = mid + 1;
    } else {
      fim = mid - 1;
    }
  }
  if (pos == -1)
    return false;
  if (ccw(B[0], B[pos], P) != giro * -1 &&
      ccw(B[0], B[pos + 1], P) != giro &&
      ccw(B[pos], B[pos + 1], P) == giro) // giro || 0 na borda
    return true;
  return false;
}

//	Determina o poligono interseccao de P e Q
//	P e Q devem estar orientados anti-horario.
polygon poly_intersect(polygon &P, polygon &Q) {
  int m = Q.size(), n = P.size();
  int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
  polygon R;
  while ((aa < n || ba < m) && aa < 2 * n && ba < 2 * m) {
    point p1 = P[a], p2 = P[(a + 1) % n], q1 = Q[b],
          q2 = Q[(b + 1) % m];
    point A = p2 - p1, B = q2 - q1;
    int cross = cmp(cross(A, B)), ha = ccw(p2, q2, p1),
        hb = ccw(q2, p2, q1);
    if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(dot(A, B)) < 0) {
      if (between(q1, p1, p2))
        R.push_back(q1);
      if (between(q2, p1, p2))
        R.push_back(q2);
      if (between(p1, q1, q2))
        R.push_back(p1);
      if (between(p2, q1, q2))
        R.push_back(p2);
      if (R.size() < 2)
        return polygon();
      inflag = 1;
      break;
    } else if (cross != 0 && seg_intersect(p1, p2, q1, q2)) {
      if (inflag == 0)
        aa = ba = 0;
      R.push_back(line_intersect(p1, p2, q1, q2));
      inflag = (hb > 0) ? 1 : -1;
    }
    if (cross == 0 && hb < 0 && ha < 0)
      return R;
    bool t = cross == 0 && hb == 0 && ha == 0;
    if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
      if (inflag == -1)
        R.push_back(q2);
      ba++;
      b++;
      b %= m;
    } else {
      if (inflag == 1)
        R.push_back(p2);
      aa++;
      a++;
      a %= n;
    }
  }
  if (inflag == 0) {
    if (in_poly(P[0], Q))
      return P;
    if (in_poly(Q[0], P))
      return Q;
  }
  R.erase(unique(all(R)), R.end());
  if (R.size() > 1 && R.front() == R.back())
    R.pop_back();
  return R;
}
