const int MAX = 2e5+5;
vector<int> adj[MAX];

struct CentroidDecomposition {
	int root;
	vector<int> sub;
	vector<int> dad;
	vector<int> lvl;
	vector<bool> vis;
	vector<vector<int>> pai;
	CentroidDecomposition(int N) {
		sub.resize(N+1);
		dad.resize(N+1);
		vis.resize(N+1);
		lvl.resize(N+1);
		pai.resize(N+1);
		build(1, -1);
		dfs_lca(root, root);
	}
	void build(int u, int p) {
		int N = dfs(u, u);
		int centroid = findCentroid(u, p, N);
		if(p == -1) root = centroid;
		vis[centroid] = true;
		dad[centroid] = p;
		for(auto v : adj[centroid])
			if(!vis[v]) build(v, centroid);
	}
	int dfs(int u, int p) {
		sub[u] = 1;
		for(auto v : adj[u])
			if(v != p && !vis[v])
				sub[u] += dfs(v, u);
		return sub[u];
	}
	int findCentroid(int u, int p, int N) {
		for(auto v : adj[u])
			if(v != p && !vis[v] && sub[v] > N/2)
				return findCentroid(v, u, N);
		return u;
	}
	void dfs_lca(int u, int p) {
		pai[u].resize(21);
		pai[u][0] = p;
		lvl[u] = lvl[p] + 1;
		REP(i, 1, 20) pai[u][i] = pai[pai[u][i-1]][i-1];
		for(auto v : adj[u])
			if(v != p) dfs_lca(v, u);
	}
	int lca(int u, int v) {
		if(lvl[u] < lvl[v]) swap(u, v);
		PER(i, 20, 0)
			if(lvl[pai[u][i]] >= lvl[v])
				u = pai[u][i];
		if(u == v) return u;
		PER(i, 20, 0)
			if(pai[u][i] != pai[v][i])
				u = pai[u][i], v = pai[v][i];
		return pai[u][0];
	}
	int dist(int u, int v) {
		int a = lca(u, v);
		return lvl[u] + lvl[v] - 2 * lvl[a];
	}
};
