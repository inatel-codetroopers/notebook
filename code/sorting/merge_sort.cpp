int b[MAXN];  // auxliar array
void merge_sort(int s[], int l, int h) {
  if ((h - l) > 0) {
    int p = (l + h) / 2;
    merge_sort(s, l, p);
    merge_sort(s, p + 1, h);
    merge(s, l, p, h);
  }
}
void merge(int s[], int l, int p, int h) {
  int i, j, k;
  for (i = l; i <= h; i++) b[i] = s[i];

  k = i = l;
  j = p + 1;
  while (i <= p && j <= h) {
    if (b[i] < b[j])
      s[k++] = b[i++];
    else
      s[k++] = b[j++];
  }
  if (i > p)
    while (j <= h) s[k++] = b[j++];
  if (j > h)
    while (i <= p) s[k++] = b[i++];
}