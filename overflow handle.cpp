How many numbers are divisible by n and m in [l, r]?

void solve()
{
    ll n,m,l,r;
    cin >> n >> m >> l >> r;
    if(n < m) swap(n,m);
    ll GCD = __gcd(n,m);
    if( n/GCD > r/m) cout << 0 << "\n";
    else
    {
        n /= GCD;
        ll LCM = n * m;
        cout << (r/LCM) - ((l-1)/LCM)  << "\n";
    }
} 
