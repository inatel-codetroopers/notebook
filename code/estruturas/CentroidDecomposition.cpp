vector<int> adj[MAX];
 
struct CentroidDecomposition {
	int root;
	vector<int> sub;
	vector<int> dad;
	vector<bool> vis;

	CentroidDecomposition() {
		int TAM = N;
		dad.resize(TAM+1);
		sub.resize(TAM+1);
		vis.resize(TAM+1);
		build(1, -1);
	}
	void build(int u, int p) {
		int TAM = dfs(u, p);
		int centroid = findCentroid(u, p, TAM);
		if(p == -1) root = centroid;
		dad[centroid] = p;
		vis[centroid] = true;
		for(auto v : adj[centroid])
			if(!vis[v]) build(v, centroid);
	}
	int dfs(int u, int p) {
		sub[u] = 1;
		for(auto v : adj[u])
			if(v != p && !vis[v]) sub[u] += dfs(v, u);
		return sub[u];
	}
	int findCentroid(int u, int p, int TAM) {
		for(auto v : adj[u])
			if(v != p && !vis[v] && sub[v] > TAM/2)
				return findCentroid(v, u, TAM);
		return u;
	}
};
