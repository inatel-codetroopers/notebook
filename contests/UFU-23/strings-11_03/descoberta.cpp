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

    int n;
    while (cin >> n and n){
        string s; set<string> st;
        rep(i, 0, n){
            cin >> s;
            sort(all(s));
            st.insert(s);
        }
        cout << st.size() << '\n';
    }

    return 0;
}
