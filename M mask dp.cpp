//https://atcoder.jp/contests/abc165/tasks/abc165_c?lang=en

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 2e5 + 9;
int n, m, q;
vector<array<int, 4>> Q;

vector<map<ll, ll>> dp;

ll f(int pos, ll mask) { 
    if(pos == n) {
        vector<int> v(n);
        ll tmpmask = mask;
        for(int i = n - 1; i >= 0; i--) {
            v[i] = (tmpmask % (m + 1));
            tmpmask /= (m + 1); 
        }
        ll tmp = 0;
        for(auto [a, b, c, d] : Q) {
            tmp += (v[b] - v[a] == c ? d : 0);
        }
        return tmp;
    }
    if(dp[pos].count(mask)) return dp[pos][mask];
    ll &ans = dp[pos][mask];
    int start = 1;
    if(pos > 0) start = mask % (m + 1);
    for(int j = start; j <= m; j++) {
        ll tmpmask = (mask * (m + 1) + j);
        ans = max(ans, f(pos + 1, tmpmask));
    }
    
    return ans;
}

void solve() {
    cin >> n >> m >> q;
    Q.resize(q);
    for(auto &[a, b, c, d] : Q) {
        cin >> a >> b >> c >> d;
        a--;
        b--;
    }
    dp.resize(n + 1);
    cout << f(0, 0) << "\n";
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