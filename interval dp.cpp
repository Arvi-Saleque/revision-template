// https://vjudge.net/problem/atcoder-dp_n

// instead of breaking think how can merge

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
void solve() {
    int n; cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, -1));
    function<ll(int, int)> f = [&](int l, int r) -> ll {
        if(l >= r) return 0;
        ll &ans = dp[l][r];
        if(ans != -1) return ans;
        ll sum = 0;
        for(int i = l; i <= r; i++) {
            sum += v[i];
        }
        ans = 1e18;
        for(int i = l; i < r; i++) {
            ans = min(ans, sum + f(l, i) + f(i + 1, r));
        }
        return ans;
    };

    cout << f(1, n) << "\n";
}  
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        //cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}
