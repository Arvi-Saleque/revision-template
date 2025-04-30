// https://cses.fi/problemset/task/1133/
// dp[v] = dp[u] - sz[v] + (n - sz[v]);

/* process - 1 */
#include <iostream>
#include <vector>
using namespace std;
 
const int NMAX = 200001;
int n;
vector<int> adj[NMAX];
long long subSize[NMAX];   // Number of nodes in the subtree of a node (including itself)
long long distSum[NMAX];   // Sum of distances from the current root (initially 1) to nodes in its subtree
long long ans[NMAX];       // Final answer for each node
 
// First DFS: compute subSize and distSum for an arbitrary root (node 1)
void dfs1(int u, int parent) {
    subSize[u] = 1; // Count itself
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs1(v, u);
        subSize[u] += subSize[v];
        distSum[u] += distSum[v] + subSize[v];
    }
}
 
// Second DFS: re-root the tree using the answer for the parent to compute answer for the child.
void dfs2(int u, int parent) {
    ans[u] = distSum[u];
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        // Backup current values before modifying
        long long orig_u_distSum = distSum[u];
        long long orig_v_distSum = distSum[v];
        long long orig_u_subSize = subSize[u];
        long long orig_v_subSize = subSize[v];
        
        // Remove v's contribution from u and add the remainder to v
        distSum[u] -= (distSum[v] + subSize[v]);
        subSize[u] -= subSize[v];
        
        distSum[v] += (distSum[u] + subSize[u]);
        subSize[v] += subSize[u];
        
        dfs2(v, u);
        
        // Restore original values after recursion (backtracking)
        distSum[u] = orig_u_distSum;
        distSum[v] = orig_v_distSum;
        subSize[u] = orig_u_subSize;
        subSize[v] = orig_v_subSize;
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // First DFS from node 1 to compute subtree sizes and initial distance sum
    dfs1(1, 0);
    
    // Second DFS to re-root the tree and compute answer for each node
    dfs2(1, 0);
    
    // Print the result for nodes 1 through n.
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}

/* process - 2 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(n + 1);
 
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        for(auto v : g[u]) {
            if(v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
        sz[u] += 1; 
    };
 
    dfs(1, 0);
 
    vector<ll> dp1(n + 1, -1);
    function<ll(int, int)> f1 = [&](int u, int p) -> ll {
        ll &ans = dp1[u];
        if(ans != -1) return ans;
        ans= 0;
        for(auto v : g[u]) if(v != p) {
            f1(v, u);
            ans += (dp1[v] + sz[v]);
        }
        return ans;
    };
    f1(1, 0);
 
    vector<ll> dp2(n + 1, -1);
    
    queue<pair<int, int>> Q;
    Q.push({1, 0});
    dp2[1] = dp1[1];
 
    while(!Q.empty()) {
        auto [u, p] = Q.front(); Q.pop();
        for(auto v : g[u]) if(v != p) {
            ll cur_val = dp1[v];
            ll par_val = dp2[u] - (cur_val + sz[v]);
            cur_val += (par_val + (n - sz[v]));
            dp2[v] = cur_val;
            Q.push({v, u});
        }
    }
 
    for(int i = 1; i <= n; i++) {
        cout << dp2[i] << " \n"[i == n];
    }
 
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

/* process - 3 */
// clean code of process - 2

// 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(n + 1);
    vector<ll> dp(n + 1);

    function<void(int, int)> dfs1 = [&](int u, int p) -> void {
        sz[u] = 1;
        for(auto v : g[u]) {
            if(v != p) {
                dfs1(v, u);
                sz[u] += sz[v];
                dp[1] += sz[v]; // root is 1
            }
        }
    };
    dfs1(1, 0);

    function<void(int, int)> dfs2 = [&](int u, int p) -> void {
        for(auto v : g[u]) if(v != p) {
            dp[v] = dp[u] - sz[v] + (n - sz[v]);
            dfs2(v, u);
        }
    };
    dfs2(1, 0);

    for(int i = 1; i <= n; i++) {
        cout << dp[i] << " \n"[i == n];
    }

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
