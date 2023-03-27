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

    map<int, int> freqr;
    int n;
    while(cin >> n){
        if(n==-1) break;
        freqr[n]++;
    }

    for(auto x : freqr){
        cout << x.first << " " << x.second << '\n';
    }

    return 0;
}
