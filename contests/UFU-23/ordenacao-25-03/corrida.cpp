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

set<char> has;

int main() {

    string s; cin >> s;
    for(auto x : s) has.insert(x);
    for(char c = 'a'; c<='z'; c++){
        if(!has.count(c)){
            cout << c << '\n';
            break;
        }
    }

    return 0;
}
