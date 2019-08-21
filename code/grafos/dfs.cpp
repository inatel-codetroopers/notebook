// dfs (exemplo: detectando ciclos)
// Complexidade O(V+E)
#define MAXV (112345)
 
int V, E; // #Vertices, #Arestas
vector<int> adj[MAXV];

bool ciclo = false;
int vis[MAXV];

void dfs(int u){
    vis[u] = 1;
    for (auto v : adj[u]){
        if (vis[v] == 1) ciclo = true;
        else if (vis[v] == 0) dfs(v);
    }
    vis[u] = 2;
}

int main(){
    cin >> V >> E;
    // inicializando var. para o caso de teste
    for(int v = 0; v < V; v++) adj[v].clear();
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    // Exemplo ciclo (dfs)
    ciclo = false;
    memset(vis, 0, sizeof(vis));
    for(int v=0; v<V; v++) if(!vis[v]) dfs(v);
    cout << "Tem ciclo = " << ciclo << endl;

    return 0;
}