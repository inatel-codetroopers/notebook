const int MAX = 1e7;
vector<int> primes;
vector<int> num;
int lp[MAX+1];

void crivo() {
	for(int i = 2; i <= MAX; i++) {
	    if(lp[i] == 0) {
	        lp[i] = i;
	        primes.pb(i);
	    }
	    for (int j = 0; j < (int)primes.size() && primes[j] <= lp[i]
			&& i * primes[j] <= MAX; j++)
	        lp[i * primes[j]] = primes[j];
	}
}
