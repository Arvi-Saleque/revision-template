// https://atcoder.jp/contests/abc107/tasks/arc101_b?lang=en

// to calcualte median of median we can conver this problem
// to find kth smallest number among all subarray
// so we can do binary search 
// we just make +1/-1 array 
// if v[i] <= x a[i] = 1 else -1
// then using prefix sum we can count easily
// how many values there are <= x

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T> using o_set = tree<T, null_type, 
less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    ll k = (1LL * n * (n + 1)) / 2;
    k = (k / 2) + 1;

    auto check = [&](ll x) {
        vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) {
            if(v[i] <= x) a[i] = 1;
            else a[i] = -1;
        }
        ll cnt = 0, cur = 0;
        o_set<pair<ll, int>>se;
        se.insert({0, 0});
        for(int i = 1; i <= n; i++) {
            cur += a[i];
            cnt += se.order_of_key({cur, 0});
            se.insert({cur, i});
        }
        return cnt;
    };

    vector<int> vv;
    for(int i = 1; i <= n; i++) {
        vv.push_back(v[i]);
    }

    sort(vv.begin(), vv.end());
    int lo = 0, hi = n - 1, mid, ans = -1;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(check(vv[mid]) >= k) {
            ans = vv[mid];
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans << "\n";
}  
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        //cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}
