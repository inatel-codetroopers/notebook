/*Lowest Common Ancestor (LCA) entre dois vertices A, B de uma arvore.
LCA(A,B) = ancestral mais proximo de A adj B. O codigo abaixo tambem
calcula a menor aresta do caminho entre A adj B. Para saber quantas
arestas tem entre A adj B basta fazer:
level[A]+level[B]-2*level[lca(A,B)]
Pode-se modificar para retorna a
distancia entre A adj B. Como usar: (1) ler a arvore em adj[] adj W[],
chamar doit(raiz), passando a raiz da arvore. Indexar em 0 os vertices
(2) A funcao retorna o LCA adj a menor aresta entre A adj B.
*/

const int MAX = 1e5+5;    // quantidade de vertices
const int LOG = 20;       // profundidade maxima 2^(maxl) > MAXV
int pai[MAX][LOG + 1];    // pai[v][i] = pai de v subindo 2^i arestas
int dist[MAX][LOG + 1];   // dist[v][i] = menor aresta de v subindo
                          // 2^i arestas
int lvl[MAX];             // level[v] = #arestas de v ate a raiz

int N, M;                         // numero de vertices adj arestas
vector<pair<int, int>> adj[MAXV]; // {v,custo}


void dfs(int u, int p, int w = (1<<30)) {
	pai[u][0] = p;
	dist[u][0] = w;
	lvl[u] = lvl[p] + 1;
	REP(i, 1, 20) {
		pai[u][i] = pai[pai[u][i-1]][i-1];
		dist[u][i] = min(dist[u][i-1], dist[pai[u][i-1]][i-1]);
	}
	for(auto [v, cost] : adj[u])
	    if(v != p) dfs(v, u, cost);
}

int lca(int a, int b) {
	int menor = INF;
	if(lvl[a] < lvl[b])
		swap(a, b);
	PER(i, 20, 0) {
		if(lvl[pai[a][i]] >= lvl[b])
			menor = min(menor, dist[a][i]), a = pai[a][i];
	}
	if(a == b) return menor;
	PER(i, 20, 0) {
		if(pai[a][i] != pai[b][i]) {
			menor = min(menor, min(dist[a][i], dist[b][i]));
			a = pai[a][i]; b = pai[b][i];
		}
	}
	menor = min(menor, min(dist[a][0], dist[b][0]));
	a = pai[a][0], b = pai[b][0];
	return menor;
}

