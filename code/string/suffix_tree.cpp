const int MAX = ; // somatorio de caracteres
const int NS = ;  // quantidade de strings
int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[2*MAX];
int cnt = 30;
 
struct node {
	int p, suf;
	int l, r, si;
	map<int, int> f;
	node(int L = 0, int R = -1, int S = 0, int P = 0) {
		l = L; r = R; si = S; p = P; suf = 0;
	}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]-'a'; }
	inline int& operator()(int c) { return f[c]; }
} t[2*MAX];
 
void init() {
	si = -1; en = 1;
	ns = lst = 0;
	t[0] = node();
}

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L, R, S, P);
	return en++;
}

void add_string(string s) {
	s += '$';
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int c, i = 0; const int n = s.size();
	for(int j = 0; j < n; j++) {
		c = (s[j] != '$') ? s[j]-'a' : cnt++;
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn](c))
				cn = t[cn](c), cd = 0;
			if(cd < t[cn].len() && t[cn][cd] == c) {
				cd++;
				if(j < (int)s.size() - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](c) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](c) = new_node(j, n - 1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn? j - cd : i + 1;
				cn = t[cn].suf;
				while(g < j && g + t[t[cn](S[si][g]-'a')].len() <= j)
					cn = t[cn](S[si][g]-'a'), g += t[cn].len();
				if(g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]-'a'), cd = j - g;
			}
		}
	}
}
