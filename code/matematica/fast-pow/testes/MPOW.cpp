#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define pb push_back
#define mp make_pair
#define debug(x) cout << __LINE__ << ": " << #x << " = " << x << endl;
#define debug2(x, y)                                                   \
  cout << __LINE__ << ": " << #x << " = " << x << "  " << #y << " = "  \
       << y << endl;
#define all(c) (c).begin(), (c).end()
#define F first
#define S second
#define UNIQUE(c)                                                      \
  sort(all(c));                                                        \
  (c).resize(unique(all(c)) - c.begin());

#define PI 3.1415926535897932384626433832795028841971

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;
const double EPS = 1e-9;

inline int cmp(double x, double y = 0, double tol = EPS) {
  return ((x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1);
}

/**
Calcula exponenciacao de matrizes de forma eficiente.
@param ordem - a ordem da matriz mat
@param mat - a matriz a ser exponenciada
@param E - expoente a ser utilizado
@return ans - resultado da matriz mat elevada a E
**/

#define MAX (51) // Max sz of square matrix

struct matrix_t {
  ll m[MAX][MAX];
  int sz;
  matrix_t(int _sz) {
    memset(m, 0, sizeof(m));
    sz = _sz;
  }
  matrix_t multiply(const matrix_t other, ll mod) {
    matrix_t ret(other.sz);
    rep(i, 0, sz) rep(j, 0, sz) {
      ret.m[i][j] = 0;
      rep(k, 0, sz) ret.m[i][j] =
          (ret.m[i][j] + (m[i][k] * other.m[k][j]) % mod) % mod;
    }
    return ret;
  }
};

matrix_t fastpow(matrix_t M, ll expo, ll mod) {
  matrix_t ret(M.sz);
  // Identity matrix
  rep(i, 0, ret.sz) rep(j, 0, ret.sz) ret.m[i][j] = (i == j);

  while (expo) {
    if (expo & 1)
      ret = ret.multiply(M, mod);
    M = M.multiply(M, mod);
    expo >>= 1;
  }
  return ret;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int size;
    int expoente;
    scanf("%d %d", &size, &expoente);

    matrix_t M(size);
    rep(i, 0, M.sz) rep(j, 0, M.sz) scanf("%lld", &M.m[i][j]);

    M = fastpow(M, expoente, 1000000007LL);

    rep(i, 0, M.sz) {
      rep(j, 0, M.sz) {
        if (j)
          printf(" ");
        printf("%lld", M.m[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}