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

set<string> especiais;

string tolower(string s){
    rep(i, 0, s.size()){
        s[i] = tolower(s[i]);
    }
    return s;
}

bool isEspecial(string s){
    return especiais.count(tolower(s));
}

void addEspecial(string s){
    especiais.insert(tolower(s));
}

bool isDelimiter(char c){
    return c == ' ' || c == ':' || c == '-';
}

vector<string> split(string s){
    s.push_back(' ');
    vector<string> ret; string aux;
    rep(i, 0, s.size()){
        if(isDelimiter(s[i])){
            if(aux.size()){
                ret.push_back(aux);
            }
            aux.clear();
        }else{
            aux.push_back(s[i]);
        }
    }

    return ret;
}

int main() {

    int e, f; cin >> e >> f;
    cin.ignore();

    string s;
    rep(i, 0, e){
        cin >> s;
        addEspecial(s);
    }

    cin.ignore();
    rep(i, 0, f){
        getline(cin, s);
        vector<string> ss = split(s);

        string ans;
        bool isFirst = true;
        for(auto s : ss){
            if(isEspecial(s)){
                if(!isFirst)
                    ans.push_back((char)tolower(s[0]));
            }else{
                ans.push_back((char)toupper(s[0]));
            }
            isFirst = false;
        }
        cout << ans << '\n';
    }


    return 0;
}
