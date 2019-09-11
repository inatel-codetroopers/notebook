#define MAX_V 2003
#define MAX_E 2 * 3003
// Inicializar MAX_V e MAX_E corretamente. Chamar init(_V) com a qtde
// de vertices (indexado em 0) mesmo que seja bidirecional. Adicionar
// as arestas duas vezes no main(). Complexiade (rapido)

typedef int cap_type;
typedef long long cost_type;
const cost_type inf = LLONG_MAX;

int V, E, pre[MAX_V], last[MAX_V], to[MAX_E], nex[MAX_E];
bool visited[MAX_V];
cap_type flowVal, cap[MAX_E];
cost_type flowCost, cost[MAX_E], dist[MAX_V], pot[MAX_V];

void init(int _V) {
  memset(last, -1, sizeof(last));
  V = _V;
  E = 0;
}

void add_edge(int u, int v, cap_type _cap, cost_type _cost) {
  to[E] = v, cap[E] = _cap;
  cost[E] = _cost, nex[E] = last[u];
  last[u] = E++;
  to[E] = u, cap[E] = 0;
  cost[E] = -_cost, nex[E] = last[v];
  last[v] = E++;
}

// only if there is initial negative cycle
void BellmanFord(int s, int t) {
  bool stop = false;
  for (int i = 0; i < V; ++i)
    dist[i] = inf;
  dist[s] = 0;

  for (int i = 1; i <= V && !stop; ++i) {
    stop = true;

    for (int j = 0; j < E; ++j) {
      int u = to[j ^ 1], v = to[j];

      if (cap[j] > 0 && dist[u] != inf && dist[u] + cost[j] < dist[v]) {
        stop = false;
        dist[v] = dist[u] + cost[j];
      }
    }
  }

  for (int i = 0; i < V; ++i)
    if (dist[i] != inf)
      pot[i] = dist[i];
}

void mcmf(int s, int t) {
  flowVal = flowCost = 0;
  memset(pot, 0, sizeof(pot));

  BellmanFord(s, t);

  while (true) {
    memset(pre, -1, sizeof(pre));
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < V; ++i)
      dist[i] = inf;

    priority_queue<pair<cost_type, int>> Q;
    Q.push(make_pair(0, s));
    dist[s] = pre[s] = 0;

    while (!Q.empty()) {
      int aux = Q.top().second;
      Q.pop();

      if (visited[aux])
        continue;
      visited[aux] = true;

      for (int e = last[aux]; e != -1; e = nex[e]) {
        if (cap[e] <= 0)
          continue;
        cost_type new_dist =
            dist[aux] + cost[e] + pot[aux] - pot[to[e]];
        if (new_dist < dist[to[e]]) {
          dist[to[e]] = new_dist;
          pre[to[e]] = e;
          Q.push(make_pair(-new_dist, to[e]));
        }
      }
    }

    if (pre[t] == -1)
      break;

    cap_type f = cap[pre[t]];
    for (int i = t; i != s; i = to[pre[i] ^ 1])
      f = min(f, cap[pre[i]]);
    for (int i = t; i != s; i = to[pre[i] ^ 1]) {
      cap[pre[i]] -= f;
      cap[pre[i] ^ 1] += f;
    }

    flowVal += f;
    flowCost += f * (dist[t] - pot[s] + pot[t]);

    for (int i = 0; i < V; ++i)
      if (pre[i] != -1)
        pot[i] += dist[i];
  }
}

int main() { return 0; }