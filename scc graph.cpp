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
        indeg.assign(compid + 1, 0);
        outdeg.assign(compid + 1, 0);
        for(int u = 1; u <= n; u++) {
            allcomponents[whichcmp[u]].push_back(u);
            for(auto v : g[u]) {
                int cmpu = whichcmp[u];
                int cmpv = whichcmp[v];
                if(cmpu != cmpv) {
                    // u -> v
                    indeg[cmpv]++;
                    outdeg[cmpu]++;
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


// https://vjudge.net/contest/749434#problem/J
// both side reachability check query 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e4 + 9, mod = 998244353;
const double eps = 1e-9;
const ll inf = 1e18;

struct scc {
    vector<vector<int>> g, rg, condensed, rcondensed, allcomp;
    vector<int> whichcmp, indeg, indegr;
    vector<bitset<N + 2>> bit, rbit;
    int n, compid;
    scc(int n) : n(n) {
        g.resize(n + 1);
        rg.resize(n + 1);
        whichcmp.assign(n + 1, 0);
        compid = 0;
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void build() {
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

        rcondensed.resize(compid + 1);
        condensed.resize(compid + 1);
        allcomp.resize(compid + 1);
        indeg.assign(compid + 1, 0);
        indegr.assign(compid + 1, 0);
        for(int u = 1; u <= n; u++) {
            allcomp[whichcmp[u]].push_back(u);
            for(auto v : g[u]) {
                int cmpu = whichcmp[u];
                int cmpv = whichcmp[v];
                if(cmpu != cmpv) {
                    indegr[cmpu]++;
                    condensed[cmpu].push_back(cmpv);
                    indeg[cmpv]++;
                    rcondensed[cmpv].push_back(cmpu);
                }
            }
        }

        bit.resize(compid + 1);
        rbit.resize(compid + 1);
        for(int i = 1; i <= compid; i++) {
            bit[i][i] = 1;
            rbit[i][i] = 1;
        }

        queue<int> Q;
        for(int i = 1; i <= compid; i++) {
            if(indegr[i] == 0) {
                Q.push(i);
            }
        }
        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            //cout << u << "\n";
            for(auto v : rcondensed[u]) {
                bit[v] |= bit[u];
                indegr[v]--;
                //cout << v << " " << indegr[v] << "\n";
                if(indegr[v] == 0) {
                    Q.push(v);
                }
            }
        }

        for(int i = 1; i <= compid; i++) {
            if(indeg[i] == 0) {
                Q.push(i);
            }
        }
        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            //cout << u << "\n";
            for(auto v : condensed[u]) {
                rbit[v] |= rbit[u];
                indeg[v]--;
                //cout << v << " " << indeg[v] << "\n";
                if(indeg[v] == 0) {
                    Q.push(v);
                }
            }
        }

        // for(int i = 1; i <= compid; i++) {
        //     cout << bit[i] << " " << rbit[i] << "\n";
        // }

    }

};
    
void solve() {
    int n, m;
    cin >> n >> m;
    scc obj(n);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        obj.add_edge(u, v);
    }
    obj.build();
    int q; cin >> q;
    bitset<N + 2> lbit, rbit;
    bool flag = 1;
    while(q--) {
        int u, v;
        cin >> u >> v;

        int cu = obj.whichcmp[u];
        int cv = obj.whichcmp[v];

        // cout << cu << " " << cv << "\n"; 
        // cout << obj.bit[cu] << " " << obj.bit[cv] << "\n"; 

        if((obj.bit[cu] & obj.bit[cv]) != obj.bit[cv]) {
            flag = 0;
        }

        lbit[cu] = 1;
        rbit[cv] = 1;
    }

    if(!flag) {
        cout << "NO\n";
    }
    else {
        for(int i = 1; i <= obj.compid; i++) {
            if((obj.bit[i] & rbit) == rbit && (obj.rbit[i] & lbit) == lbit) {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
