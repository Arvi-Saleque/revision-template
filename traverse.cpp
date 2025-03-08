// https://codeforces.com/contest/1366/problem/C
// travesersing a grid diagonally 

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
void solve() {
    int n, m;
    cin >> n >> m;
    int v[n + 1][m + 1];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> v[i][j];
        }
    }
    vector<vector<int>> mp(n + m + 2, vector<int>());
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            mp[i + j - 2].push_back(v[i][j]); // i + j - 2 is the diagonal
        }
    }
    int ans = 0;
    for(int d = 0; d < (n + m - 1) / 2; d++) { // skip middle diagonal 
        int zero = 0, one = 0;
        auto vv = mp[d];
        for(auto x : vv) {
            (x == 0) ? zero++ : one++; 
        }
        vv = mp[n + m - 2 - d]; // alter diagonal
        for(auto x : vv) {
            (x == 0) ? zero++ : one++; 
        }
        ans += min(zero, one);
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
