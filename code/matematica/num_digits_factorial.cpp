int NumOfDigitsInFactorial(int N, int B){
	double logFatN = 0;
	for (int i = 1; i <= N; i++)
		logFatN += log((double)i);
	int nd = floor(logFatN / log((double)B)) + 1;
	return nd;
}