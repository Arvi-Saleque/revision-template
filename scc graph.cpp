#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;

struct SCC_graph {
    vector<vector<int>> g, rg, condensed, allcomponents;
    vector<int> whichcmp, indeg, outdeg;
    int n, m, q, compid;
    SCC_graph(int n, int m, int q = 0) : n(n), m(m), q(q) {
        g.resize(n + 1);
        rg.resize(n + 1);
        whichcmp.assign(n + 1, 0);
        compid = 0;
        take_input();
    }
    void take_input() {
        for(int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            rg[v].push_back(u);
        }
        build();
    }
    void build() {
        // get the order
        vector<int> order;
        vector<bool> vis(n + 1, 0);
        function<void(int)> dfs1 = [&](int u) -> void {
            vis[u] = 1;
            for(auto v : g[u]) if(!vis[v]) {
                dfs1(v);
            }
            order.push_back(u);
        };
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) dfs1(i);
        }
        reverse(order.begin(), order.end());

        // make SCC
        vector<int> cmp;
        function<void(int)> dfs2 = [&](int u) -> void {
            vis[u] = 1;
            for(auto v : rg[u]) if(!vis[v]) {
                dfs2(v);
            }
            cmp.push_back(u);
        };
        vis.assign(n + 1, 0);
        for(auto u : order) {
            if(!vis[u]) {
                cmp.clear();
                dfs2(u);
                compid++;
                for(auto x : cmp) {
                    whichcmp[x] = compid;
                }
            }
        }
        // make the condensed graph
        condensed.resize(compid + 1);
        allcomponents.resize(compid + 1);
        indeg.resize(compid + 1);
        outdeg.resize(compid + 1);
        for(int u = 1; u <= n; u++) {
            allcomponents[whichcmp[u]].push_back(u);
            for(auto v : g[u]) {
                int cmpu = whichcmp[u];
                int cmpv = whichcmp[v];
                if(cmpu != cmpv) {
                    // u -> v
                    indeg[cmpu]++;
                    outdeg[cmpv]++;
                    condensed[cmpu].push_back(cmpv);
                }
            }
        }
    }   
    void print() {
        cout << compid << "\n";
        for(int c = 1; c <= compid; c++) {
            cout << allcomponents[c].size();
            for(auto x : allcomponents[c]) {
                cout << " " << x - 1;
            }
            cout << "\n";   
        }
    }
    void solve() {
        print();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    SCC_graph graph(n, m);
    graph.solve();
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
