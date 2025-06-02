#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<char, int>>> g(n + 1);
    for(int i = 1; i <= m; i++){
        int u, v;
        char ch;
        cin >> u >> v >> ch;
        g[u].push_back({ch, v});
        g[v].push_back({ch, u});
    }
    
    queue<array<int, 3>> Q;
    vector<vector<bool>> vis(n + 1, vector<bool>(n + 1, 0));
    Q.push({1, n, 0});
    vis[1][n] = 1;
    int ans = 1e9;
    while(!Q.empty()) {
        auto [u, v, d] = Q.front(); Q.pop();
        if(u == v) {
            ans = min(ans, d);
        }
        else {
            for(auto [ch, vv] : g[u]) {
                if(vv == v) {
                    ans = min(ans, 1 + d);
                }
            }
            for(auto [ch1, uu] : g[u]) {
                for(auto [ch2, vv] : g[v]) {
                    if(vis[uu][vv] || ch1 != ch2) continue;
                    vis[uu][vv] = 1;
                    Q.push({uu, vv, d + 2});
                }
            }
        }
    }

    if(ans == 1e9) ans = -1;
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}

// number of pairs (u, v) a palindrome walk exist
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e7 + 9, mod = 1e9 + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<char, int>>> g(n + 1), rg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; char w;
        cin >> u >> v >> w;
        g[u].push_back({w, v});
        rg[v].push_back({w, u});
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for(int u = 1; u <= n; u++) {
        dp[u][u]  = 1;
        for(auto [w, v] : g[u]) {
            dp[u][v] = 1;
        }
    }
    deque<pair<int,int>> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(dp[i][j]) {
                q.emplace_back(i, j);
            }
        }
    }
    while(!q.empty()) {
        auto [v1, v2] = q.front();
        q.pop_front();
        for(auto [ch1, u1] : rg[v1]) {
            for(auto [ch2, u2] : g[v2]) {
                if(ch1 != ch2) continue;
                if(!dp[u1][u2]) {
                    dp[u1][u2] = 1;
                    q.emplace_back(u1, u2);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;
            ans += dp[i][j];
        }
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    while(tc--) {
        solve();
    }
    return 0;
}

