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

int main() {

    int t; cin >> t;
    while(t--){
        int n; string s;
        cin >> n >> s;
        for(auto c : s){
            cout << (char)( (c-'A' + n + 26)%26 + 'A' );
        }
        cout << '\n';
    }

    return 0;
}
