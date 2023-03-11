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

    char c; string s;
    while(cin >> c >> s){
        string t;
        bool hasNonZero = false;
        for(auto cs : s){
            if(cs == c) continue;
            if(cs == '0' && hasNonZero == false) continue;
            t.push_back(cs);
            hasNonZero = true;
        }
        if(t.size()==0) t = "0";
        cout << t << '\n';
    }

    return 0;
}
