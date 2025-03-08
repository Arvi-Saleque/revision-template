// https://tlx.toki.id/problems/troc-16/D

// if we need to wokr with two group and need to count
// min-max or max-min then check if binary search possible
// then based on serach devide them into two group 
// then check bipartite graph exist or not

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 9;
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> v(n + 1, vector<int>(n + 1));
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> v[i][j];
            mx = max(mx, v[i][j]);
        }
    }

    auto check = [&](int k) {
        vector<vector<int>> g(n + 1);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i == j) continue;
                if(v[i][j] < k) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        vector<int> col(n + 1, 0);
        vector<bool> vis(n + 1, 0);
        function<void(int, bool&)> dfs = [&](int u, bool &flag) { 
            if(!flag) return;
            vis[u] = 1;
            for(auto v : g[u]) {
                if(vis[v]) {
                    if(col[v] == col[u]) {
                        flag = 0;
                        return;
                    }
                    continue;
                }
                col[v] = col[u] ^ 1;
                dfs(v, flag);
            }
        };

        bool res = 1;
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                bool flag = 1;
                dfs(i, flag);
                res &= flag;
            }
        }

        return res;

    };

    int lo = 1, hi = mx, mid, bans = -1;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(check(mid)) {
            bans = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << bans << "\n";
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