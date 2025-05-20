#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
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
                if(low[v] > disc[u]) {
                    mp[{min(u, v), max(u, v)}] = 1;
                }
            }
        }
    };
 
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs1(i, 0);
        }
    }

    vis.assign(n + 1, 0);
    vector<int> whichcmp(n + 1, 0), path;
    int cmpid = 0;

    function<void(int)> dfs2 = [&](int u) -> void {
        vis[u] = 1;
        path.push_back(u);
        for(auto v : g[u]) if(!vis[v]) {
            if(mp.count({min(u, v), max(u, v)})) continue;
            dfs2(v);
        }
    };

    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            path.clear();
            dfs2(i);
            cmpid++;
            for(auto x : path) {
                whichcmp[x] = cmpid;
            }
        }
    }

    vector<vector<int>> bridgetree(cmpid + 1);
    for(int u = 1; u <= n; u++) {
        for(auto v : g[u]) {
            if(whichcmp[u] != whichcmp[v]) {
                bridgetree[whichcmp[u]].push_back(whichcmp[v]);
                bridgetree[whichcmp[v]].push_back(whichcmp[u]);
            }
        }
    }

    vector<int> dis;

    function<int(int)> bfs = [&](int u) -> int {
        dis.assign(cmpid + 1, -1);
        queue<int> Q;
        Q.push(u);
        dis[u] = 0;
        int node = u, mx = 0;
        while(not Q.empty()) {
            int p = Q.front(); Q.pop();
            for(auto v : bridgetree[p]) {
                //cout << p << " " << v << "\n";
                if(dis[v] == -1) {
                    dis[v] = dis[p] + 1;
                    Q.push(v);
                    if(dis[v] > mx) {
                        mx = dis[v];
                        node = v;
                    }
                }
            }
        }
        return node;
    };

    auto nd1 = bfs(1);
    auto nd2 = bfs(nd1);

    cout << dis[nd2] << "\n";

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
