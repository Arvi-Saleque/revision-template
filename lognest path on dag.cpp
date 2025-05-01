// https://cses.fi/problemset/result/12767783/
/*
check which nodes can reach n then dp from those nodes
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
 
    vector<bool> vis(n + 1, 0);
    vector<bool> okay(n + 1, 0);
    okay[n] = 1;

    function<bool(int)> dfs = [&](int u) -> bool {
        vis[u] = 1;
        for(auto v : g[u]) {
            if(!vis[v]) dfs(v);
            okay[u] = okay[u] || okay[v];
        }
        return okay[u];
    };
 
    dfs(1);
    if(!vis[n]) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    /*for(int i = 1; i <= n; i++) {
        cout << i << " " << okay[i] << "\n";
    }*/
 
    vector<int> dp(n + 1, -1);
    vector<int> child(n + 1, 0);
 
    function<int(int)> f = [&](int u) -> int {
        int &ans = dp[u];
        if(ans != -1) return ans;
        int mx = 0, node = -1;
        for(auto v : g[u]) if(okay[v]) {
            int cur = 1 + f(v);
            if(cur > mx) {
                mx = cur;
                child[u] = v;
            }
        }
        return ans = mx;
    };
    f(1);
    vector<int> path;
    int u = 1;
    while(u != n) {
        path.push_back(u);
        u = child[u];
    }
    path.push_back(n);
 
    cout << path.size() << "\n";
    for(auto x : path) {
        cout << x << " ";
    }
    cout << "\n";
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

// more clean and sorter code

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
 
    vector<int> dp(n + 1, -1e9);
    vector<int> child(n + 1, 0);
 
    function<int(int)> f = [&](int u) -> int {
        int &ans = dp[u];
        if(ans != -1e9) return ans;
        if(u == n) return ans = 0;
        int mx = -1e9, node = -1;
        for(auto v : g[u]) {
            int cur = f(v);
            if(cur != -1e9 && cur + 1 > mx) {
                mx = cur + 1;
                child[u] = v;
            }
        }
        return ans = mx;
    };
    f(1);

    if (dp[1] < 0) {      
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> path;
    int u = 1;
    while(u != n) {
        path.push_back(u);
        u = child[u];
    }
    path.push_back(n);
 
    cout << path.size() << "\n";
    for(auto x : path) {
        cout << x << " ";
    }
    cout << "\n";
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

// iiterative appraoch 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }
    
    queue<int> Q;
    for(int i = 1; i <= n; i++) {
        if(indeg[i] == 0) Q.push(i);
    }

    vector<int> topo;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        topo.push_back(u);
        for(auto v : g[u]) {
            if(--indeg[v] == 0) {
                Q.push(v);
            }
        }
    }

    vector<int> dp(n + 1, -1e9);
    vector<int> par(n + 1, 0);
    
    dp[1] = 1;

    for(auto u : topo) {
        if(dp[u] == -1e9) continue;
        for(auto v : g[u]) {
            if(dp[u] + 1 > dp[v]) {
                dp[v] = dp[u] + 1;
                par[v] = u;
            }
        }
    }

    if(dp[n] == -1e9) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> path;
    int u = n;
    while(u != 0) {
        path.push_back(u);
        u = par[u];
    }
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for(auto x : path) {
        cout << x << " ";
    }
    cout << "\n";
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
