// https://www.spoj.com/problems/IITKWPCH/

// at first mark all mask then try inclusion exclusion using check all mask

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9;
void solve() {
    int n;
    cin >> n;
    vector<ll> mp(3000, 0);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        ll mask = 0;
        for(auto x : s) {
            mask |= (1 << (x - '0'));
        }
        mp[mask]++;
    }
    ll ans = 0;
    for(int curmask = 1; curmask < (1 << 10); curmask++) {
        int cnt = 0;
        for(int allmask = 1; allmask < (1 << 10); allmask++) {
            if((allmask & curmask) == curmask) {
                cnt += mp[allmask];
            }
        }
        if(__builtin_popcount(curmask) & 1) {
            ans += ((1LL * cnt * (cnt -  1))) / 2;
        }
        else {
            ans -= ((1LL * cnt * (cnt -  1))) / 2;
        }
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
