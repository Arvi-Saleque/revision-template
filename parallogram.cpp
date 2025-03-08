// https://codeforces.com/problemset/problem/660/D

// if we need to work with parallogram 
// we can work with the middle point of two diagonal

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e5 + 9, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> vpp;
    for(int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        vpp.push_back({x, y});
    }
    map<pair<int, int>, int> cnt;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int midX = vpp[i].first + vpp[j].first;
            int midY = vpp[i].second + vpp[j].second;
            cnt[make_pair(midX, midY)]++;
        }
    }

    ll ans = 0;
    for(auto [x, y] : cnt) {
        ans += (y*(y-1))/2LL;
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