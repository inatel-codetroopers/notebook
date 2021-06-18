typedef __uint128_t u128;

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = fastpow(a, d, n);
    if(x == 1 || x == n - 1)
        return false;
    for(int r = 1; r < s; r++) {
        x = (u128)x * x % n;  // cuidado na multiplicação
        if(x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(ll n) {
    if(n < 2) return false;
    int r = 0;
    ll d = n - 1;
    while((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if(n == a)
            return true;
        if(check_composite(n, a, d, r))
            return false;
    }
    return true;
}
