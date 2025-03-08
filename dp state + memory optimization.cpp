#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 1e9 + 7;
int dp[20][20][5300];
ll a[201];
array<int, 2> pw[201];
int n, k;
int f(int pos, int rem, int p5) {
    if(pos > n) {
        if(rem == 0 && p5 == 0) return 0;
        return -100;
    }
    int &ans = dp[pos][rem][p5];
    if(ans != -1) return ans;
    ans = f(pos + 1, rem, p5);
    if(p5 - pw[pos][1] >= 0) {
        ans = max(ans, pw[pos][0] + f(pos + 1, rem - 1, p5 - pw[pos][1]));
    }
    return ans;
}
void solve() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        ll val = a[i];
        int cnt2 = 0, cnt5 = 0;
        while(val % 2 == 0) {
            val /= 2;
            cnt2++;
        }
        while(val % 5 == 0) {
            val /= 5;
            cnt5++;
        }
        tot += cnt5;
        pw[i] = {cnt2, cnt5};
    }
    //memset(dp, -1, sizeof dp);
    int ans = 0;
    for(int cnt5 = 1; cnt5 <= tot; cnt5++) {
        //ans = max(ans, min(f(1, k, cnt5), cnt5));
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

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    array<int, 2> pw[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        ll val = a[i];
        int cnt2 = 0, cnt5 = 0;
        while(val % 2 == 0) {
            val /= 2;
            cnt2++;
        }
        while(val % 5 == 0) {
            val /= 5;
            cnt5++;
        }
        tot += cnt5;
        pw[i] = {cnt2, cnt5};
    }
   
    vector<vector<vector<int>>> dp(n + 2, vector<vector<int>>(k + 2, vector<int>(tot + 2, -1e9)));
    
    for(int i = 1; i <= n; i++) {
        dp[i][0][0] = 0;
    }

    int ans = 0;
    for(int cnt5 = 1; cnt5 <= tot; cnt5++) {
        //ans = max(ans, min(f(1, k, cnt5), cnt5));
        for(int pos = n + 1; pos >= 1; pos--) {
            for(int rem = 0; rem <= k; rem++) {
                for(int p5 = 0; p5 <= cnt5; p5++) {
                    if(pos > n) {
                        if(rem == 0 && p5 == 0) {
                            dp[pos][rem][p5] = 0;
                        }
                        else {
                            dp[pos][rem][p5] = -1e9;
                        }
                        continue;
                    }
                    int &ans = dp[pos][rem][p5];
                    ans = dp[pos + 1][rem][p5];
                    if(p5 - pw[pos][1] >= 0 && rem - 1 >= 0) {
                        ans = max(ans, pw[pos][0] + dp[pos + 1][rem - 1][p5 - pw[pos][1]]);
                    }
                    dp[pos][rem][p5] = ans;
                }
            }
        }
        cout << cnt5 << " " << dp[1][k][cnt5] << "\n";
        ans = max(ans, min(cnt5, dp[1][k][cnt5]));
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

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    array<int, 2> pw[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        ll val = a[i];
        int cnt2 = 0, cnt5 = 0;
        while(val % 2 == 0) {
            val /= 2;
            cnt2++;
        }
        while(val % 5 == 0) {
            val /= 5;
            cnt5++;
        }
        tot += cnt5;
        pw[i] = {cnt2, cnt5};
    }
   
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(k + 2, vector<int>(tot + 2, -1e9)));
    
    dp[0][0][0] = 0;
    dp[1][0][0] = 0;

    int res = 0;

    for(int pos = n + 1; pos >= 1; pos--) {
        int cur, pre;
        if(pos & 1) {
            cur = 1;
            pre = 0;
        }
        else {
            cur = 0;
            pre = 1;
        }
        for(int rem = 0; rem <= k; rem++) {
            for(int p5 = 0; p5 <= tot; p5++) {
                if(pos > n) {
                    if(rem == 0 && p5 == 0) {
                        dp[cur][rem][p5] = 0;
                    }
                    else {
                        dp[cur][rem][p5] = -1e9;
                    }
                    continue;
                }
                int &ans = dp[cur][rem][p5];
                ans = dp[pre][rem][p5];
                if(p5 - pw[pos][1] >= 0 && rem - 1 >= 0) {
                    ans = max(ans, pw[pos][0] + dp[pre][rem - 1][p5 - pw[pos][1]]);
                }
                dp[cur][rem][p5] = ans;
                if(pos == 1 && rem == k) {
                    res = max(res, min(p5, ans));
                }
            }
        }
    }

    cout << res << "\n";
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