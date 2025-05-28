#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 9, mod = 1e9 + 7; 
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> cnt(N + 1, 0);
    for(auto &x : v) {
        cin >> x;
        cnt[x]++;
    }
 
    int bit = 20;
 
    int mask = (1 << bit);
    
    // 3^n 
 
    auto flip = [&](int x) {
        int val = (~x) & ((1 << bit) - 1);
        return val;
    };
 
    map<int, array<int, 3>> ans;
    
    /*for(int m = 1; m < mask; m++) { // each ai (x)
        if(cnt.count(m) == 0) continue;
        for(int s = m; s; s = (s - 1) & m) { // x | y = x
            if(cnt.count(s) == 0) continue;
            ans[m][0] += cnt[s];
            ans[s][1] += cnt[m];
        }
    }
    
    for(int m = 1; m < mask; m++) { // each ai (x)
        if(cnt.count(m) == 0) continue;
        int fm = flip(m); // ~x 
        for(int s = fm; s; s = (s - 1) & fm) { // x | y = x
            if(cnt.count(s) == 0) continue;
            ans[m][2] += cnt[s]; 
        }
    }*/
 
    vector<int> dp1(mask);
    vector<int> dp2(mask);
    vector<int> dp3(mask);
 
    // efficient solution of 
    // x | y = x part  -> dp[m][i][0]
 
    for(auto m : v) {
        dp1[m] = cnt[m];
    }
 
    for(int i = 0; i < bit; i++) {
        for(int m = 0; m < mask; m++) {
            if(m & (1 << i)) {
                dp1[m] += dp1[m ^ (1 << i)];
            } 
        }
    }
 
    // efficient solution of 
    // x & y = x part  -> dp[m][i][1]
 
    for(auto m : v) {
        dp2[m] = cnt[m];
    }
 
    for(int i = bit - 1; i >= 0; i--) {
        for(int m = 0; m < mask; m++) {
            if(!(m & (1 << i))) {
                dp2[m] += dp2[m | (1 << i)];
            } 
        }
    }
 
    // efficient solution of 
    // x & y = 0 part  -> dp[m][i][2]
 
    for(auto m : v) {
        dp3[m] = cnt[m];
    }
 
    vector<int> fliped(mask);
    for(int i = 0; i < mask; i++) {
        fliped[i] = flip(i);
    }
 
    for(int i = 0; i < bit; i++) {
        for(int m = 0; m < mask; m++) {
            int mm = fliped[m];
            if(mm & (1 << i)) {
                dp3[mm] += dp3[mm ^ (1 << i)];
            } 
        }
    }
 
 
    for(auto x : v) {
        cout << dp1[x] << " " << dp2[x] << " " << n -  dp3[fliped[x]] << "\n";
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
} 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 9, mod = 1e9 + 7; 
void solve() {
    int n;
    cin >> n;
    int bit = 20;
    int mask = (1 << bit);
    vector<int> v(n);
    vector<int> dp1(mask + 1, 0), dp2(mask + 1, 0);
    for(auto &x : v) {
        cin >> x;
        dp1[x]++;
        dp2[x]++;
    }
     
    auto flip = [&](int x) {
        int val = (~x) & ((1 << bit) - 1);
        return val;
    };

    for(int i = 0; i < bit; i++) {
        for(int m = 0; m < mask; m++) {
            if(m & (1 << i)) {
                dp1[m] += dp1[m ^ (1 << i)];
            } 
        }
    }
 
    for(int i = bit - 1; i >= 0; i--) {
        for(int m = mask - 1; m >= 0; m--) {
            if(!(m & (1 << i))) {
                dp2[m] += dp2[m ^ (1 << i)];
            } 
        }
    }
     
    for(auto x : v) {
        // complement of x = (1 << bit) - 1 - x 
        cout << dp1[x] << " " << dp2[x] << " " << n - dp1[(1 << bit) - 1 - x] << "\n";
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
} 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 9, mod = 1e9 + 7; 
void solve() {
    int n;
    cin >> n;
    int bit = 23;
    int mask = (1 << bit);
    vector<int> v(n);
    vector<int> dp1(mask + 1, 0), par(mask + 1, 0);
    for(auto &x : v) {
        cin >> x;
        dp1[x]++;
        par[x] = x;
    }
     
    for(int i = 0; i < bit; i++) {
        for(int m = 0; m < mask; m++) {
            if(m & (1 << i)) {
                dp1[m] += dp1[m ^ (1 << i)];
                par[m] = max(par[m], par[m ^ (1 << i)]);
            } 
        }
    }

    for(auto x : v) {
        int flipx = (1 << bit) - 1 - x;
        cout << (dp1[flipx] == 0 ? -1 : par[flipx]) << " ";
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
} 


//https://cses.fi/problemset/task/3141/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 9, mod = 1e9 + 7; 
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    int bit = 18;
    int mask = (1 << bit);
    vector<ll> cnt(mask);
    for(auto &x : v) {
        cin >> x;
        cnt[x]++;
    }

    for(int i = bit - 1; i >= 0; i--) {
        for(int m = mask - 1; m >= 0; m--) {
            if(!(m & (1 << i))) {
                cnt[m] = (cnt[m] + cnt[m ^ (1 << i)]) % mod; // supermask
            }
        }
    }

    vector<ll> pw(n + 1);
    pw[0] = 1;
    for(int i = 1; i<= n; i++) {
        pw[i] = (1LL * 2 * pw[i - 1]) % mod;
    }

    vector<ll> sup(mask);
    for(int m = 0; m < mask; m++) {
        sup[m] = (pw[cnt[m]] - 1 + mod) % mod;
    }

    auto exact = sup;
    for(int i = 0; i < bit; i++) {
        for(int m = 0; m < mask; m++) {
            if(!(m & (1 << i))) {
                exact[m] = (exact[m] - exact[m | (1 << i)] + mod) % mod;
            }
        }
    }

    for(int i = 0; i <= n; i++) {
        cout << exact[i] << " ";
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
} 
