// No main, chamar quicksort(array, 0, tam-1);
int partition(int s[], int l, int h) {
  int i, p, firsthigh;
  p = h;
  firsthigh = l;
  for (i = l; i < h; i++)
    if (s[i] < s[p]) {
      swap(s[i], s[firsthigh]);
      firsthigh++;
    }
  swap(s[i], s[firsthigh]);
  return firsthigh;
}
void quicksort(int s[], int l, int h) {
  int p;
  if ((h - l) > 0) {
    p = partition(s, l, h);
    quicksort(s, l, p - 1);
    quicksort(s, p + 1, h);
  }
}