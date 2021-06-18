// Dinic para fluxo maximo
// Grafo indexado em 1
// Inicializar maxV, source, sink
// Montar o grafo chamando
// add_edge(u,v,c,f), sendo c cap. de u->v e f flow de u->v
struct use{
	int from, to;
	ll cap, flow;
	use(int _from=-1, int _to=-1, ll _cap=0, ll _flow=0){
		from = _from;
		to = _to;
		cap = _cap;
		flow = _flow;
	}
};
 
const int maxV = 505;
int source, sink;
vector <int> adj[maxV];
vector <use> edg;
int dst[maxV];
int ptr[maxV];

void add_edge(int u, int v, int c, int f){
	adj[u].pb(edg.size());
	edg.pb(use(u, v, c, 0));
	adj[v].pb(edg.size());
	edg.pb(use(v, u, 0, 0));
}
 
bool bfs(){
	memset(dst, -1, sizeof dst);
	queue <ii> q;
	dst[source] = 0;
	q.push(ii(source, 0)); 
	
	while(!q.empty()){
		int u = q.front().F, d = q.front().S; q.pop();
		if(u==sink) return true;
		rep(i, 0, adj[u].size()){
			int id = adj[u][i];
			use aux = edg[id];
			if(dst[aux.to]!=-1) continue;
			if(aux.cap-aux.flow>0){
				dst[aux.to] = d+1;
				q.push(ii(aux.to, d+1));
			}
		}
	}
	return false;
}

ll dfs(int u, ll c){
	if(u==sink) return c;
	ll ret = 0;
	for(; ptr[u]<adj[u].size(); ptr[u]++){
		int id = adj[u][ptr[u]];
		use aux = edg[id];
		if(dst[aux.to]!=dst[u]+1) continue;
		if(aux.cap-aux.flow>0){
			ret = dfs(aux.to, min(c, aux.cap-aux.flow));
			if(ret>0){
				edg[id].flow+=ret;
				edg[id^1].flow-=ret;
				return ret;
			}
		}
	}
	return ret;
}
 
ll maxFlow(){
	ll ret = 0;
	while(bfs()){
		memset(ptr, 0, sizeof ptr);
		while(1){
			ll push = dfs(source, 1LL<<56);
			if(!push) break;
			ret+=push;
		}
	}
	return ret;
}