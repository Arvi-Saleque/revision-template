// https://codeforces.com/contest/812/problem/C
// sometime you can fixed a variable and using binary/ternary search
//reduce number of itterations

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 2e5 + 9, mod = 1e9 + 7;
ll inf = 1e18;
void solve() {
    int n, s;
    cin >> n >> s;
    vector<pair<int, int>> v(n);    
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }
    int lo = 1, hi = n, mid, ansitem = 0, anscost = 0;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        sort(v.begin(), v.end(), [&](auto a, auto b) -> bool {
            auto [x1, y1] = a; 
            auto [x2, y2] = b;
            return (x1 + y1 * mid < x2 + y2 * mid); 
        });
        ll cost1 = 0;
        for(int i = 0; i < mid; i++) {
            auto [x, y] = v[i];
            cost1 += x + 1LL * y * mid;
        }
        if(cost1 <= s) {
            anscost = cost1;
            ansitem = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    cout << ansitem << " " << anscost << "\n";
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
