// https://atcoder.jp/contests/abc151/tasks/abc151_e?lang=en

// fix a value
// and check how much smaller/greated value present 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
int f[N], invf[N];
ll power(ll a, ll b) {
    ll ans = 1;
    bool f = 1;
    while(b) {
        if(b & 1) {
            ans *= a;
            if(ans >= mod) {
                ans %= mod;
                f = 1;
            }
        }
        a *= a;
        if(a >= mod) {
            a %= mod;
            f = 1;
        }
        b >>= 1;
    }
    return (ans + (mod * f)) % mod;
}
void pre() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = 1LL * i * f[i - 1] % mod;
    }
    invf[N - 1] = power(f[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--) {
        invf[i] = 1LL * invf[i + 1] * (i + 1) % mod;
    }
}
int nCr(int n, int r) {
    if (n < r or n <= 0) return 0;
    return 1LL * f[n] * invf[r] % mod * invf[n - r] % mod;
}
void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        mp[x]++;
    }

    if(k == 1) {
        cout << 0 << "\n";
        return;
    }

    vector<pair<int, int>> vpp;
    for(auto [x, y] : mp) {
        vpp.push_back({x, y});
    }
    // as max
    ll ans = 0, cnt = 0;
    for(int i = 0; i < vpp.size(); i++) {
        auto [x, y] = vpp[i];
        for(int c = 1; c <= min(y, k - 1); c++) {
            ll val = (1LL * nCr(y, c) * nCr(cnt, k - c)) % mod;
            val = (1LL * val * x) % mod;
            ans = (ans + val) % mod;
        }
        //cout << x << " " << y << " " << ans << "\n";
        cnt += y;
    }
    cnt = n;
    for(int i = 0; i < vpp.size(); i++) {
        auto [x, y] = vpp[i];
        cnt -= y;
        for(int c = 1; c <= min(y, k - 1); c++) {
            ll val = (1LL * nCr(y, c) * nCr(cnt, k - c)) % mod;
            val = (1LL * val * x) % mod;
            ans = (ans - val + mod) % mod;
        }
    }
    cout << ans << "\n";
}   
int main() {
    pre();
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        // /cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}

// https://atcoder.jp/contests/abc167/tasks/abc167_e?lang=en

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 2e5 + 2, mod = 998244353;
int f[N], invf[N];
ll power(ll a, ll b) {
    ll ans = 1;
    bool f = 1;
    while(b) {
        if(b & 1) {
            ans *= a;
            if(ans >= mod) {
                ans %= mod;
                f = 1;
            }
        }
        a *= a;
        if(a >= mod) {
            a %= mod;
            f = 1;
        }
        b >>= 1;
    }
    return (ans + (mod * f)) % mod;
}
void pre() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = 1LL * i * f[i - 1] % mod;
    }
    invf[N - 1] = power(f[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--) {
        invf[i] = 1LL * invf[i + 1] * (i + 1) % mod;
    }
}
int nCr(int n, int r) {
    if(r < 0 || r > n) return 0;
    if(n == 0 && r == 0) return 1;
    return 1LL * f[n] * invf[r] % mod * invf[n - r] % mod;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    ll ans = 0;
    for(int i = 0; i <= k; i++) {
        ll val = (1LL * nCr(n - 1, i) * power(m - 1, n - 1 - i)) % mod;
        ans = (ans + val) % mod;
    }
    cout << (1LL * ans * m) % mod << "\n";
}   
int main() {
    pre();
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        // /cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
