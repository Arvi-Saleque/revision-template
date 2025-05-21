#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;

void solve() {
    int n, m, q, s;
    for(int tc = 1; ; tc++) {
        cin >> n >> m >> q >> s;

        if(n + m + q + s == 0) break;

        if(tc > 1) {
            cout << "\n";
        }

        vector<array<int, 3>> edges;
        vector<vector<int>> g(n + 1);

        for(int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            g[u].push_back(v);

        }

        vector<ll> dis(n, inf);
        dis[s] = 0;

        // n - 1 relaxation
        for(int c = 1; c < n; c++) {
            bool relax = false;
            for(auto [u, v, w] : edges) {
                if(dis[u] != inf && dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    relax = true;
                }
            }
            if(!relax) false;
        }

        queue<int> Q;
        for(auto [u, v, w] : edges) {
            if(dis[u] != inf && dis[u] + w < dis[v]) {
                Q.push(u);
            }
        }

        vector<int> bad(n);
        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            bad[u] = 1;
            for(auto v : g[u]) {
                if(!bad[v]) {
                    bad[v] = 1;
                    Q.push(v);
                }
            }
        }
        
    
        while(q--) {
            int u;
            cin >> u;
            ll d = dis[u];
            if(d == inf) {
                cout << "Impossible\n";
            }
            else if(bad[u]) {
                cout << "-Infinity\n";
            }
            else {
                cout << d << "\n";
            }
        }
    }   
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
