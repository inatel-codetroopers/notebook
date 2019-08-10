// Calcula o maior divisor comum entre A e B
ll A, B;
cin >> A >> B;
cout << __gcd(A, B);

// Calcula o menor multiplo comum entre A e B
ll lcm(ll A, ll B){
	if (A and B) return abs(A)/__gcd(A, B)*abs(B);
	else return abs(A | B);
}