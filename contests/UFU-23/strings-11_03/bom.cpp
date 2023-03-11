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
    cin >> c; cin.ignore();
    getline(cin, s);
	
    int total = 0;
    for(auto x : s){
        if(tolower(x) == tolower(c))
            total++;
    }

    cout << total << '\n';

    return 0;
}
