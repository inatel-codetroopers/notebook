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

map<char, int> freq;
set<ii> ans;

int main() {

    ll n; cin >> n;
    string s; getline(cin, s);
    rep(i, 0, n){
        getline(cin, s);
        for(auto c : s){
            char uc = toupper(c);
            if(uc >= 'A' && uc <= 'Z'){
                freq[uc]++;
            }
        }
    }

    for(auto x : freq){
        ans.insert(ii(-x.second, x.first));
    }

    for(auto x : ans){
        cout << x.second << " " << -x.first << '\n';
    }
	
    return 0;
}
