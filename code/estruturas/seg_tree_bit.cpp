const int MAX = 5e5 + 5;
map<int, int> tree[4 * MAX];
vector<int> a(MAX), mp(MAX);

void update(int no, int x) {
    for(; x; x -= x & -x) tree[no][x]++;
}

int query(int no, int x) {
    int ans = 0;
    for(; x < MAX; x += x & -x)
        if(tree[no].count(x)) ans += tree[no][x];
    return ans;
}

void build(int no, int i, int j) {
    if(i == j) {
        int NO = no;
        while (NO) {
            update(NO, a[i]);
            NO >>= 1;
        }
        return;
    }
    build(no * 2, i, (i + j) / 2);
    build(no * 2 + 1, (i + j) / 2 + 1, j);
}

// quantidade de elementos em a(L, R) que é >= L
int query(int no, int i, int j, int l, int r) { 
    if(i > r || j < l) return 0;
    if(i >= l && j <= r) return(j - i + 1) - query(no, l);
    return query(no * 2, i, (i + j) / 2, l, r) + query(no * 2 + 1, (i + j) / 2 + 1, j, l, r);
}
