// https://atcoder.jp/contests/abc259/tasks/abc259_f?lang=en

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld inf = 1e100; 
const ld eps = 1e-18;

void solve() {
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<vector<pair<int, int>>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }
    vector<vector<ll>> dp(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        dp[u].assign(d[u] + 1, -1);
        dp[u][0] = 0;
        for(auto [w, v] : g[u]) if(v != p) {
            dfs(v, u);
        }
        vector<ll> profit;
        for (auto [w,v] : g[u]) if (v != p) {
            ll keep = dp[v][ d[v] ];          
            dp[u][0] += keep;                 

            if (d[v] >= 1) {
                ll take = w + dp[v][ d[v]-1 ];   
                ll gain = take - keep;           
                if (gain > 0) profit.push_back(gain);
            }
        }
        sort(profit.rbegin(), profit.rend());      

        for (int c = 1; c <= d[u]; ++c) {
            if (c <= (int)profit.size())
                dp[u][c] = dp[u][c-1] + profit[c-1];
            else
                dp[u][c] = dp[u][c-1];
        }

    };
    dfs(1, 0);
    cout << dp[1][d[1]] << "\n";
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while (tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
