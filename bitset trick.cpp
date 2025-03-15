// https://codeforces.com/gym/103158/problem/I

// given some pair (cnt1, cnt0) put some cnt1 and cnt0
// so sum = x we can do it easily using bitset

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

// https://vjudge.net/problem/UVA-12716

// gcd(a, b) <= b - a
// a ^ b >= b - a
// so gcd(a, b) = a ^ b = b - a
// so just fix d = b - a then pre calculate 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 3e7, mod = 998244353;
ll ans[N + 2];
void pre() {
    for(int d = 1; d <= N; d++) {
        for(int j = d; j + d <= N; j += d) {
            if((j ^ (j + d)) == d) {
                ans[j + d]++;
            }
        }
    }
    for(int i = 2; i <= N; i++) {
        ans[i] += ans[i - 1];
    }
}
void solve() {
    int n;
    cin >> n;
    cout << ans[n] << "\n";
}   
int main() {
    pre();
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t;
    while(t--) {
        cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
