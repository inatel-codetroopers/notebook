// Euclides Estendido
ll gcd(ll A, ll B, ll &X, ll &Y) {
	if(B == 0) {
		X = 1; Y = 0;
		return A;
	}
	ll x1, y1;
	ll G = gcd(B, A % B, x1, y1);
	X = y1; Y = x1 - (A / B) * y1;
	return G;
}

// Acha a primeira vez que dois eventos ocorrem ao mesmo tempo
// Os eventos acontecem a cada:
// A * T1 + Z1 e B * T2 + Z2
pair<ll, ll> solve(ll A, ll B, ll Z1, ll Z2) {
	if(Z2 > Z1) swap(A, B), swap(Z1, Z2);
	ll X, Y, ans = 0;
	ll G = gcd(A, B, X, Y), C = Z2-Z1;
	if(C%G) return mk(-1LL, -1LL);	// impossivel
	C /= G; X *= C; Y *= C;
	if(X >= 0) {
		ll K = (X * G) / B;
		ans = A * (X - K * (B / G)) + Z1;
	} else {
		ll K = (-X * G + B - 1) / B;
		ans = A * (X + K * (B / G)) + Z1;
	}
	// retorna um par na forma (A, Z)
	// A -> novo tamanho do ciclo
	// Z -> primeira vez que acontece
	return mk(A * (B / G), ans);
}

// Anotação importante, Há duas formas de alterar as soluções:
// (1) -> X = X + K * (B / G) e Y = Y - K * (A / G)
// (2) -> X = X - K * (B / G) e Y = Y + K * (A / G)
