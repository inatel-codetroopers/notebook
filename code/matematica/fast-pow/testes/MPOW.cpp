#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define pb push_back
#define mp make_pair
#define debug(x) cout<<__LINE__<<": "<<#x<<" = "<<x<<endl;
#define debug2(x, y) cout<<__LINE__<<": "<<#x<<" = "<<x<<\
                                     "  "<<#y<<" = "<<y<<endl;
#define all(c) (c).begin(), (c).end()
#define F first
#define S second
#define UNIQUE(c) \
    sort(all(c)); \
    (c).resize(unique(all(c))-c.begin());

#define PI 3.1415926535897932384626433832795028841971

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;
const double EPS = 1e-9;

inline int cmp(double x, double y = 0, double tol = EPS){
  return ((x <= y+tol) ? (x+tol < y) ? -1:0:1);
}




/**
Calcula exponenciacao de matrizes de forma eficiente.
@param ordem - a ordem da matriz mat
@param mat - a matriz a ser exponenciada
@param E - expoente a ser utilizado
@return ans - resultado da matriz mat elevada a E
**/

#define MAX (51) // Max size of square matrix
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


int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    matrix_t M;
    int expoente;
    scanf("%d %d", &M.size, &expoente);
    rep(i,0,M.size) rep(j,0,M.size)
      scanf("%lld", &M.m[i][j]);

    M = fastpow(M, expoente, 1000000007LL);

    rep(i,0,M.size){
      rep(j,0,M.size){
        if(j) printf(" ");
        printf("%lld", M.m[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}

