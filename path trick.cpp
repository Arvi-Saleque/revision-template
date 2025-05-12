// https://codeforces.com/problemset/problem/1328/E

/*
if i need to check if any node u belongs to the path
from root to a fixed leaf 
we need to check just
tin[u] <= tin[leaf] && tout[u] >= tout[leaf]
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 9, mod = 998244353; 
void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> tin(n + 1), tout(n + 1), dis(n + 1), par(n + 1, 0);
    int time = 1;
    function<void(int, int, int)> dfs = [&](int u, int p, int d) -> void {
        tin[u] = time++;
        dis[u] = d;
        par[u] = p;
        for(auto v : g[u]) if (v != p) {
            dfs(v, u, d + 1);
        }
        tout[u] = time++;
    };

    dfs(1, 0, 0);

    // return true if u is on the path from root to leaf
    auto check = [&](int leaf, int u) {
        if(tin[u] <= tin[leaf] && tout[u] >= tout[leaf]) return true;
        return false;
    };

    while(q--) {
        int k; cin >> k;
        vector<int> nodes;
        int node = 1, mx = 0;
        for(int i = 1; i <= k; i++) {
            int x; cin >> x;
            if(mx < dis[x]) {
                mx = dis[x];
                node = x;
            }
            nodes.push_back(x);
        }
        for(auto &x : nodes) {
            if(x == node || x == 1) continue;
            x = par[x];
        }
        bool flag = 1;
        for(auto x : nodes) {
            //cout << x << " " << check(node, x) << "\n";
            flag &= check(node, x);
        }
        cout << (flag ? "YES\n" : "NO\n");
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": " << "\n";
        solve();
    }
}
