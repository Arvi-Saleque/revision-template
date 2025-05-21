#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;

void solve() {
    int n, m, q;
    for(int tc = 1; ; tc++) {
        cin >> n >> m >> q;

        if(n + m + q == 0) break;

        if(tc > 1) {
            cout << "\n";
        }

        vector<vector<ll>> dis(n, vector<ll>(n, inf));

        for (int i = 0; i < n; i++) {
            dis[i][i] = 0;
        }

        for(int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dis[u][v] = min(dis[u][v], 1LL * w);
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dis[i][k] < inf && dis[k][j] < inf) {
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    }
                }
            }
        }
        /* if (d[i][k] + d[k][j] < d[i][j] - EPS)
              d[i][j] = d[i][k] + d[k][j]; */

        for (int k = 0; k < n; k++) {
            if(dis[k][k] >= 0) continue;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dis[i][k] < inf && dis[k][j] < inf) {
                        dis[i][j] = -inf; // negative cycle found
                    }
                }
            }
        }
    
        while(q--) {
            int u, v;
            cin >> u >> v;
            ll d = dis[u][v];
            if(d == inf) {
                cout << "Impossible\n";
            }
            else if(d == -inf) {
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
