// https://codeforces.com/problemset/problem/1061/C

// reverse DP
// sometimes it needs to do reverse DP to avoid overcounting

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
vector<int> divs[N + 2];
void pre() {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            divs[j].push_back(i);
        }
    }
    for(int i = 1; i <= N; i++) {
        sort(divs[i].rbegin(), divs[i].rend());
    }
}
void solve() {
    pre();
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    vector<ll> dp(N + 2);
    dp[0] = 1;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(auto d : divs[v[i]]) {
            ans = (ans + dp[d - 1]) % mod;
        }
        for(auto d : divs[v[i]]) {
            dp[d] = (dp[d] + dp[d - 1]) % mod;
        }
        //cout << i << " " << ans << "\n";
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
