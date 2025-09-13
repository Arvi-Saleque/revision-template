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

// https://judge.yosupo.jp/problem/bipartitematching

#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    vector<vector<int>> g;
    vector<int> pairU, pairV, dis;
    int n, m;

    HopcroftKarp(int n, int m) : n(n), m(m) {
        g.resize(n + 1);
        dis.resize(n + 1);
        pairU.assign(n + 1, -1);
        pairV.assign(m + 1, -1);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v); 
    }

    bool bfs() {
        queue<int> Q;
        for(int u = 1; u <= n; u++) {
            if(pairU[u] == -1) {
                dis[u] = 0;
                Q.push(u);
            }
            else {
                dis[u] = -1;
            }
        }
        bool flag = false;
        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            for(auto v : g[u]) {
                int u2 = pairV[v];
                if(u2 == -1) {
                    flag = true;
                }
                else if(dis[u2] == -1) {
                    dis[u2] = dis[u] + 1;
                    Q.push(u2);
                }
            }
        }
        return flag;
    }

    bool dfs(int u) {
        for(auto v : g[u]) {
            int u2 = pairV[v];
            if(u2 == -1 || (dis[u2] == dis[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dis[u] = -1;
        return false;
    }

    int run() {
        int match = 0;
        while(bfs()) {
            for(int u = 1; u <= n; u++) {
                if(pairU[u] == -1 && dfs(u)) {
                    match++;
                }
            }
        }
        return match;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    HopcroftKarp obj(n, m);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u++;
        v++;
        obj.add_edge(u, v);
    }
    cout << obj.run() << "\n";
    for(int u = 1; u <= n; u++) {
        if(obj.pairU[u] != -1) {
            cout << u - 1 << " " << obj.pairU[u] - 1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}

