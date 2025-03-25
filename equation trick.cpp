// https://codeforces.com/problemset/problem/1189/E

// if we need to work with modular arithmatic 
// like ai + aj (=) ai^2 + aj^2 mod p
// then try to generanize and make all i/j in one side
// do some algebra and try to find solution

<details> <summary>Click to expand</summary>
markdown
Copy
```latex
We start with the given equation:
$$
(a_i + a_j)(a_i^2 + a_j^2) \equiv k \pmod{p}.
$$

Observe that the difference of fourth powers factors as:
$$
a_i^4 - a_j^4 = (a_i - a_j)(a_i + a_j)(a_i^2 + a_j^2).
$$

Since \(a_i \neq a_j\) (and thus \(a_i - a_j \not\equiv 0 \pmod{p}\)), we can divide both sides by \(a_i - a_j\) (in modulo \(p\)) to get:
$$
\frac{a_i^4 - a_j^4}{a_i - a_j} \equiv k \pmod{p}.
$$

Multiplying both sides by \((a_i - a_j)\) leads to:
$$
a_i^4 - a_j^4 \equiv k(a_i - a_j) \pmod{p}.
$$

Rearrange the equation to group terms with \(a_i\) and \(a_j\) separately:
$$
a_i^4 - k\,a_i \equiv a_j^4 - k\,a_j \pmod{p}.
$$

This motivates the definition of the function:
$$
f(x) = x^4 - kx \pmod{p}.
$$

Thus, the condition for a valid pair \((i,j)\) is equivalent to:
$$
f(a_i) \equiv f(a_j) \pmod{p}.
$$
css
Copy
</details>



#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
void solve() {
    ll n, p, k;
    cin >> n >> p >> k;
    vector<ll> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    auto f = [&](ll x) {
        ll ans = 1;
        for(int i = 1; i <= 4; i++) {
            ans = ((1LL * ans * x) % p);
        }
        return ans;
    };

    map<ll, int> mp;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll val = ((f(v[i])  - (1LL * k * v[i]) % p) + p) % p;
        ans += mp[val];
        mp[val]++;
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
