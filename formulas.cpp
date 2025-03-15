// sum of from l to r
ll f(ll l, ll r) {
    ll val = (l + r) * (r - l + 1) / 2;
    return val;
}

gcd(a, b) = gcd(a, b - a)
so gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)
