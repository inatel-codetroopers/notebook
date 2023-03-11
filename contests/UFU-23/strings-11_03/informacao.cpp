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

    string s, t;
    while(cin >> s >> t){
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if(s[i] == t[j]) i++;
            j++;
        }

        if (i == s.size()) cout << "sim\n";
        else cout << "nao\n";
    }

    return 0;
}
