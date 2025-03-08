// https://codeforces.com/problemset/problem/632/D

// if i need to make x <= LCM 
// we can fix x say x = k and check if we can make k = LCM
// then solve for all 1 to x
// also let LCM = p -> LCM = p^n -> LCM = P * Q -> LCM = p^a * Q^b

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 9;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> divs[m + 1];
    auto pre = [&]() {
        for(int i = 1; i <= m; i++) {
            for(int j = i; j <= m; j += i) {
                divs[j].push_back(i);
            }
        }
    };
    pre();
    vector<int> cnt(m + 1);
    vector<int> v(n);
    for(auto &x : v) {
        cin >> x;
        if(x <= m) cnt[x]++;
    }

    int ans = 0, mx = 0;
    for(int i = 1; i <= m; i++) {
        int tmp = 0;
        for(auto v : divs[i]) {
            tmp += cnt[v];
        }
        if(ans < tmp) {
            ans = tmp;
            mx = i;
        }
    }

    if(mx == 0) {
        cout << 1 << " " << 0 << "\n";
    }
    else {
        cout << mx << " " << ans << "\n";
        for(int i = 0; i < n; i++) {
            if(mx % v[i] == 0) {
                cout << i + 1 << " ";
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