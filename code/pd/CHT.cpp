bool bad(int l1, int l2, int l3) {
  return (B[l3] - B[l1]) * (M[l1] - M[l2]) <
         (B[l2] - B[l1]) * (M[l1] - M[l3]);
}
void add(long long m, long long b) {
  M.push_back(m);
  B.push_back(b);
  while (M.size() >= 3 &&
         bad(M.size() - 3, M.size() - 2, M.size() - 1)) {
    M.erase(M.end() - 2);
    B.erase(B.end() - 2);
  }
}
long long query(long long x) {
  if (pointer >= M.size()) pointer = M.size() - 1;
  while (pointer < M.size() - 1 &&
         M[pointer + 1] * x + B[pointer + 1] <
             M[pointer] * x + B[pointer])
    pointer++;
  return M[pointer] * x + B[pointer];
}

struct hux {
  int a, b, id;
};
bool my_sort(hux a, hux b) {
  return a.b != b.b ? a.b > b.b : a.a > b.a;
}

const ll LINF = 1LL << 52;
const double EPS = 1e-9;
const int MAXV = 100010;

double intersept(hux a, hux b) {
  return double(b.b - a.b) / (a.a - b.a);
}

vector<pair<double, double> > convex_hux(const vector<hux> &v) {
  int p = 0, n = v.size(), bestai = v[0].a;
  double cross = 0.0;
  pair<double, int> aux;

  priority_queue<pair<double, int> > pq;
  vector<pair<double, double> > ret(n + 1, mp(-1, -1));

  pq.push(mp(cross, p));
  ret[v[p].id].F = cross, ret[v[p].id].S = LINF;

  rep(i, 1, n) {
    aux = pq.top();
    cross = aux.F, p = aux.S;

    if (v[i].a <= bestai) continue;
    bestai = v[i].a;

    double new_cross = intersept(v[i], v[p]);
    while (new_cross <= cross + EPS) {
      pq.pop();
      ret[v[p].id] = mp(-1.0, -1.0);

      aux = pq.top();
      cross = aux.F, p = aux.S;

      new_cross = intersept(v[i], v[p]);
    }

    pq.push(mp(new_cross, i));
    ret[v[p].id].S = new_cross;
    ret[v[i].id].F = new_cross;
    ret[v[i].id].S = LINF;
  }

  // rep(i, 0, n) cout << ret[i].F << " " << ret[i].S << "\n";

  return ret;
}
