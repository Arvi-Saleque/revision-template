// https://codeforces.com/contest/231/problem/E

/*
convert the cycle to a node
make a tree then apply LCA
*/

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = (1 << 21), mod = 1e9 + 7;

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

    int component = 0;
    vector<int> which(n + 1), col;
    col.push_back(0); // make 1 based
    vector<bool> vis(n + 1);
    vector<int> path;

    function<void(int, int)> dfs = [&](int u, int p) -> void {
        vis[u] = 1;
        path.push_back(u);

        for(auto v : g[u]) if(v != p) {
            if(!vis[v]) {
                dfs(v, u);
            }
            else if(!which[v]){
                ++component;
                col.push_back(1);
                int x;
                do {
                    x = path.back(); path.pop_back();
                    which[x] = component;
                } while (x != v);
            }
        }
        if(!which[u]) {
            ++component;
            col.push_back(0);
            which[u] = component;
            path.pop_back();
        }
    };

    for(int i = 1; i <= n; i++) {
        if(!vis[i]) dfs(i, -1);
    }

    vector<vector<int>> tree(component + 1);
    for(int u = 1; u <= n; u++) {
        for(auto v : g[u]) {
            if(which[u] != which[v]) {
                tree[which[u]].push_back(which[v]);
            }
        }
    }

    for(int i = 1; i <= component; i++) {
        auto & adj = tree[i];
        sort(adj.begin(), adj.end());
        adj.erase(unique(adj.begin(), adj.end()), adj.end());
    }

    int q; cin >> q;
    vector<pair<int, int>> Q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        Q.push_back({which[u], which[v]});
    }

    class LCA {
    public:
        int n;
        vector<vector<int>> g, par;
        vector<int> dep, sum, sz, col, power;
        vector<pair<int, int>> Q;
        int lg;
        LCA(){}
        LCA(int n, vector<vector<int>> gg, vector<int> ccol, vector<pair<int, int>> qq) {
            Q = qq;
            this -> n = n;
            g = gg;
            lg = log2(n) + 1;
            par.assign(n + 1, vector<int>(lg + 1, 0));
            dep.assign(n + 1, 0);
            sum.assign(n + 1, 0);
            sz.assign(n + 1, 0);
            col = ccol;
            power.assign(n + 1, 1);
            for(int i = 1; i <= n; i++) {
                power[i] = (2LL * power[i - 1]) % mod;
            }
            dep[0] = -1;
            dfs();
        }
        void dfs(int u = 1, int p = 0) {
            par[u][0] = p;
            dep[u] = dep[p] + 1;
            sum[u] = sum[p] + col[u];
            for(int i = 1; i <= lg; i++) {
                par[u][i] = par[par[u][i - 1]][i - 1];
            }
            for(auto v : g[u]) {
                if(v != p) {
                    dfs(v, u);
                } 
            }
        }
        int lca(int u, int v) {
            if(dep[u] < dep[v]) swap(u, v);
            for(int k = lg; k >= 0; k--) {
                if(par[u][k] && dep[par[u][k]] >= dep[v])
                    u = par[u][k];
            }
            if(u == v) return v;
            for(int k = lg; k >= 0; k--) {
                if(par[u][k] && par[v][k] && par[u][k] != par[v][k]) {
                    u = par[u][k];
                    v = par[v][k];
                }
            }
            return par[u][0];
        }
        void solve() {
            for (auto [x, y] : Q) {
                int l = lca(x, y);                          
                int cnt =  sum[x] + sum[y] - 2 * sum[l] + col[l];              
                cout << power[cnt] << '\n';                  
            }
        }
    };

    LCA obj(component + 1, tree, col, Q);
    obj.solve();

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
