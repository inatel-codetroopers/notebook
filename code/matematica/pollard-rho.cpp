// Retorna um fator primo de N, util para fatorizacao quando N for
// grande.

ll mult(ll a, ll b, ll mod) {
	// return (a * b) % mod com mod mt grande
	long long result = 0;
	while(b) {
		if(b & 1)
			result = (result + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return result;
}

ll f(ll x, ll c, ll mod) {
	return (mult(x, x, mod) + c) % mod;
}

// recomendo chamar rho(n, n, 1)
ll rho(ll n, ll x0, ll c) {
	if(n == 1) return 0;
	ll x = x0, y = x0, g = 1;
	int cnt = 0, lim = 1e5;
	while(g == 1 && ++cnt < lim) {
		x = f(x, c, n);
		y = f(y, c, n);
		y = f(y, c, n);
		g = __gcd(abs(x - y), n);
	}
	if(cnt == lim) return n;
	return g;
}

