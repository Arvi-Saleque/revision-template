// https://codeforces.com/contest/888/problem/D

// fixed the same position and permurte/dearange the other positions.

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 1002;
long long C(int n, int r) {
    if(r > n - r) r = n - r;
    ll ans = 1;
    for(int i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}
ll der[12];
void countDer() {
 
    der[1] = 0;
    der[2] = 1;
 
    for (int i = 3; i <= 10; ++i)
        der[i] = (i - 1) * (der[i - 1] + 
                            der[i - 2]);
}
void solve() {
    int n, k;
    cin >> n >> k;
    ll ans = 1;
    for(int i = 0; i <= k; i++) {
        ans += (C(n, i) * der[i]);
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    countDer();
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
