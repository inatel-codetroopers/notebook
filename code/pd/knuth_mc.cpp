int N, B, C, yep, save[MAXN][MAXN], sav[MAXN];
ll n[MAXN], mc[MAXN][MAXN], se[MAXN], sd[MAXN], pd[MAXN][MAXN];

ll solve(int i, int k) {
  if (i == N)
    return 0;
  if (k == 1)
    return pd[i][k] = mc[i][N - 1];
  if (pd[i][k] != -1)
    return pd[i][k];

  ll ret = LINF;
  int ini = i, fim = N - k + 1, best = -1;
  if (i && save[i - 1][k])
    ini = save[i - 1][k];
  if (save[i][k - 1])
    fim = save[i][k - 1] + 1;

  rep(l, ini, fim) {
    ll aux = solve(l + 1, k - 1) + mc[i][l];
    if (ret > aux) {
      best = l;
      ret = aux;
    }
  }
  save[i][k] = best;
  return pd[i][k] = ret;
}

int main() {
  rep(i, 0, N) scanf("%lld", &n[i]);

  se[0] = n[0];
  rep(i, 1, N) se[i] = se[i - 1] + n[i];

  sd[N - 1] = n[N - 1];
  for (int i = N - 2; i >= 0; i--)
    sd[i] = sd[i + 1] + n[i];

  rep(i, 1, N) pd[0][i] = pd[0][i - 1] + se[i - 1];
  for (int i = N - 2; i >= 0; i--)
    pd[N - 1][i] = pd[N - 1][i + 1] + sd[i + 1];

  rep(i, 1, N) {
    rep(j, i + 1, N) pd[i][j] = pd[i - 1][j] - n[i - 1] * (j - i + 1);
  }
  for (int i = N - 2; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--)
      pd[i][j] = pd[i + 1][j] - n[i + 1] * (i - j + 1);
  }

  rep(i, 0, N) {
    if (pd[i][i + 1] < pd[i + 1][i])
      mc[i][i + 1] = pd[i][i + 1], save[i][i + 1] = i + 1;
    else
      mc[i][i + 1] = pd[i + 1][i], save[i][i + 1] = i;
    rep(j, i + 2, N) {
      int ini = save[i][j - 1];
      mc[i][j] = pd[i][ini] + pd[j][ini], save[i][j] = ini;
      rep(k, ini + 1, j + 1) {
        ll a = pd[i][k] + pd[j][k];
        if (mc[i][j] <= a)
          break;
        mc[i][j] = a;
        save[i][j] = k;
      }
    }
    rep(j, 0, N + 1) { pd[i][j] = -1, save[i][j] = 0; }
  }

  rep(j, 0, N + 1) pd[N][j] = -1, save[N][j] = 0;

  solve();

  return 0;
}
