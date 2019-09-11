const double EPS = 1e-9;
inline int cmp(double x, double y = 0, double tol = EPS) {
  return ((x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1);
}

struct point {
  double x, y;
  point(double x = 0, double y = 0) : x(x), y(y) {}
  point operator+(point q) { return point(x + q.x, y + q.y); }
  point operator-(point q) { return point(x - q.x, y - q.y); }
  point operator*(double t) { return point(x * t, y * t); }
  point operator/(double t) { return point(x / t, y / t); }
  int cmp(point q) const {
    if (int t = ::cmp(x, q.x))
      return t;
    return ::cmp(y, q.y);
  }
  bool operator==(point q) const { return cmp(q) == 0; };
  bool operator!=(point q) const { return cmp(q) != 0; };
  bool operator<(point q) const { return cmp(q) < 0; };
};
ostream &operator<<(ostream &os, const point &p) {
  os << "(" << p.x << "," << p.y << ")";
}
#define vec(a, b) (b - a)
typedef vector<point> polygon;

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double collinear(point a, point b, point c) {
  return cmp(cross(b - a, c - a)) == 0;
}
// retorna 1 se R esta a esquerda do vetor P->Q, -1 se estiver a
// direita. 0 se P, Q e R forem colineares
int ccw(point p, point q, point r) { return cmp(cross(q - p, r - p)); }

// Rotaciona um ponto em relacao a origem em 90 graus sentido
// anti-horario
point RotateCCW90(point p) { return point(-p.y, p.x); }
// Rotaciona um ponto em relacao a origem em 90 graus sentido horario
point RotateCW90(point p) { return point(p.y, -p.x); }

// Rotaciona um ponto P em A graus no sentido anti-horario em relacao a
// origem; Para rotacionar no sentido horario, basta A ser negativo
point RotateCCW(point p, double a) {
  a = (a / 180.0) * acos(-1.0); // convertendo para radianos
  return point(p.x * cos(a) - p.y * sin(a),
               p.x * sin(a) + p.y * cos(a));
}
// Rotaciona P em A graus em relacao a Q.
point RotateCCW(point p, point q, double a) {
  return RotateCCW(p - q, a) + q;
}
// Tamanho ou norma de um vetor
double abs(point u) { return sqrt(dot(u, u)); }
// Projeta o vetor A sobre a direcao do vetor B
point project(point a, point b) { return b * (dot(a, b) / dot(b, b)); }
// Retorna a projecao do ponto P sobre reta definida por [A,B]
point projectPointLine(point p, point a, point b) {
  return p + project(p - a, b - a);
}
// Retorna o angulo que p faz com +x
double arg(point p) { return atan2(p.y, p.x); }
// Retorna o angulo entre os vetores AB e AC
double arg(point b, point a, point c) {
  point u = b - a, v = c - a;
  return atan2(cross(u, v), dot(u, v));
}

//////////////////////////////////////////////////////////////////////
/////////////////////////  Segmentos, Retas  /////////////////////////
//////////////////////////////////////////////////////////////////////

// Determina se P esta entre o segmento fechado [A,B], inclusive
bool between(point p, point a, point b) {
  return collinear(p, a, b) && dot(a - p, b - p) <= 0;
}

/* Distancia de ponto P para reta que passa por [A,B]. Armazena em C
 * (por ref) o ponto projecao de P na reta. */
double distancePointLine(point p, point a, point b, point &c) {
  c = projectPointLine(p, a, b);
  return fabs(cross(p - a, b - a)/abs(a - b); // or abs(p-c);
}

/* Distancia de ponto P ao segmento [A,B]. Armazena em C (por ref) o
 * ponto de projecao de P em [A,B]. Se este ponto estiver fora do
 * segmento, eh retornado o mais proximo. */
double distancePointSeg(point p, point a, point b, point &c) {
  if ((b - a) * (p - a) <= 0) {
    c = a;
    return abs(a - p);
  }
  if ((a - b) * (p - b) <= 0) {
    c = b;
    return abs(b - p);
  }

  c = projectPointLine(p, a, b);
  return fabs(cross(p - a, b - a)/abs(a - b); // or abs(p-c);
}

// Determina se os segmentos [A, B] e [C, D] se tocam
bool seg_intersect(point a, point b, point c, point d) {
  int d1, d2, d3, d4;
  d1 = ccw(c, a, d);
  d2 = ccw(c, b, d);
  d3 = ccw(a, c, b);
  d4 = ccw(a, d, b);
  if (d1 * d2 == -1 && d3 * d4 == -1)
    return true;
  if (d1 == 0 && between(c, a, d))
    return true;
  if (d2 == 0 && between(c, b, d))
    return true;
  if (d3 == 0 && between(a, c, b))
    return true;
  if (d4 == 0 && between(a, d, b))
    return true;
  return false;
}

// Encontra a interseccao das retas (p-q) e (r-s) assumindo que existe
// apenas 1 intereccao. Se for entre segmentos, verificar se
// interseptam primeiro.
point line_intersect(point p, point q, point r, point s) {
  point a = q - p, b = s - r, c = point(cross(p, q), cross(r, s));
  double x = cross(point(a.x, b.x), c);
  double y = cross(point(a.y, b.y), c);
  return point(x, y) / cross(a, b);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(point a, point b, point c, point d) { //! Nao
                                                         //! testado
  return fabs(cross(b - a, c - d)) < EPS;
}
bool LinesCollinear(point a, point b, point c,
                    point d) { //! Nao testado
  return LinesParallel(a, b, c, d) &&
         fabs(cross(a - b, a - c)) < EPS &&
         fabs(cross(c - d, c - a)) < EPS;
}

//////////////////////////////////////////////////////////////////////
////////////////////////////  Triangulos  ////////////////////////////
//////////////////////////////////////////////////////////////////////

bool pointInTriangle(point p, point a, point b, point c) {
  // TODO
}

// Heron's formula - area do triangulo(a,b,c) -1 se nao existe
double area_heron(double a, double b, double c) {
  if (a < b)
    swap(a, b);
  if (a < c)
    swap(a, c);
  if (b < c)
    swap(b, c);
  if (a > b + c)
    return -1;
  return sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) *
              (a + (b - c)) / 16.0);
}

//////////////////////////////////////////////////////////////////////
////////////////////////////  Circulos  //////////////////////////////
//////////////////////////////////////////////////////////////////////

bool pointInCircle(point p, point c, double radius) {
  // Todo
}

/*Dado dois pontos (A, B) de uma circunferencia e seu raio R, eh
 * possivel obter seus possiveis centros (C1 e C2). Para obter o outro
 * centro, basta inverter os paramentros */
bool circle2PtsRad(point a, point b, double r, point &c) {
  point aux = a - b;
  double d = dot(aux, aux);
  double det = r * r / d - 0.25;
  if (det < 0.0)
    return false;
  double h = sqrt(det);
  c.x = (a.x + b.x) * 0.5 + (a.y - b.y) * h;
  c.y = (a.y + b.y) * 0.5 + (b.x - a.x) * h;
  return true;
}

//	Menor distancia entre dois pontos numa esfera de raio r
//	lat = [-90,90]; long = [-180,180]
double spherical_distance(double lt1, double lo1, double lt2,
                          double lo2, double r) {
  double pi = acos(-1);
  double a = pi * (lt1 / 180.0), b = pi * (lt2 / 180.0);
  double c = pi * ((lo2 - lo1) / 180.0);
  return r * acos(sin(a) * sin(b) + cos(a) * cos(b) * cos(c));
}

//////////////////////////////////////////////////////////////////////
/////////////////////////////  Planos  ///////////////////////////////
//////////////////////////////////////////////////////////////////////

// Distancia entre (x,y,z) e plano ax+by+cz=d
double distancePointPlane(double x, double y, double z, double a,
                          double b, double c, double d) {
  return fabs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

//***[Inicio] Funcoes que usam numeros complexos para pontos***
typedef complex<double> cxpt;
struct circle {
  cxpt c;
  double r;
  circle(cxpt c, double r) : c(c), r(r) {}
  circle() {}
};
double cross(const cxpt &a, const cxpt &b) {
  return imag(conj(a) * b);
}
double dot(const cxpt &a, const cxpt &b) { return real(conj(a) * b); }

// Area da interseccao de dois circulos
double circ_inter_area(circle &a, circle &b) {
  double d = abs(b.c - a.c);
  if (d <= (b.r - a.r))
    return a.r * a.r * M_PI;
  if (d <= (a.r - b.r))
    return b.r * b.r * M_PI;
  if (d >= a.r + b.r)
    return 0;
  double A = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
  double B = acos((b.r * b.r + d * d - a.r * a.r) / (2 * b.r * d));
  return a.r * a.r * (A - 0.5 * sin(2 * A)) +
         b.r * b.r * (B - 0.5 * sin(2 * B));
}

// Pontos de interseccao de dois circulos
// Intersects two circles and intersection points are in 'inter'
// -1-> outside, 0-> inside, 1-> tangent, 2-> 2 intersections
int circ_circ_inter(circle &a, circle &b, vector<cxpt> &inter) {
  double d2 = norm(b.c - a.c), rS = a.r + b.r, rD = a.r - b.r;
  if (d2 > rS * rS)
    return -1;
  if (d2 < rD * rD)
    return 0;
  double ca = 0.5 * (1 + rS * rD / d2);
  cxpt z = cxpt(ca, sqrt((a.r * a.r / d2) - ca * ca));
  inter.push_back(a.c + (b.c - a.c) * z);
  if (abs(z.imag()) > EPS)
    inter.push_back(a.c + (b.c - a.c) * conj(z));
  return inter.size();
}

// Line-circle intersection
// Intersects (infinite) line a-b with circle c
// Intersection points are in 'inter'
// 0 -> no intersection, 1 -> tangent, 2 -> two intersections
int line_circ_inter(cxpt a, cxpt b, circle c, vector<cxpt> &inter) {
  c.c -= a;
  b -= a;
  cxpt m = b * real(c.c / b);
  double d2 = norm(m - c.c);
  if (d2 > c.r * c.r)
    return 0;
  double l = sqrt((c.r * c.r - d2) / norm(b));
  inter.push_back(a + m + l * b);
  if (abs(l) > EPS)
    inter.push_back(a + m - l * b);
  return inter.size();
}
//***[FIM] Funcoes que usam numeros complexos para pontos***