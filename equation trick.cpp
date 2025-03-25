// https://codeforces.com/problemset/problem/1189/E

// if we need to work with modular arithmatic 
// like ai + aj (=) ai^2 + aj^2 mod p
// then try to generanize and make all i/j in one side
// do some algebra and try to find solution

`a_i^4 - a_j^4 = (a_i - a_j)(a_i + a_j)(a_i^2 + a_j^2)`


#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
void solve() {
    ll n, p, k;
    cin >> n >> p >> k;
    vector<ll> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    auto f = [&](ll x) {
        ll ans = 1;
        for(int i = 1; i <= 4; i++) {
            ans = ((1LL * ans * x) % p);
        }
        return ans;
    };

    map<ll, int> mp;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll val = ((f(v[i])  - (1LL * k * v[i]) % p) + p) % p;
        ans += mp[val];
        mp[val]++;
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
