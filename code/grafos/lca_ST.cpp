// MAX -> N * 4
// Consulta LCA em O(1)
const int MAX = 4e3+3;
vector<int> adj[MAX];
int st[2][MAX][20];
int h[MAX], g[MAX];
vector<int> num;
int f[MAX];

void dfs(int u, int p) {	// chamar dfs(root, root) na main
	f[u] = num.size();
	h[u] = h[p]+1;
	num.pb(u);
	rep(i, 0, (int)adj[u].size()) {
		if(adj[u][i] == p) continue;
		dfs(adj[u][i], u);
		num.pb(u);
	}
}

void SparseTable() {
	rep(i, 0, (int)num.size()) st[1][i][0] = num[i];
	rep(i, 0, (int)num.size()) st[0][i][0] = h[num[i]];
	rep(j, 1, 20) for(int i = 0; (i+(1<<j)-1) < (int)num.size(); i++) {
		st[0][i][j] = min(st[0][i][j-1], st[0][i+(1<<(j-1))][j-1]);
		st[1][i][j] = st[0][i][j-1] < st[0][i+(1<<(j-1))][j-1] ? st[1][i][j-1] : 
			st[1][i+(1<<(j-1))][j-1];
	}
}

int query(int l, int r) {		// return lca entre os vertives (l, r)
	int k = log2(r-l+1);
	return st[0][l][k] < st[0][r-(1<<k)+1][k] ?
		st[1][l][k] : st[1][r-(1<<k)+1][k];
}
