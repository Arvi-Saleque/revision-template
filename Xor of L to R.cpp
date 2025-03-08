ll get(ll x, int i) {
    ll cycle = 1LL << (i + 1);   // cycle length
    ll fullCycles = (x + 1) / cycle;
    ll count = fullCycles * (1LL << i); 
    ll remainder = (x + 1) % cycle;
    count += max(0LL, remainder - (1LL << i));
    return count;
}
// how many bits on of ith bit from l to r
ll f(ll l, ll r, ll i) {
    return get(r, i) - get(l - 1, i);
}
ll F(ll n) {
    switch(n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
}
ll XorFromLtoR(ll l, ll r) {
    /*ll ans = 0;
    for(int i = 0; i < 60; i++) {
        if(f(l, r, i) & 1) ans |= (1LL << i);
    }
    return ans; */   
    return F(r) ^ (l == 0 ? 0 : F(l - 1));
}