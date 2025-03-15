// https://codeforces.com/problemset/problem/1342/C

// if i need to count something for a big range
// check if cycle is found
// then just use some precalucaltions 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
const ll inf = 1e18;
void solve() {
    int a, b, q;
    cin >> a >> b >> q;
    int lc = (a * b) / __gcd(a, b);
    int cnt = 0;
    vector<int> pref(lc + 1);
    for(int x = 1; x <= lc; x++) {
        if(((x % a) % b) != ((x % b) % a)) {
            pref[x]++;
            cnt++;
        }
        pref[x] += pref[x - 1];
    }
    auto f = [&](ll n) {
        ll val = (n / lc);
        ll ans = 1LL * val * cnt;
        ans += pref[n % lc];
        return ans;
    };
    while(q--) {
        ll l, r;
        cin >> l >> r;
        cout << max(0LL, f(r) - f(l - 1)) << " ";
    }
    cout << "\n";
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
