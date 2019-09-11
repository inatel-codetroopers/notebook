//[IME] 0-1 Knapsack, v-valores, w-pesos, Cap-capacidade
int mochila01(vector<int> v, vector<int> w, int Cap) {
  int n = v.size();
  int dp[n + 1][Cap + 1];
  for (int i = 0; i <= n; i++)
    dp[i][0] = 0;
  for (int j = 0; j <= Cap; j++)
    dp[0][j] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= Cap; j++) {
      if (w[i - 1] > j)
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] =
            max(dp[i - 1][j], v[i - 1] + dp[i - 1][j - w[i - 1]]);
    }
  return dp[n][Cap];
}