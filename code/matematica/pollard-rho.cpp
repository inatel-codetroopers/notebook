// Retorna um fator primo de N, util para fatorizacao quando N for grande.
ll pollard_r, pollard_n;
ll f(ll val){return (val*val+pollard_r)%pollard_n; }
ll myabs(ll a){return a >= 0 ? a:-a; }
ll pollard(ll n){
	srand(unsigned(time(0)));
	pollard_n = n;
	long long d = 1;
	do {
		d = 1;
		pollard_r = rand()%n;
		long long x = 2, y = 2;
		while(d == 1)
			x = f(x), y = f(f(y)), d = __gcd(myabs(x-y), n);
	} while(d == n);
	return d;
}