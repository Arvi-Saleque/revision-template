#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    map<pair<int, int>, int> edges; // chekc for multiple edges
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges[{min(u, v), max(u, v)}]++;
    }
    
    int time = 0;
    vector<bool> vis(n + 1);
    vector<int> disc(n + 1), low(n + 1);
    map<pair<int, int>, bool> mp;
    function<void(int, int)> dfs1 = [&](int u, int p) -> void {
        vis[u] = 1;
        disc[u] = low[u] = time++;
        for(auto v : g[u]) if (v != p) {
            if(vis[v]) {
                low[u] = min(low[u], disc[v]);
            }
            else {
                dfs1(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] > disc[u] && edges[{min(u, v), max(u, v)}] == 1) { // if u -> v only one edge
                    mp[{min(u, v), max(u, v)}] = 1;
                }
            }
        }
    };
 
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs1(i, -1);
        }
    }

    vector<vector<int>> ans;
    vector<int> cmp;
    vis.assign(n + 1, 0);

    function<void(int, int )> dfs2 = [&](int u, int p) -> void {
        vis[u] = 1;
        cmp.push_back(u);
        for(auto v : g[u]) if(v != p && !vis[v]) {
            if(mp.count({min(u, v), max(u, v)})) continue;
            dfs2(v, u);
        }
    };

    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            cmp.clear();
            dfs2(i, -1);
            ans.push_back(cmp);
        }
    }

    cout << ans.size() << "\n";
    for(auto v : ans) {
        cout << v.size() << " ";
        for(auto x : v) {
            cout << x << " ";
        }
        cout << "\n";
    }
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
