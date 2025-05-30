// https://atcoder.jp/contests/abc098/tasks/arc098_b?lang=en

// if there are max 1 bit on then
// A[l] + ... + A[r] = A[l] ^ .... ^ A[r];
// so to count number of pair (l, r)
// we can use BS 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<ll> presum(n + 1, 0), prexor(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + v[i];
        prexor[i] = prexor[i - 1] ^ v[i];
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int lo = i, hi = n, mid, bans = -1;
        //cout << i << "\n";
        while(lo <= hi) {
            mid = lo + hi >> 1;
            ll v1 = presum[mid] - presum[i - 1];
            ll v2 = prexor[mid] ^ prexor[i - 1];
            //cout << mid << " " << v1 << " " << v2 << "\n";
            if(v1 == v2) {
                bans = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        //cout << i << " - " << (bans - i + 1) << "\n";
        ans += (bans - i + 1); 
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

// https://vjudge.net/problem/codeforces-1368d

// check if it possible to work on bit independelty
// and somehow shift the bit 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
void solve() { 
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<int> cnt(20);
    for(int j = 19; j >= 0; j--) {
        for(auto x : v) {
            if(x & (1 << j)) {
                cnt[j]++;
            }
        }
    }

    v.clear();
    v.resize(n + 1, 0);
    for(int i = 0; i <= 19; i++) {
        for(int j = 0; j < cnt[i]; j++) {
            v[j] += (1 << i);
        }
    }

    ll sum = 0;
    for(int i = 0; i < n; i++) {
        //cout << v[i] << " \n"[i + 1 == n];
        sum += (1LL * v[i] * v[i]);
    }

    cout << sum << "\n";
}          
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;  
    //cin >> t;
    while (t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
