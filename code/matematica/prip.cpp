int priP(int N, int K, int P) {
	double x = K * log10(N);
	return pow(10, x-int(x)) * pow(10, P-1);
}
