#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;
void solve() {
    int  n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    map<pair<int, int>, int> edge;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> state(n + 1, 0), par(n + 1, -1);
    vector<int> cycle;
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        state[u] = 1;
        for(auto v : g[u])  {
            //if(v == p) continue; // only for undirected
            if(state[v] == 0) {
                par[v] = u;
                dfs(v, u);
            }
            else if(state[v] == 1 && cycle.empty()) {
                cycle.push_back(v);
                for(int cur = u; cur != v ; cur = par[cur]) {
                    cycle.push_back(cur);
                }
                cycle.push_back(v);
            }
        }
        state[u] = 2; 
    };

    for(int i = 1; i <= n; i++) {
        if(state[i] == 0) {
            dfs(i, -1);
        }
    }

    if(cycle.empty()) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        reverse(cycle.begin(), cycle.end());
        cout << cycle.size() << "\n";
        for(auto x : cycle) {
            cout << x << " ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
