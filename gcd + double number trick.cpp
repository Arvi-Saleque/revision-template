// https://codeforces.com/problemset/problem/983/A

// we can reprensent any double number = val / 10^k
// so for 10^k % q = 0 must be when every prime of q is in 10
// for b base
// so for b^k % q = 0 must be when every prime of q is in b
// for gcd dont use __gcd use gcd()
// also if you need to know cehck if 
// every prime of q also occur in b
// then just do
/*
while(gcd(q, b) != 1) {
    ll g = gcd(q, b);
    q /= g;
}
and check if q == 1
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 998244353;
void solve() {
    ll p, q, b;
    cin >> p >> q >> b;

    ll g = gcd(p, q);
    q /= g;

    while(gcd(q, b) != 1) {
        ll g = gcd(q, b);
        q /= g;
    }

    cout << ((q == 1) ? "Finite\n" : "Infinite\n");

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
