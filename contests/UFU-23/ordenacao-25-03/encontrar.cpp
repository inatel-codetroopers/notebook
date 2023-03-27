#include <bits/stdc++.h>

// LIFE IS NOT A PROBLEM TO BE SOLVED

using namespace std;
 
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(S) (S).begin(), (S).end()
#define pb push_back
#define S second
#define F first

typedef long long ll;
typedef pair<int, char> ii;

const int MAXN = 255;
const ll INF = 1LL << 60;


int main() {

   string a, b; cin >> a >> b;
   sort(all(a)); sort(all(b));
   cout << (a == b ? 1 : 0) << '\n';

    return 0;
}
