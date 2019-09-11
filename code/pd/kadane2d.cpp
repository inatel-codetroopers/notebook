/*Maior soma de uma sub-matriz a partir de valores positivos.
 * [x1,y1]=upper-left, [x2,y2]=bottom-right*/
int L, C, pd[MAX_L], mat[MAX_L][MAX_C];
int x1, y1, x2, y2;
int Kadane2D() {
  int ret = 0, aux;
  rep(left, 0, C) {
    rep(i, 0, L) pd[i] = 0;
    rep(right, left, C) {
      rep(i, 0, L) pd[i] += mat[i][right];
      int sum = aux = 0;
      rep(i, 0, L) { // Kadane1D
        sum += pd[i];
        if (sum > ret)
          ret = sum, x1 = aux, y1 = left, x2 = i, y2 = right;
        if (sum < 0)
          sum = 0, aux = i + 1;
      }
    }
  }
  return ret;
}