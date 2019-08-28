/**
 * fastpow() realiza exponenciacao rapida de matrizes
 * #param matrix_t M - matriz a ser elevada
 * #param ll expo - expoente
 * #param ll mod - o resultado sera calculado modulo este valor
 * #return - o resultado de (M ^ expo) % mod
 * #complexidade - O(size^3 * log(expo))
**/

#define MAX (ChangeMe) // Max size of square matrix
struct matrix_t{
  ll m[MAX][MAX];
  int size;
  matrix_t multiply(const matrix_t q, ll mod){
    matrix_t ret;
    ret.size = size;
    rep(i,0,size) rep(j,0,size){
      ret.m[i][j] = 0;
      rep(k,0,size){
        ret.m[i][j] = (ret.m[i][j] + (m[i][k] * q.m[k][j]) % mod) % mod;
      }
    }
    return ret;
  }
};


matrix_t fastpow(matrix_t M, ll expo, ll mod){
  matrix_t ret;
  ret.size = M.size;
  rep(i,0,ret.size)
    rep(j,0,ret.size)
      ret.m[i][j] = (i == j); // init Identity matrix

  while (expo){
    if(expo & 1)
      ret = ret.multiply(M, mod);
    M = M.multiply(M, mod);
    expo >>= 1;
  }
  return ret;
}