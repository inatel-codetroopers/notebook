#include <bits/stdc++.h>
using namespace std;

/**
Calcula exponenciacao de matrizes de forma eficiente.
@param ordem - a ordem da matriz mat
@param mat - a matriz a ser exponenciada
@param E - expoente a ser utilizado
@return ans - resultado da matriz mat elevada a E
**/
int ordem = 2; 
ll mod = 1e9 + 7;

ll mat[ordem][ordem], ans[ordem][ordem], tmp[ordem][ordem];

// multiplica as matrizes a[][] e b[][] e armazena em a[][] o
// resultado

void mult(ll a[][ordem], ll b[][ordem]) {
  ll aux = 0;
  rep(i, 0, ordem) rep(j, 0, ordem) {
    tmp[i][j] = 0;
    rep(k, 0, ordem)
    {
      aux = a[i][k] * b[k][j];
      if (aux >= mod)
        aux %= mod;
      tmp[i][j] += aux;
      if (tmp[i][j] >= mod)
        tmp[i][j] %= mod;
    }
  }
  memcpy(a, tmp, sizeof tmp);
}


// Calcula mat^n
// resultado fica em ans[][]


typedef struct 
{
  vector<vector<ll> > m;
  

} matrix_t;


void fastExp(ll E) {
  rep(i, 0, ordem)
    rep(j, 0, ordem)
      ans[i][j] = (i == j);
  while (E) {
    if (E & 1) mult(ans, mat);
    E >>= 1;
    mult(mat, mat);
  }
}

int main()
{

}