// Longest Commom Prefix between S[i..] and S[j..]
int lcp(int i, int j, int tam) {
  int lo = 0, hi = tam, ans;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (my_hash(i, i + mid - 1) == my_hash(j, j + mid - 1)) {
      ans = mid;
      lo = mid + 1;
    } else
      hi = mid - 1;
  }
  return ans;
}