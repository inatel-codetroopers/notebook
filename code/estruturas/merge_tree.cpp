const int MAX = 5e5+5;
vector<int> tree[4*MAX];
int a[MAX];

void build(int no, int i, int j) {
	if(i == j) { tree[no].pb(a[i]); return; }
	build(no*2, i, (i+j)/2);
    build(no*2+1, (i+j)/2+1, j);
	merge(all(tree[no*2]), all(tree[no*2+1]), back_inserter(tree[no]));
}

int query(int no, int i, int j, int l, int r) {
	if(i > r || j < l) return 0;
	if(i >= l && j <= r)
        return (lower_bound(all(tree[no]), l)-tree[no].begin());
	return query(no*2, i, (i+j)/2, l, r) + query(no*2+1, (i+j)/2+1, j, l, r);
}
