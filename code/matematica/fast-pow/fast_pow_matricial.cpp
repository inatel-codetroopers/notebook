
vector<vector<int>> mult(vector<vector<int>> &a, vector<vector<int>> &b) {
    vector<vector<int>> res(4, vector<int>(4, 0));
    rep(i, 0, 4) rep(j, 0, 4) rep(k, 0, 4)
        res[i][j] = (res[i][j]+1LL*a[i][k]*b[k][j])%MOD;
    return res;
}

int exp(vector<vector<int>> b, ll e) {
    vector<vector<int>> res(4, vector<int>(4, 0));
    rep(i, 0, 4) res[i][i] = 1;
    while(e) {
        if(e&1LL) res = mult(res, b);
        b = mult(b, b); e >>= 1;
    }
    // Return depende da questao, geralmente eh a soma da primeira linha
    return (2LL*res[0][0]+res[0][1]+res[0][2]+res[0][3])%MOD;
}
