const int MAX = 2e5+5;
vector<int> adj[MAX];
vector<int> seg[MAX];
int cntI, cntG;
int group[MAX];
int first[MAX];
int p[MAX][21];
int szG[MAX];
int lvl[MAX];
int ind[MAX];
int sz[MAX];
int w[MAX];
int a[MAX];
int N, Q;

void build(int G, int no, int i, int j) {
	if(i == j) return void(seg[G][no] = a[i]);
	build(G, no*2, i, (i+j)/2);
	build(G, no*2+1, (i+j)/2+1, j);
	seg[G][no] = max(seg[G][no*2], seg[G][no*2+1]);
}
 
void update(int G, int no, int i, int j, int p, int v) {
	if(i > p || j < p) return;
	if(i == j) return void(seg[G][no] = v);
	update(G, no*2, i, (i+j)/2, p, v);
	update(G, no*2+1, (i+j)/2+1, j, p, v);
	seg[G][no] = max(seg[G][no*2], seg[G][no*2+1]);
}
 
int query(int G, int no, int i, int j, int l, int r) {
	if(i > r || j < l) return 0;
	if(i >= l && j <= r) return seg[G][no];
	return 	max(query(G, no*2, i, (i+j)/2, l, r),
				query(G, no*2+1, (i+j)/2+1, j, l, r));
}
 
int path_solve(int u, int v) {
	int ans = -1;
	while(group[u] != group[v]) {
		int L = ind[first[group[u]]];
		ans = max(ans, query(group[u], 1, L, L + szG[group[u]]-1, ind[first[group[u]]],  ind[u]));
		u = p[first[group[u]]][0];
	}
	int L = ind[first[group[u]]];
	return max(ans, query(group[u], 1, L, L + szG[group[u]]-1, ind[v],  ind[u]));
}

void dfs(int u, int P) {
	if(u == P) first[++cntG] = u;
	group[u] = cntG;
	szG[cntG]++;	
	a[++cntI] = w[u];
	ind[u] = cntI;
	int Vm = -1;
	for(auto v : adj[u])
		if(v != P && (Vm == -1 || sz[v] > sz[Vm])) Vm = v;
	if(Vm != -1) dfs(Vm, u);
	for(auto v : adj[u])
		if(v != P && v != Vm) {
			first[++cntG] = v;
			dfs(v, u);
		}
}

int pre_dfs(int u, int P) {
	sz[u] = 1;
	p[u][0] = P;
	lvl[u] = lvl[P] + 1;
	REP(i, 1, 20)
		p[u][i] = p[p[u][i-1]][i-1];
	for(auto v : adj[u])
		if(v != P) sz[u] = max(sz[u], pre_dfs(v, u)+1);
	return sz[u];
}

int lca(int u, int v) {
	if(lvl[u] < lvl[v]) swap(u, v);
	PER(i, 20, 0)
		if(lvl[p[u][i]] >= lvl[v])
			u = p[u][i];
	if(u == v) return u;
	PER(i, 20, 0)
		if(p[u][i] != p[v][i])
			u = p[u][i], v = p[v][i];
	return p[u][0];
}

int path(int u, int v) {
	int a = lca(u, v);
	return max(path_solve(u, a), path_solve(v, a));
}
