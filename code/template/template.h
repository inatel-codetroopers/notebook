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