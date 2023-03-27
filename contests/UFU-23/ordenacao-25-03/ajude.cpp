#include <bits/stdc++.h>

// LIFE IS NOT A PROBLEM TO BE SOLVED

using namespace std;
 
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(S) (S).begin(), (S).end()
#define pb push_back
#define S second
#define F first

typedef long long ll;
typedef pair<int, int> ii;

const int MAXN = 255;
const ll INF = 1LL << 60;

set <ll> st;

int main() {

    ll n;
    while(cin >> n){
        if(n&1) st.insert(n);
    }

    for(auto x: st){
        cout << x << '\n';
    }
	
    return 0;
}
