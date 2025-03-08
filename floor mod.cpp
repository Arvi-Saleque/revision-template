// https://atcoder.jp/contests/arc111/tasks/arc111_a?lang=en

// floor(a / b) % M = ((a - (a % b)) / b) % M
// if a^n too check if it is someting equal as a^n % m^2 % M  

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9;
ll power(ll a, ll b, ll mod) {
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
    ll n, m;
    cin >> n >> m;
    ll k = power(10, n, m*m);
    cout << (k - (k % m)) / m << "\n";
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
