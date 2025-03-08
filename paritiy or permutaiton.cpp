// https://codeforces.com/problemset/problem/911/D

// if number of inversion of a permutation is ODD 
// then with one swap it become even then again odd
// also from an identity permutation if using X swap we got a permtaion
// and also if using Y swap we got same permtaion
// then X % 2 == Y % 2 must HOLD

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 9;
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;

    auto get = [&]() {
        int cnt = 0;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(v[j] > v[i]) cnt++;
            }
        }
        return cnt;
    };

    int tot = get();

    string o = "odd", e = "even";
    string ans = e;

    if(tot & 1) {
        ans = o;
    }

    int q; cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        if((len / 2) & 1) {
            if(ans == e) ans = o;
            else ans = e;
        }
        cout << ans << "\n";
    }
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