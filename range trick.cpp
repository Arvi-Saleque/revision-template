// https://vjudge.net/problem/AtCoder-abc163_d

// if i have 1 2 3 4 5 6 and i can pick at least k element
// then i can make all valus from  1 + 2 + 3 = 6 to 4 + 5 + 6 = 15

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 2e5 + 9, mod = 1e9 + 7;
ll inf = 1e18;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    n++;
    for(int i = 0; i < n; i++) {
        v[i] = i;
    }
    ll ans = 0;
    ll mn = 0, mx = 0;
    int l = 0, r = n - 1;
    while(l < k) {
        mn += v[l];
        mx += v[r];
        l++;
        r--;
    }
    ans = (ans + (mx - mn + 1)) % mod;
    while(l < n) {
        mn += v[l];
        mx += v[r];
        ans = (ans + (mx - mn + 1)) % mod;
        l++;
        r--;
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
