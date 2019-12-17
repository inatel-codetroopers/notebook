const int MAX = 1e5 + 5;
const int MAXT = 80 * MAX;
int a[MAX], tree[MAXT];
int L[MAXT], R[MAXT];
vector<int> root;
int cnt;

void build(int no, int i, int j) {
  if (i == j) {
    tree[no] = a[i];
    return;
  }
  L[no] = ++cnt;
  R[no] = ++cnt;
  build(L[no], i, (i + j) / 2);
  build(R[no], (i + j) / 2 + 1, j);
  tree[no] = tree[L[no]] + tree[R[no]];
}

int update(int no, int i, int j, int p, int v) {
  int NO = ++cnt;
  if (i == j) {
    tree[NO] = v;
    return NO;
  }
  
  L[NO] = L[no];
  R[NO] = R[no];

  if (p <= (i + j)/2) L[NO] = update(L[NO], i, (i + j) / 2, p, v);
  else                R[NO] = update(R[NO], (i + j) / 2 + 1, j, p, v);
  
  tree[NO] = tree[L[NO]] + tree[R[NO]];
  return NO;
}

int query(int no, int i, int j, int l, int r) {
  if (i > r || j < l)   return 0;
  if (i >= l && j <= r) return tree[no];

  int left  = query(L[no], i, (i + j) / 2, l, r);
  int right = query(R[no], (i + j) / 2 + 1, j, l, r);
  return left + right;
}

void init() {
  memset(tree, 0, sizeof tree);
  root.clear();
  root.pb(0);
  cnt = 0;
}

int main(int argc, char **argv) {
  query(root[k], 1, N, l, r));	// consulta na versao k
  root.pb(update(root[sz], 1, N, l, v)); // update
  return 0;
}
