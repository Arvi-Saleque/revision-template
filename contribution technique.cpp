// https://vjudge.net/problem/atcoder-arc116_b

// as subsequecen order does not matter so i can sort then
// fix J and try to find all i < j and how much contribute a[j]
// as max and min

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
ll power(ll a, ll b) {
    ll ans = 1;
    bool f = (a >= mod);
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
    return (ans + (f * mod)) % mod;
}
void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    sort(v.begin(), v.end());
    vector<int> suff(n + 2, 0);
    for(int i = n - 1; i > 0; i--) {
        int val = (1LL * v[i] * power(2, (i - 1))) % mod;
        suff[i] = (suff[i + 1] + val) % mod;
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans = (ans + (1LL * v[i] * v[i]) % mod) % mod;
        int val = (1LL * v[i] * power(power(2, i), mod - 2)) % mod;
        ans = (ans + (1LL * val * suff[i + 1]) % mod) % mod;
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    // /cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
