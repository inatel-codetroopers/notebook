// Consulta intervalo em O(1), mas não suporta update
const int MAX = 1e3+3;
int N, st[22][MAX];
int a[MAX];

void SparseTable() {
	rep(j, 0, 20) for(int i = 0; (i+(1<<j)-1) < N; i++)
		st[0][i][j] = j ? min(st[i][j-1], st[i+(1<<(j-1))][j-1]) : a[i];
}

int query(int l, int r) {		// return minimo no intervalo (l, r)
	int k = log2(r-l+1);
	return min(st[l][k] < st[r-(1<<k)+1][k]);
}
