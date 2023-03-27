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

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

typedef tree<int, // tipo da variavel
        null_type,
        less<int>, // funcao de comparacao(greater, less_equal,
        rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

vector<int> ans;
ordered_set lt;

int main() {

    int n; cin >> n;
    rep(i, 1, n+1){
        lt.insert(i);
    }

    int pos = 0;
    while(lt.size() > 0){
        pos = (pos + 1)%lt.size();
        // cout << pos << " " << lt.size() << "\n";
        int aux = *(lt.find_by_order(pos));
        ans.push_back(aux);
        lt.erase(aux);
    }

    for(auto x : ans) cout << x << " "; cout << '\n';

    return 0;
}
