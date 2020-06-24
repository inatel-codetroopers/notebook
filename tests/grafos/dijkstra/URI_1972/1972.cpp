#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)

typedef long long ll;
typedef pair<int, int> ii;

const int INF = 0x3f3f3f3f;

#define MAXN 500 + 10
typedef int cost_t; // tipo de variavel para o custo da aresta

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int R, C;
char grid[MAXN][MAXN];
cost_t dist[MAXN][MAXN];

bool inside(int i, int j) {
  return (i >= 0 && i < R && j >= 0 && j < C);
}

bool is_valid(int i, int j) {
  return inside(i, j) && grid[i][j] != '#';
}

void dijkstra(int src_x, int src_y) {
  memset(dist, INF, sizeof dist);

  priority_queue<pair<cost_t, ii> > PQ;

  dist[src_x][src_y] = 0;
  PQ.push(make_pair(0, make_pair(src_x, src_y)));

  while (!PQ.empty()) {
    pair<cost_t, ii> top = PQ.top();
    PQ.pop();

    int x = top.second.first;
    int y = top.second.second;

    if (dist[x][y] != -top.first)
      continue; // (x,y) já foi processado

    for (int direcao = 0; direcao < 4; direcao++) {
      // (a,b) são um dos 4 vizinhos de (x,y)
      int a = x + dx[direcao];
      int b = y + dy[direcao];
      if (is_valid(a, b)) {
        cost_t cost_xy_to_ab = 0;

        if (grid[a][b] == '.' || grid[a][b] == 'E')
          cost_xy_to_ab = 0;
        else
          cost_xy_to_ab = (grid[a][b] - '0'); // convert ASCII to digit

        if (dist[x][y] + cost_xy_to_ab < dist[a][b])
        {
          dist[a][b] = dist[x][y] + cost_xy_to_ab;
          PQ.push(make_pair(-dist[a][b], ii(a, b)));
        }
      }
    } // for
  } // while
  return;
}

int main() {
  while (scanf("%d %d\n", &R, &C) == 2) {
    int ini_x, ini_y;
    int fim_x, fim_y;
    rep(i, 0, R) rep(j, 0, C) {
      cin >> grid[i][j];
      if (grid[i][j] == 'H') {
        ini_x = i;
        ini_y = j;
      }
      if (grid[i][j] == 'E') {
        fim_x = i;
        fim_y = j;
      }
    }

    dijkstra(ini_x, ini_y);

    if (dist[fim_x][fim_y] == INF)
      cout << "ARTSKJID" << endl;
    else
      cout << dist[fim_x][fim_y] << endl;
  }
  return 0;
}
