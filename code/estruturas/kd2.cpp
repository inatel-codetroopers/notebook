struct point {
  int x, y, z;
  point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
  point operator-(point q) { return point(x - q.x, y - q.y, z - q.z); }
  int operator*(point q) { return x * q.x + y * q.y + z * q.z; }
};

typedef vector<point> polygon;
priority_queue<double> vans;
int NN, CC, KK, DD;

struct KDTreeNode {
  point p;
  int level;
  KDTreeNode *below, *above;
  KDTreeNode(const point &q, int levl) {
    p = q;
    level = levl;
    below = above = 0;
  }
  ~KDTreeNode() { delete below, above; }
  int diff(const point &pt) {
    switch (level) {
    case 0:
      return pt.x - p.x;
    case 1:
      return pt.y - p.y;
    case 2:
      return pt.z - p.z;
    }
    return 0;
  }
  ll distSq(point &q) { return (p - q) * (p - q); }
  int rangeCount(point &pt, ll K) {
    int count = (distSq(pt) <= K * K) ? 1 : 0;
    if (count)
      vans.push(-sqrt(distSq(pt)));

    int d = diff(pt);
    if (~d <= K && above != 0)
      count += above->rangeCount(pt, K);
    if (d <= K && below != 0)
      count += below->rangeCount(pt, K);
    return count;
  }
};

class KDTree {
public:
  polygon P;
  KDTreeNode *root;
  int dimention;
  KDTree() {}
  KDTree(polygon &poly, int D) {
    P = poly;
    dimention = D;
    root = 0;
    build();
  }
  ~KDTree() { delete root; }
  // count the number of pairs that has a distance less than K
  ll countPairs(ll K) {
    ll count = 0;
    rep(i, 0, P.size()) count += root->rangeCount(P[i], K) - 1;
    return count;
  }

protected:
  void build() {
    // random_shuffle(all(P));
    rep(i, 0, P.size()) { root = insert(root, P[i], -1); }
  }
  KDTreeNode *insert(KDTreeNode *t, const point &pt, int parentLevel) {
    if (t == 0) {
      t = new KDTreeNode(pt, (parentLevel + 1) % dimention);
      return t;
    } else {
      int d = t->diff(pt);
      if (d <= 0)
        t->below = insert(t->below, pt, t->level);
      else
        t->above = insert(t->above, pt, t->level);
    }
    return t;
  }
};

int main() {
  point e;
  e.z = 0;
  polygon p;
  set<ii> st;

  while (scanf("%d %d %d %d", &NN, &CC, &KK, &DD) != EOF) {
    p.clear();
    KK = min(NN, KK);
    st.clear();

    rep(i, 0, NN) {
      scanf("%d %d", &e.x, &e.y);
      st.insert(mp(e.x, e.y));
      p.pb(e);
    }

    KDTree tree(p, 2);
    int ans = 0;
    rep(i, 0, CC) {
      scanf("%d %d", &e.x, &e.y);
      if (st.count(mp(e.x, e.y)))
        continue;

      ll at = 0;
      rep(i, 0, 30) {
        at = ll(1) << i;
        while (!vans.empty())
          vans.pop();
        int aux = tree.root->rangeCount(e, at);
        if (aux >= KK)
          break;
      }
      double sum = 0.0;
      rep(i, 0, KK) {
        sum += -vans.top();
        vans.pop();
      }
      if (sum >= DD)
        ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}