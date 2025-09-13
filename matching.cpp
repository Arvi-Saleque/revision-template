// https://cses.fi/problemset/task/1696

#include <bits/stdc++.h>
using namespace std;

struct Kuhn {
    vector<vector<int>> g;
    vector<int> match;
    vector<bool> vis;
    int n; // number of left-side nodes (boys)

    Kuhn(int n) : n(n) {
        g.resize(n + 1);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v); // boy u → girl v
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<pair<int,int>> run(int m) {
        match.assign(m + 1, -1);
        for (int u = 1; u <= n; u++) {
            vis.assign(m + 1, false);
            dfs(u);
        }
        vector<pair<int,int>> res;
        for (int v = 1; v <= m; v++) {
            if (match[v] != -1) {
                res.push_back({match[v], v});
            }
        }
        return res;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    Kuhn obj(n);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        obj.add_edge(u, v);
    }
    auto ans = obj.run(m);
    cout << ans.size() << "\n";
    for (auto [boy, girl] : ans) {
        cout << boy << " " << girl << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
