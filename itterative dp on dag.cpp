//https://codeforces.com/problemset/problem/919/D

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    string s; cin >> s;
    s = '.' + s;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for(int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }
    bool cycle = 0;
    vector<int> vis(n + 1);
    function<void(int)> check = [&](int u) {
        vis[u] = 1;
        for(auto v : g[u]) {
            if(vis[v] == 0) {
                check(v);
                if(cycle) return;
            }
            else if(vis[v] == 1) {
                cycle = 1;
                return;
            }
        }
        vis[u] = 2;
    };
    for(int v = 1; v <= n; v++) {
        if(vis[v] == 0 && !cycle) check(v);
    }
    if(cycle) {
        cout << "-1\n";
        return;
    }
    /*vector<vector<int>> dparr(n + 1, vector<int>(27, -1));
    function<int(int, char)> dp = [&](int u, char target) -> int {
        int &ans = dparr[u][target - 'a'];
        if(ans != -1) return ans;
        ans = 0;
        for(auto v : g[u]) {
            ans = max(ans, dp(v, target));
        }
        ans += (s[u] == target);
        return ans;
    };*/
    vector<vector<int>> dp(n + 1, vector<int>(27, 0));
    int ans = 0;
    for(char ch = 'a'; ch <= 'z'; ch++) {
        queue<int> Q;
        for(int i = 1; i <= n; i++) {
            if(indeg[i] == 0) {
                Q.push(i);
                dp[i][ch - 'a'] = (s[i] == ch);
            }
        }
        auto indegg = indeg;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            ans = max(ans, dp[u][ch - 'a']);
            for(auto v : g[u]) {
                dp[v][ch - 'a'] = max(dp[v][ch - 'a'], dp[u][ch - 'a'] + (s[v] == ch));
                indegg[v]--;
                if(indegg[v] == 0) {
                    Q.push(v);
                }
            }
        }
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

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    string s; cin >> s;
    s = '.' + s;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for(int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }
    
    vector<int> topo;
    queue<int> Q;

    for(int i = 1; i <= n; i++) {
        if(indeg[i] == 0) {
            Q.push(i);
        }
    }

    while(!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        topo.push_back(u);
        for(auto v : g[u]) {
            indeg[v]--;
            if(indeg[v] == 0) {
                Q.push(v);
            }
        }
    }

    if(topo.size() != n) {
        cout << "-1\n";
        return;
    }

    vector<vector<int>> dp(n + 1, vector<int>(27));
    int ans = 0;
    for(auto u : topo) {
        dp[u][s[u] - 'a']++;
        ans = max(ans, dp[u][s[u] - 'a']);
        for(auto v : g[u]) {
            for(int i = 0; i < 26; i++) {
                dp[v][i] = max(dp[v][i], dp[u][i]);
            }
        }
    }
    cout << ans << "\n";
}
