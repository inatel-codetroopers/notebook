/*
Encontra o lca usando sparse table.
O(NlogN) de pre-processamento
O(1) em cada consulta

Como usar:
	main:	level[root] = 0
			dfs(root, root);
	consulta:
			lca(u,v)
*/

typedef pair<int, int> ii;

#define MAXN	(1e5+1);
#define LOGN	(23)

vector<int> adj[MAXN];
int level[MAXN];


vector<int> num;
int f[MAXN];
ii st[4*MAXN][LOGN];

void dfs(int u, int p) {
	level[u] = level[p] + 1;
	
	f[u] = num.size();
	num.pb(u);
	
	rep(i, 0, (int)adj[u].size()) {
		if(adj[u][i] == p) continue;
		dfs(adj[u][i], u);
		num.pb(u);
	}
}

ii comb(ii left, ii right)
{
	return min(left, right);
}

void SparseTable() {
	rep(i, 0, (int)num.size()) st[i][0] = make_pair(level[num[i]], num[i]);
	
	rep(k, 1, LOGN) for(int i = 0; (i + (1<<k) - 1) < (int)num.size(); i++)
		st[i][k] = comb(st[i][k - 1], st[i + (1<<(k-1))][k - 1]);
}

int lca(int u, int v)
{
	int l = f[u];
	int r = f[v];

	int k = log2(r - l + 1);
	return comb(st[l][k], st[r - (1<<k) + 1][k]).second;
}