// https://codeforces.com/problemset/problem/903/D

// becare full of typecase when use bigint128

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 9;

void print128(__int128 x) {
    if (x == 0) {
        std::cout << "0";
        return;
    }
    bool isNegative = false;
    if (x < 0) {
        isNegative = true;
        x = -x;
    }
    std::string result;
    while (x > 0) {
        int digit = x % 10;
        result.push_back('0' + digit);
        x /= 10;
    }
    if (isNegative) {
        result.push_back('-');
    }
    std::reverse(result.begin(), result.end());
    std::cout << result;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> v(n);
    for(auto &x : v) {
        cin >> x;
    }

    __int128 ans = 0, sum = 0;
    map<ll, ll> mp;
    for(int i = 0; i < n; i++) {
        __int128 v1 = (__int128)i * v[i] - sum;
        __int128 v2 = (__int128)mp[v[i]-1] * v[i] - (__int128)mp[v[i]-1] * (v[i]-1);
        __int128 v3 = (__int128)mp[v[i]+1] * (v[i]+1) - (__int128)mp[v[i]+1] * v[i];
        v1 = v1 - v2 + v3;
        ans += v1;
        sum += v[i];
        mp[v[i]]++;
    }

    print128(ans);
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