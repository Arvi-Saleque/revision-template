// https://toph.co/arena?practice=6813c2bb7f6edd8b4346a559#!/p/6749e691bdbdbf46f834aa7d

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
ll const neg = -1e18;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n + 1);
    for(int i = 2; i <= n; i++) {
        int x; cin >> x;
        g[x].push_back(i);
    }
    vector<ll> cost(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    vector<vector<ll>> dp1(n + 1, vector<ll>(k + 1, neg));
    vector<vector<ll>> vis1(n + 1, vector<ll>(k + 1, 0));

    for(int i = 1; i <= n; i++) {
        dp1[i][1] = cost[i];
        dp1[i][0] = 0;
        vis1[i][1] = 1;
        vis1[i][0] = 1;
    }

    vector<vector<vector<ll>>> dp2(n + 1);
    vector<vector<vector<bool>>> vis2(n + 1);

    for(int u = 1; u <= n; u++) {
        int sz = g[u].size();
        dp2[u].assign(sz + 1, vector<ll>(k + 1, neg));
        vis2[u].assign(sz + 1, vector<bool>(k + 1, 0));
    }

    function<ll(int, int, int, vector<int> &)> knapsack = [&](int u, int pos, int cnt, vector<int> &vec) -> ll {
        if(pos == vec.size()) {
            if(cnt == 0) return 0LL;
            return neg;
        }
        ll &ans = dp2[u][pos][cnt];
        if(vis2[u][pos][cnt]) return ans;
        vis2[u][pos][cnt] = 1;
        for(int c = 0; c <= cnt; c++) {
            if(!vis1[vec[pos]][c]) continue;
            ans = max(ans, dp1[vec[pos]][c] + knapsack(u, pos + 1, cnt - c, vec));
        }
        return ans;
    };

    function<ll(int, int, int)> f = [&](int u, int p, int cnt) -> ll {
        ll &ans = dp1[u][cnt];
        if(vis1[u][cnt]) return ans;
        vis1[u][cnt] = 1;
        for(auto v : g[u]) if( v != p) {
            for(int c = 0; c <= cnt; c++) {
                if(!vis1[v][c]) f(v, u, c);
            }
        }
        ll res = neg;
        for(auto v : g[u]) if(v != p) {
            res = max(res, dp1[v][cnt]);
        }
        ans = cost[u];
        vector<int> childs;
        for(auto v : g[u]) if (v != p) {
            childs.push_back(v);
        }
        ans += knapsack(u, 0, cnt - 1, childs);
        return max(ans, res);
    };

    f(1, 0, k);

    ll ans = neg;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dp1[i][k]);
    }

    cout << ans << "\n";
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
