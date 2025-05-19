// https://codeforces.com/contest/1142/problem/B

/*
when all number distinct and we need to work something like
take n values like a permutation 
so we can check the first value and then
nth parent of that value
so we need binary lifting
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    if (n == 1) {
        for (int i = 1, x; i <= n; i++) cin >> x;
        for (int i = 1, x; i <= m; i++) cin >> x;
        for (int i = 1, x; i <= q; i++) cin >> x;
        cout << string(q, '1') << "\n";
        return;
    }
    vector<int> p(n), v(m+1), par(n+1);
    for (auto &x : p) cin >> x;
    for (int i = 1; i < n; i++) par[p[i-1]] = p[i];
    par[p.back()] = p[0];
    map<int, vector<int>> mp;
    for (int i = 1; i <= m; i++) {
        cin >> v[i];
        mp[v[i]].push_back(i);
    }

    int lg = __lg(n) + 1;
    vector<vector<int>> parQ(m + 2, vector<int>(lg + 1, m + 1));

    for (int i = 1; i <= m; i++) {
        int target = par[v[i]];
        auto &vec = mp[target];
        auto it = upper_bound(vec.begin(), vec.end(), i);
        parQ[i][0] = (it == vec.end() ? m + 1 : *it);
    }

    for(int i = m; i >= 1; i--) {
        for(int j = 1; j <= lg; j++) {
            parQ[i][j] = parQ[parQ[i][j - 1]][j - 1];
        }
    }


    auto get = [&](int x, int k) {
        while(k > 0) {
            int pos = 31 - __builtin_clz(k);
            x = parQ[x][pos];
            k -= (1 << pos);
        }
        return x;
    };


    vector<int> bestR(m+2, m+2);
    
    for (int i = m; i >= 1; i--) {
        bestR[i] = get(i, n - 1);
        bestR[i] = min(bestR[i], bestR[i+1]);
    }

    string ans(q, '0');
    for (int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        if (bestR[l] <= r) ans[i] = '1';
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
