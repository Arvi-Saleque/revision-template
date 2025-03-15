// https://atcoder.jp/contests/abc155/tasks/abc155_d?lang=en

// if i need to count somethinig kth value then first 
// check if somehow it is possible to bs on the ans
// such as how many values <= x and then check x == k

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for(auto &x : v) cin >> x;
    sort(v.begin(), v.end());
    
    auto f = [&](ll val) {
        vector<ll> pos, neg;
        for(auto x : v) {
            if(x > 0) pos.push_back(x);
            if(x < 0) neg.push_back(x);
        }
        int zero = n - (pos.size() + neg.size());
        ll cnt = 0;

        if(val < 0) {
            for(auto x : neg) { // < 0 part
                if(val % x == 0) {
                    auto it2 = lower_bound(pos.begin(), pos.end(), val / x); 
                    cnt += max(0LL, 1LL*(pos.end() - it2));
                }
                else {
                    auto it2 = upper_bound(pos.begin(), pos.end(), val / x); 
                    cnt += max(0LL, 1LL*(pos.end() - it2));
                }
            }
        }
        else {
            cnt += (1LL * neg.size() * (n - neg.size()));
            ll r = n - neg.size() - 1, l = r - zero + 1;
            cnt += (1LL * (((l + r) * zero) / 2LL));
            //cout << (((l + r) * zero) >> 1) << "\n";
            if(val > 0) {
                for(int i = 0; i < pos.size(); i++) {
                    auto it2 = upper_bound(pos.begin(), pos.end(), val / pos[i]);
                    //cout << pos[i] << " " << (it2 - pos.begin()) - i - 1 << "\n";
                    cnt += max(0LL, 1LL*((it2 - pos.begin()) - i - 1));
                }
                pos.clear();
                for(auto x : neg) {
                    pos.push_back(-x);
                }
                sort(pos.begin(), pos.end());
                for(int i = 0; i < pos.size(); i++) {
                    auto it2 = upper_bound(pos.begin(), pos.end(), val / pos[i]);
                    //cout << pos[i] << " " << (it2 - pos.begin()) - i - 1 << "\n";
                    cnt += max(0LL, 1LL*((it2 - pos.begin()) - i - 1));
                }
            }
        }

        return cnt;
    };

    ll lo = -1e18, hi = 1e18, mid, ans = -1;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        //cout << mid << " " << f(mid) << "\n";
        if(f(mid) >= k) {
            ans = mid;
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
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
