// https://codeforces.com/gym/102964/problem/F

// if I need to make any inc/dec sequence and 1-n all are present 
// then i can check only if 1 and n both present

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 300002, mod = 1e9 + 7;
int n, m; // n size m values
int dp[2002][2002][2][2];
int f(int pos, int cur, bool f1, bool fm) {
    if(cur < 1 || cur > m) return 0;
    //cout << pos << " " << cur << " " << f1 << " " << fm << "\n";
    if(n == pos) {
        f1 |= (cur == 1);
        fm |= (cur == m);
        if(f1 & fm) return 1;
        else return 0;
    }
    int &ans = dp[pos][cur][f1][fm];
    if(ans != -1) return ans;
    ans = 0;
    ans = (ans + f(pos + 1, cur + 1, (f1 | (cur == 1)), (fm | (cur == m)))) % mod;
    ans = (ans + f(pos + 1, cur - 1, (f1 | (cur == 1)), (fm | (cur == m)))) % mod;
    return ans;
}
void solve() {
    cin >> n >> m;
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans = (ans + f(1, i, (i == 1), (i == m))) % mod;
    }
    cout << ans << "\n";
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