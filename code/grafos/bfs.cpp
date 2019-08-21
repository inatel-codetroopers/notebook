// bfs (exemplo: calculando distancias a partir da origem)
// Complexidade O(V+E)
#define INF 0x3f3f3f3f
#define MAXV (112345)
 
int V, E; // #Vertices, #Arestas
vector<int> adj[MAXV];
int dist[MAXV];

void bfs(int src){
    queue <int> Q;
    memset(dist, INF, sizeof(dist));
    dist[src] = 0;
    
    Q.push(src);
    while (!Q.empty()){
        int u = Q.front();
        printf("Dist from %d to %d = %d\n", src, u, dist[u]);
        for (auto v : adj[u]){
            if(dist[u] + 1 < dist[v]){
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
}

int main(){
    cin >> V >> E;
    // inicializando var. para o caso de teste
    for(int v = 0; v < V; v++)	adj[v].clear();
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    bfs(0);

    return 0;
}