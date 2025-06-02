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
