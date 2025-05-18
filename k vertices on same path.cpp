// https://codeforces.com/contest/1702/problem/G2

/*
given k vertices
and you need to check if they are on the same path
so let lc = lca of k vertices 
find diameter endpoint of lc tree u and v
then just check for each node if 
dist(u, v) == dist(u, x) + dist(v, x)
*/

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;
class LCA {
public:
    int n;
    vector<vector<int>> g, par;
    vector<int> dep, sz, tin, tout;
    int lg, timer;
    LCA(){}
    LCA(int n) {
        timer = 0;
        this -> n = n;
        g.assign(n + 1, vector<int>());
        lg = log2(n) + 1;
        par.assign(n + 1, vector<int>(lg + 1, 0));
        dep.assign(n + 1, 0);
        tin.assign(n + 1, 0);
        tout.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        take_input();
    }
    void take_input() {
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs();
    }
    void dfs(int u = 1, int p = 0) {
        par[u][0] = p;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        tin[u] = timer++;
        for(int i = 1; i <= lg; i++) {
            par[u][i] = par[par[u][i - 1]][i - 1];
        }
        for(auto v : g[u]) {
            if(v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            } 
        }
        tout[u] = timer++;
    }
    int lca(int u, int v) {
        if(u == 0) return v;
        if(v == 0) return u;
        if(dep[u] < dep[v]) swap(u, v); // make sure that dep[u] > dep[v]
        for(int k = lg; k >= 0; k--) {
            if(dep[par[u][k]] >= dep[v]) u = par[u][k];
        }
        if(u == v) return v;
        for(int k = lg; k >= 0; k--) {
            if(par[u][k] != par[v][k]) {
                u = par[u][k];
                v = par[v][k];
            }
        } 
        return par[u][0];
    }
    int dist(int u, int v) {
        int l = lca(u, v);
        return dep[u] + dep[v] - (2 * dep[l]);
    }
    void solve() {
        int q; cin >> q;
        while(q--) {
            int k; cin >> k;
            vector<int> nodes(k);
            for(auto &x : nodes) {
                cin >> x;
            }
            auto get = [&](int u) {
                int node = u, mx = 0;
                for(auto v : nodes) {
                    int d = dist(u, v);
                    if(d > mx) {
                        mx = d;
                        node = v;
                    }
                }
                return node;
            };
            
            int u = get(nodes[0]);
            int v = get(u);
            int d = dist(u, v);

            string ans = "YES";
            for(auto x : nodes) {
                int d1 = dist(x, u);
                int d2 = dist(x, v);
                if(d1 + d2 != d) {
                    ans = "NO";
                    break;
                } 
            }

            cout << ans << "\n";
        }
    }
};

void solve() {
    int n;
    cin >> n;
    LCA lca(n);
    lca.solve();
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
