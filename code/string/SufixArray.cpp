vector<int> suffix_array(char s[]){
    int n = strlen(s), N = n + 256;
    vector<int> sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++){
        vector<int> nsa(sa), nra(n), cnt(N);
        for(int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n;
        for(int i = 0; i < n; i++) cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
 
        int r = 0;
        for(int i = 1; i < n; i++){
            if(ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if(ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        ra = nra;
    }
    return sa;
}
 
vector<int> kasai(char s[], vector<int> sa){
    int n = strlen(s), k = 0;
    vector<int> ra(n), lcp(n);
    for(int i = 0; i < n; i++) ra[sa[i]] = i;
    for(int i = 0; i < n; i++){
        if(k) k--;
        if(ra[i] == n - 1) {k = 0; continue;}
        int j = sa[ra[i] + 1];
        while(k < n && s[(i + k) % n] == s[(j + k) % n]) k++;
        lcp[ra[i]] = k;
        if(ra[(sa[ra[i]] + 1) % n] > ra[(sa[ra[j]] + 1) % n]) k = 0;
    }
    return lcp;
}

bool isValid(char c){
	return c>='a' && c<='z';
}
vector <int> ranks(char s[], vector <int> sa, vector <int> lcp){
	int n = strlen(s), k = 0;
	vector <int> rk(n);
	for(int i=0; i<n; i++){
		if(!isValid(s[i])){ k++; rk[i] = -1; }
		else{ rk[i] = k; }
	}
	return rk;
}

vector <int> sizes(char s[], vector <int> sa, vector <int> lcp){
	int n = strlen(s), len = 0;
	vector <int> sz(n);
	for(int i=n-1; i>=0; i--){
		if(!isValid(s[i])){ len = 0; sz[i] = -1; }
		else{ len++; sz[i] = len; }
	}
	return sz;
}

void PrintAll(char s[], vector <int> sa, vector <int> lcp, vector <int> rk, vector <int> sz) {
	int n = strlen(s);
	printf("RK\tSZ\tSA\ttam\tLCP\tSuffix\n");
	rep(i, 0, n){
		printf("%2d\t%2d\t%2d\t%2d\t%2d\t%s\n", rk[sa[i]], sz[sa[i]], sa[i], n-sa[i], lcp[i], s+sa[i]);
	}
}

int main(){
	
	char s[] = "macarrao#batata$brigadeiro";
	vector <int> sa = suffix_array(s);
	vector <int> lcp = kasai(s, sa);
	vector <int> rk = ranks(s, sa, lcp);
	vector <int> sz = sizes(s, sa, lcp);
	PrintAll(s, sa, lcp, rk, sz);
	
	return 0;
}