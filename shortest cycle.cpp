// https://codeforces.com/problemset/problem/1205/B
// to get the shortest cycle remove the edge of u-v and
// caluculate the sortest distance between u - v

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<ll> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    for(int i = 0; i <= 60; i++) {
        int cnt = 0;
        for(int j = 1; j <= n; j++) {
            if(v[j] == 0) continue;
            if(v[j] & (1LL << i)) {
                cnt++;
            }
        }
        if(cnt >= 3) {
            cout << "3\n";
            return;
        }
    }

    map<int, vector<int>> g;
    for(int i = 1; i <= n; i++) {
        if(v[i] == 0) continue;
        for(int j = 1; j <= n; j++) {
            if(v[j] == 0) continue;
            if(i != j && (v[i] & v[j]) != 0) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    map<pair<int, int>, bool> vis;

    auto bfs = [&](int u, int t) {
        vector<int> dis(n + 1, -1);
        queue<int> Q;
        Q.push(u);
        dis[u] = 0;
        while(!Q.empty()) {
            int pu = Q.front(); Q.pop();
            for(auto v : g[pu]) {
                if(vis.count({pu, v}) || vis.count({v, pu})) continue;
                if(dis[v] == -1) {
                    dis[v] = dis[pu] + 1;
                    Q.push(v);
                }
            }
        }
        //cout << u << " " << t << " " << dis[t] << "\n";
        return dis[t];
    };

    int ans = 1e9;
    for(int u = 1; u <= n; u++) {
        if(v[u] == 0) continue;
        for(auto v : g[u]) {
            vis[{u, v}] = 1;
            //cout << u << " " << v << "\n";
            int val = bfs(u, v);
            ans = min(ans, (val == -1 ? (int)1e9 : val + 1));
            vis[{v, u}] = 0;
        }
    }
    if(ans == 1e9) ans = -1;
    cout << ans << "\n";
}  
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        //cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}
