// Permite encontrar um hash de uma substring de S. precompute O(n),
// my_hash O(1)
const ll mod = 1e9 + 7; // modulo do hash
const ll x = 31;        // num. primo > que o maior caracter de S.
ll V(char c) { return c - 'a'; }
 
struct hashing {
	string s;
	vector<ll> X, H;
 
	hashing(string _s) {
		s = _s;
		X.resize(s.size() + 1);
		H.resize(s.size());
		precompute();
	}
 
	void precompute() {
		X[0] = 1, H[0] = V(s[0]);
		rep(i, 1, s.size()) {
			X[i] = (X[i - 1] * x) % mod;
			H[i] = ((H[i - 1] * x) % mod + V(s[i])) % mod;
		}	X[s.size()] = (X[s.size() - 1] * x) % mod;
	}
 
	ll hash(int i, int j) {
		ll ret = H[j];
		if (!i) return ret;
		return ((ret - (H[i - 1] * X[j - i + 1]) % mod) + mod) % mod;
	}
};

