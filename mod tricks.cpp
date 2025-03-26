https://cses.fi/problemset/task/1712

if you need to caulaute a^b^c % mod
then must use b % phi(mod)
c % phi(phi(mod)) 
for any prime mod m = a^b % mod = a^(b%(mod-1)) % mod

https://tlx.toki.id/problems/troc-16/E

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
int spf[N + 2];
void pre() {
    for(int i = 1; i <= N; i++) {
        spf[i] = i;
    }
    for(int i = 2; i <= N; i++) {
        if(spf[i] == i) {
            for(int j = i * 2; j <= N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}
ll power(ll a, ll b) {
    if(b < 0) return 0;
    if(b == 0) return 1;
    ll ans = 1;
    bool f = 0;
    while(b) {
        if(b & 1) {
            ans *= a;
            if(ans >= mod) {
                ans %= mod;
                f = 1;
            }
        }
        a *= a;
        if(a >= mod) {
            a %= mod;
            f = 1;
        }
        b >>= 1;
    }
    return (ans + (f * mod)) % mod;
}
void solve() {
    int n;
    cin >> n;
    vector<int> vv(n + 1);  
    set<int> st;
    for(int i = 1; i <= n; i++) {
        cin >> vv[i];
        int val = vv[i];
        while(val > 1) {
            st.insert(spf[val]);
            val /= spf[val];
        }
    }

    map<int, vector<pair<int, int>>> mp;

    for(int i = 1; i <= n; i++) {
        int val = vv[i];
        while(val > 1) {
            int sml = spf[val];
            int mul = 1;
            while(val % sml == 0) {
                mul *= sml;
                val /= sml;
            }
            mp[sml].push_back({i, mul});
        }
    }

    ll ans = 1;

    for(auto &[x, v] : mp) {
        int m = v.size();
        // make 1-based 
        v.push_back({-1, -1});
        sort(v.begin(), v.end());

        stack<pair<int, int>> right_max, left_max; // right strict
        right_max.push({1e9, n + 1});
        left_max.push({1e9, 0});
        vector<int> left(m + 1);
        vector<int> right(m + 1);
        for(int i = m; i >= 1; i--) {
            while(!right_max.empty() && right_max.top().first <= v[i].second) {
                right_max.pop();
            }
            right[i] = right_max.top().second;
            right_max.push({v[i].second, v[i].first});
        }
        for(int i = 1; i <= m; i++) {
            while(!left_max.empty() && left_max.top().first < v[i].second) {
                left_max.pop();
            }
            left[i] = left_max.top().second;
            left_max.push({v[i].second, v[i].first});
        }

        for(int j = 1; j <= m; j++) {
            int l = left[j], r = right[j];
            auto [i, mul] = v[j];
            //cout << sml << " " << l << " " << r << "\n";
            ll cnt = (1LL * (i - l) * (r - i)) % (mod - 1);
            //cout << mul << " -- " << cnt << "\n";
            ans = (ans * power(mul, cnt)) % mod;
        }
    }

    cout << ans << "\n";
}   
int main() {
    pre();
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        // /cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
