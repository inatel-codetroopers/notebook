#define LINE 0
#define SEGMENT 1
#define RAY 2
int sgn(double x) { return (x > EPS) - (x < -EPS); }

#define vec(ini, fim) (fim - ini)
struct PT {
  double x, y, z;
  PT() { x = y = z = 0; }
  PT(double x, double y, double z) : x(x), y(y), z(z) {}
  PT operator+(PT q) { return PT(x + q.x, y + q.y, z + q.z); }
  PT operator-(PT q) { return PT(x - q.x, y - q.y, z - q.z); }
  PT operator*(double d) { return PT(x * d, y * d, z * d); }
  PT operator/(double d) { return PT(x / d, y / d, z / d); }
  double dist2() const { return x * x + y * y + z * z; }
  double dist() const { return sqrt(dist2()); }
  bool operator==(const PT &a) const {
    return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS &&
           fabs(z - a.z) < EPS;
  }
};

double dot(PT A, PT B) { return A.x * B.x + A.y * B.y + A.z * B.z; }
PT cross(PT A, PT B) {
  return PT(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z,
            A.x * B.y - A.y * B.x);
}
bool collinear(PT A, PT B, PT C) {
  return sgn(cross(B - A, C - A)) == 0;
}

inline double det(double a, double b, double c, double d) {
  return a * d - b * c;
}
inline double det(double a11, double a12, double a13, double a21,
                  double a22, double a23, double a31, double a32,
                  double a33) {

  return a11 * det(a22, a23, a32, a33) -
         a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}
inline double det(const PT &a, const PT &b, const PT &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

// tamanho do vetor A
double norma(PT A) { return sqrt(dot(A, A)); }

// distancia^2 de (a->b)
double distSq(PT a, PT b) { return dot(a - b, a - b); }

// Projeta vetor A sobre o vetor B
PT project(PT A, PT B) { return B * dot(A, B) / dot(B, B); }

// Verifica se existe interseccao de segmentos
// (assumir que [A,B] e [C,D] sao coplanares)
bool seg_intersect(PT A, PT B, PT C, PT D) {
  return cmp(dot(cross(A - B, C - B), cross(A - B, D - B))) <= 0 &&
         cmp(dot(cross(C - D, A - D), cross(C - D, B - D))) <= 0;
}

// square distance between point and line, ray or segment
double ptLineDistSq(PT s1, PT s2, PT p, int type) {
  double pd2 = distSq(s1, s2);
  PT r;
  if (pd2 == 0)
    r = s1;
  else {
    double u = dot(p - s1, s2 - s1) / pd2;
    r = s1 + (s2 - s1) * u;
    if (type != LINE && u < 0.0)
      r = s1;
    if (type == SEGMENT && u > 1.0)
      r = s2;
  }
  return distSq(r, p);
}

//  Distancia de ponto P ao segmento [A,B]
double dist_point_seg(PT P, PT A, PT B) {
  PT PP = A + project(P - A, B - A);
  if (cmp(norma(A - PP) + norma(PP - B), norma(A - B)) == 0)
    return norma(P - PP); // distance point-line!
  else
    return min(norma(P - A), norma(P - B));
}

// Distance between lines ab and cd. TODO: Test this
double lineLineDistance(PT a, PT b, PT c, PT d) {
  PT v1 = b - a;
  PT v2 = d - c;
  PT cr = cross(v1, v2);
  if (dot(cr, cr) < EPS) {
    PT proj = v1 * (dot(v1, c - a) / dot(v1, v1));
    return sqrt(dot(c - a - proj, c - a - proj));
  } else {
    PT n = cr / sqrt(dot(cr, cr));
    PT p = dot(n, c - a);
    return sqrt(dot(p, p));
  }
}

//	Menor distancia do segmento [A,B] ao segmento [C,D] (lento*)
#define dps dist_point_seg
double dist_seg_seg(PT A, PT B, PT C, PT D) {
  PT E = project(A - D, cross(B - A, D - C));
  // distance between lines!
  if (seg_intersect(A, B, C + E, D + E)) {
    return norma(E);
  } else {
    double dA = dps(A, C, D), dB = dps(B, C, D);
    double dC = dps(C, A, B), dD = dps(D, A, B);
    return min(min(dA, dB), min(dC, dD));
  }
}

//  Menor distancia do segmento [A,B] ao segmento [C,D] (rapido*)
double dist_seg_seg2(PT A, PT B, PT C, PT D) {
  PT u(B - A), v(D - C), w(A - C);
  double a = dot(u, u), b = dot(u, v);
  double c = dot(v, v), d = dot(u, w), e = dot(v, w);

  double DD = a * c - b * b;
  double sc, sN, sD = DD;
  double tc, tN, tD = DD;
  if (DD < EPS) {
    sN = 0, sD = 1, tN = e, tD = c;
  } else {
    sN = (b * e - c * d);
    tN = (a * e - b * d);
    if (sN < 0) {
      sN = 0, tN = e, tD = c;
    } else if (sN > sD) {
      sN = sD, tN = e + b, tD = c;
    }
  }
  if (tN < 0) {
    tN = 0;
    if (-d < 0)
      sN = 0;
    else if (-d > a)
      sN = sD;
    else {
      sN = -d;
      sD = a;
    }
  } else if (tN > tD) {
    tN = tD;
    if ((-d + b) < 0)
      sN = 0;
    else if (-d + b > a)
      sN = sD;
    else {
      sN = -d + b;
      sD = a;
    }
  }
  sc = fabs(sN) < EPS ? 0 : sN / sD;
  tc = fabs(tN) < EPS ? 0 : tN / tD;
  PT dP = w + (u * sc) - (v * tc);
  return norma(dP);
}

//  Distancia de Ponto a Triangulo, dps = dist_point_seg
double dist_point_tri(PT P, PT A, PT B, PT C) {
  PT N = cross(B - A, C - A);
  PT PP = P - project(P - A, N);
  PT R1, R2, R3;
  R1 = cross(B - A, PP - A);
  R2 = cross(C - B, PP - B);
  R3 = cross(A - C, PP - C);

  if (cmp(dot(R1, R2)) >= 0 && cmp(dot(R2, R3)) >= 0 &&
      cmp(dot(R3, R1)) >= 0) {
    return norma(P - PP);
  } else {
    return min(dps(P, A, B), min(dps(P, B, C), dps(P, A, C)));
  }
}

// compute a, b, c, d such that all points lie on ax + by + cz = d.
// TODO: test this
void planeFromPts(PT p1, PT p2, PT p3, double &a, double &b, double &c,
                  double &d) {
  PT normal = cross(p2 - p1, p3 - p1);
  a = normal.x;
  b = normal.y;
  c = normal.z;
  d = -a * p1.x - b * p1.y - c * p1.z;
}

// project point onto plane. TODO: test this
PT ptPlaneProj(PT p, double a, double b, double c, double d) {
  double l =
      (a * p.x + b * p.y + c * p.z + d) / (a * a + b * b + c * c);
  return PT(p.x - a * l, p.y - b * l, p.z - c * l);
}

// distance from point p to plane aX + bY + cZ + d = 0
double ptPlaneDist(PT p, double a, double b, double c, double d) {
  return fabs(a * p.x + b * p.y + c * p.z + d) /
         sqrt(a * a + b * b + c * c);
}

// distance between parallel planes aX + bY + cZ + d1 = 0 and
// aX + bY + cZ + d2 = 0
double planePlaneDist(double a, double b, double c, double d1,
                      double d2) {
  return fabs(d1 - d2) / sqrt(a * a + b * b + c * c);
}

// Volume de Tetraedro
double signedTetrahedronVol(PT A, PT B, PT C, PT D) {
  double A11 = A.x - B.x;
  double A12 = A.x - C.x;
  double A13 = A.x - D.x;
  double A21 = A.y - B.y;
  double A22 = A.y - C.y;
  double A23 = A.y - D.y;
  double A31 = A.z - B.z;
  double A32 = A.z - C.z;
  double A33 = A.z - D.z;
  double det = A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
  return det / 6;
}

// Parameter is a vector of vectors of points - each interior vector
// represents the 3 points that make up 1 face, in any order.
// Note: The polyhedron must be convex, with all faces given as
// triangles.
double polyhedronVol(vector<vector<PT>> poly) {
  int i, j;
  PT cent(0, 0, 0);
  for (i = 0; i < poly.size(); i++)
    for (j = 0; j < 3; j++)
      cent = cent + poly[i][j];
  cent = cent * (1.0 / (poly.size() * 3));
  double v = 0;
  for (i = 0; i < poly.size(); i++)
    v += fabs(signedTetrahedronVol(cent, poly[i][0], poly[i][1],
                                   poly[i][2]));
  return v;
}

// Outras implementacoes [Usa struct PT]

struct line { // reta definida por um ponto p e direcao v
  PT p, v;
  line(){};
  line(const PT &p, const PT &v) : p(p), v(v) { assert(!(v == PT())); }
  bool on(const PT &pt) const { return cross(pt - p, v) == PT(); }
};
struct plane {
  PT n;
  double d;
  plane() : d(0) {}
  plane(const PT &p1, const PT &p2, const PT &p3) {
    n = cross(p2 - p1, p3 - p1);
    d = -dot(n, p1);
    assert(side(p1) == 0);
    assert(side(p2) == 0);
    assert(side(p3) == 0);
  }
  int side(const PT &p) const { return sgn(dot(n, p) + d); }
};

// interesecao de retas
int intersec(const line &l1, const line &l2, PT &res) {
  assert(!(l1.v == PT()));
  assert(!(l2.v == PT()));
  if (cross(l1.v, l2.v) == PT()) {
    if (cross(l1.v, l1.p - l2.p) == PT())
      return 2; // same
    return 0;   // parallel
  }
  PT n = cross(l1.v, l2.v);
  PT p = l2.p - l1.p;
  if (sgn(dot(n, p)))
    return 0; // skew
  double t;
  if (sgn(n.x))
    t = (p.y * l2.v.z - p.z * l2.v.y) / n.x;
  else if (sgn(n.y))
    t = (p.z * l2.v.x - p.x * l2.v.z) / n.y;
  else if (sgn(n.z))
    t = (p.x * l2.v.y - p.y * l2.v.x) / n.z;
  else
    assert(false);
  res = l1.p + l1.v * t;
  assert(l1.on(res));
  assert(l2.on(res));
  return 1; // intersects
}

// distancia entre 2 retas
double dist(const line &l1, const line &l2) {
  PT ret = l1.p - l2.p;
  ret = ret - l1.v * (dot(l1.v, ret) / l1.v.dist2());
  PT tmp = l2.v - l1.v * (dot(l1.v, l2.v) / l1.v.dist2());
  if (sgn(tmp.dist2()))
    ret = ret - tmp * (dot(tmp, ret) / tmp.dist2());
  assert(fabs(dot(ret, l1.v)) < eps);
  assert(fabs(dot(ret, tmp)) < eps);
  assert(fabs(dot(ret, l2.v)) < eps);
  return ret.dist();
}

// Retorna os dois pontos mais proximos entre l1 e l2
void closest(const line &l1, const line &l2, PT &p1, PT &p2) {
  if (cross(l1.v, l2.v) == PT()) {
    p1 = l1.p;
    p2 = l2.p - l1.v * (dot(l1.v, l2.p - l1.p) / l1.v.dist2());
    return;
  }
  PT p = l2.p - l1.p;
  double t1 =
      (dot(l1.v, p) * l2.v.dist2() - dot(l1.v, l2.v) * dot(l2.v, p)) /
      cross(l1.v, l2.v).dist2();
  double t2 =
      (dot(l2.v, l1.v) * dot(l1.v, p) - dot(l2.v, p) * l1.v.dist2()) /
      cross(l2.v, l1.v).dist2();
  p1 = l1.p + l1.v * t1;
  p2 = l2.p + l2.v * t2;
  assert(l1.on(p1));
  assert(l2.on(p2));
}

// retorna a intersecao de reta com plano [retorna 1 se intersecao for
// pt]
int cross(const line &l, const plane &pl, PT &res) {
  double d = dot(pl.n, l.v);
  if (sgn(d) == 0) {
    return (pl.side(l.p) == 0) ? 2 : 0;
  }
  double t = (-dot(pl.n, l.p) - pl.d) / d;
  res = l.p + l.v * t;
#ifdef DEBUG
  assert(pl.side(res) == 0);
#endif
  return 1;
}

bool cross(const plane &p1, const plane &p2, const plane &p3,
           PT &res) {
  double d = det(p1.n, p2.n, p3.n);
  if (sgn(d) == 0) {
    return false;
  }
  PT px(p1.n.x, p2.n.x, p3.n.x);
  PT py(p1.n.y, p2.n.y, p3.n.y);
  PT pz(p1.n.z, p2.n.z, p3.n.z);
  PT p(-p1.d, -p2.d, -p3.d);
  res = PT(det(p, py, pz) / d, det(px, p, pz) / d, det(px, py, p) / d);
#ifdef DEBUG
  assert(p1.side(res) == 0);
  assert(p2.side(res) == 0);
  assert(p3.side(res) == 0);
#endif
  return true;
}

// retorna reta da intersecao de dois planos
int cross(const plane &p1, const plane &p2, line &res) {
  res.v = cross(p1.n, p2.n);
  if (res.v == PT()) {
    if ((p1.n * (p1.d / p1.n.dist2())) ==
        (p2.n * (p2.d / p2.n.dist2())))
      return 2;
    else
      return 0;
  }
  plane p3;
  p3.n = res.v;
  p3.d = 0;
  bool ret = cross(p1, p2, p3, res.p);
  assert(ret);
  assert(p1.side(res.p) == 0);
  assert(p2.side(res.p) == 0);
  return 1;
}

// testes
int main() {
  {
    line l;
    l.p = PT(1, 1, 1);
    l.v = PT(1, 0, -1);
    plane p(PT(10, 11, 12), PT(9, 8, 7), PT(1, 3, 2));
    PT res;
    assert(cross(l, p, res) == 1);
  }
  {
    plane p1(PT(1, 2, 3), PT(4, 5, 6), PT(-1, 5, -4));
    plane p2(PT(3, 2, 1), PT(6, 5, 4), PT(239, 17, -42));
    line l;
    assert(cross(p1, p2, l) == 1);
  }
  {
    plane p1(PT(1, 2, 3), PT(4, 5, 6), PT(-1, 5, -4));
    plane p2(PT(1, 2, 3), PT(7, 8, 9), PT(3, -1, 10));
    line l;
    assert(cross(p1, p2, l) == 2);
  }
  {
    plane p1(PT(1, 2, 3), PT(4, 5, 6), PT(-1, 5, -4));
    plane p2(PT(1, 2, 4), PT(4, 5, 7), PT(-1, 5, -3));
    line l;
    assert(cross(p1, p2, l) == 0);
  }

  line l1, l2;
  while (l1.p.load()) {
    l1.v.load();
    l1.v = l1.v - l1.p;
    l2.p.load();
    l2.v.load();
    l2.v = l2.v - l2.p;
    if (l1.v == PT() || l2.v == PT())
      continue;
    PT res;
    int cnt = intersec(l1, l2, res);
    double d = dist(l1, l2);
    if (fabs(d) < eps)
      assert(cnt >= 1);
    else
      assert(cnt == 0);
    PT p1, p2;
    closest(l1, l2, p1, p2);
    assert(fabs((p1 - p2).dist() - d) < eps);
  }
  plane a(PT(1, 0, 0), PT(0, 1, 0), PT(0, 0, 1));
  plane b(PT(-1, 0, 0), PT(0, -1, 0), PT(0, 0, -1));
  line l;
  assert((cross(a, b, l)) == 0);
  return 0;
}
