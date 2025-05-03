//https://codeforces.com/contest/1592/problem/C

/*
when works using Xor on tree alz care about subtree
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
ll const neg = -1e18;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot ^= a[i];
    }
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if(tot == 0) {
        cout << "YES\n";
        return;
    }

    if (k < 3) {
        cout << "NO\n";
        return;
    }

    int cnt = 0;
    function<ll(int, int)> f = [&](int u, int p) -> ll {
        ll cur = a[u];
        for(auto v : g[u]) if(v != p) {
            cur ^= f(v, u);
        }
        if(cur == tot) {
            cnt++;
            return 0;
        }
        return cur;
    };

    f(1, 0);

    cout << (cnt >= 2 ? "YES" : "NO") << "\n";
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

// wa code

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
ll const neg = -1e18;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot ^= a[i];
    }
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if(tot == 0) {
        cout << "YES\n";
        return;
    }

    if (k < 3) {
        cout << "NO\n";
        return;
    }

    vector<ll> dp(n + 1, 0);
    function<ll(int, int)> f = [&](int u, int p) -> ll {
        dp[u] = a[u];
        for(auto v : g[u]) if(v != p) {
            f(v, u);    
            dp[u] ^= dp[v];
        }
        return dp[u];
    };

    f(1, 0);

    map<int, int> mp;
    for(int i = 2; i <= n; i++) {
        mp[dp[i]]++;
    }

    cout << (mp[tot] >= 2 ? "YES" : "NO") << "\n";
 
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}

this overcounts 
