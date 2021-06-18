const int MAX = 1e5+5;
vector<int> b[MAX+1];
vector<int> p[MAX+1];
int a[MAX];

void init() {
	REP(i, 1, MAX) {
		sort(all(p[i]));
		p[i].resize(unique(all(p[i]))-p[i].begin());
		b[i].assign(p[i].size()+1, 0);
	}
}

// Se tem query(i, x) ou add(i, x) criar ele antes
void pre_add(int i, int x) {
	if(!i) return;
	for(; i <= MAX; i += i&-i)
		p[i].pb(x);
}

void add(int i, int x, int v) {
	for(; i <= MAX; i += i&-i) {
		int id = upper_bound(all(p[i]), x)-p[i].begin();
		for(; id < b[i].size(); id += id&-id)
			b[i][id] += v;
	}
}

int query(int i, int x) {
	int sum = 0;
	for(; i; i -= i&-i) {
		int id = upper_bound(all(p[i]), x)-p[i].begin();
		for(; id; id -= id&-id)
			sum += b[i][id];
	}
	return sum;
}
