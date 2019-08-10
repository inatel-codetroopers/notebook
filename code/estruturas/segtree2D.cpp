struct node {
  int qt;
  int f1, f2, f3, f4;
};

node new_node() {
  node ret;
  ret.qt = ret.f1 = ret.f2 = ret.f3 = ret.f4 = 0;
  return ret;
}

vector<node> tree;
int cnt = 0;

bool inRange(int x1, int x2, int y1, int y2, int a1, int a2, int b1,
             int b2) {
  if (x2 < x1 || y2 < y1) return false;
  if (x2 < a1 || x1 > a2) return false;
  if (y2 < b1 || y1 > b2) return false;
  return true;
}

void update(int no, int x1, int x2, int y1, int y2, int a1, int a2,
            int b1, int b2, int val) {
  if (no == cnt) tree[cnt++] = new_node();

  if (x1 >= a1 && x2 <= a2 && y1 >= b1 && y2 <= b2) {
    tree[no].qt = val;
    return;
  }

  int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
  if (inRange(x1, (x1 + x2) / 2, y1, (y1 + y2) / 2, a1, a2, b1, b2)) {
    if (!tree[no].f1) tree[no].f1 = cnt;
    update(tree[no].f1, x1, (x1 + x2) / 2, y1, (y1 + y2) / 2, a1, a2,
           b1, b2, val);
  }
  if (inRange(x1, (x1 + x2) / 2, (y1 + y2) / 2 + 1, y2, a1, a2, b1,
              b2)) {
    if (!tree[no].f2) tree[no].f2 = cnt;
    update(tree[no].f2, x1, (x1 + x2) / 2, (y1 + y2) / 2 + 1, y2, a1,
           a2, b1, b2, val);
  }
  if (inRange((x1 + x2) / 2 + 1, x2, y1, (y1 + y2) / 2, a1, a2, b1,
              b2)) {
    if (!tree[no].f3) tree[no].f3 = cnt;
    update(tree[no].f3, (x1 + x2) / 2 + 1, x2, y1, (y1 + y2) / 2, a1,
           a2, b1, b2, val);
  }
  if (inRange((x1 + x2) / 2 + 1, x2, (y1 + y2) / 2 + 1, y2, a1, a2,
              b1, b2)) {
    if (!tree[no].f4) tree[no].f4 = cnt;
    update(tree[no].f4, (x1 + x2) / 2 + 1, x2, (y1 + y2) / 2 + 1, y2,
           a1, a2, b1, b2, val);
  }

  if (tree[no].f1) f1 = tree[tree[no].f1].qt;
  if (tree[no].f2) f2 = tree[tree[no].f2].qt;
  if (tree[no].f3) f3 = tree[tree[no].f3].qt;
  if (tree[no].f4) f4 = tree[tree[no].f4].qt;

  tree[no].qt = f1 + f2 + f3 + f4;
}

int query(int no, int x1, int x2, int y1, int y2, int a1, int a2,
          int b1, int b2) {
  if (!inRange(x1, x2, y1, y2, a1, a2, b1, b2) || no >= cnt ||
      tree[no].qt == 0)
    return 0;

  if (x1 >= a1 && x2 <= a2 && y1 >= b1 && y2 <= b2)
    return tree[no].qt;

  int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
  if (tree[no].f1)
    f1 = query(tree[no].f1, x1, (x1 + x2) / 2, y1, (y1 + y2) / 2, a1,
               a2, b1, b2);
  if (tree[no].f2)
    f2 = query(tree[no].f2, x1, (x1 + x2) / 2, (y1 + y2) / 2 + 1, y2,
               a1, a2, b1, b2);
  if (tree[no].f3)
    f3 = query(tree[no].f3, (x1 + x2) / 2 + 1, x2, y1, (y1 + y2) / 2,
               a1, a2, b1, b2);
  if (tree[no].f4)
    f4 = query(tree[no].f4, (x1 + x2) / 2 + 1, x2, (y1 + y2) / 2 + 1,
               y2, a1, a2, b1, b2);

  return f1 + f2 + f3 + f4;
}

void erase() {
  tree.clear();
  vector<node> xua;
  swap(tree, xua);
  tree.resize(1000010);
  cnt = 0;
}

int main() { return 0; }