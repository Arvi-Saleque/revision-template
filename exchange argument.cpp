// https://codeforces.com/problemset/problem/632/C

// exchagne argument

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9;
void solve() {
    int n;
    cin >> n;
    vector<string> vpp(n);
    for(auto &x : vpp) {
        cin >> x;
    }

    sort(vpp.begin(), vpp.end(), [&](auto a, auto b) -> bool {
        return (a + b < b + a);
    });

    for(auto x : vpp) {
        cout << x;
    }
    cout << "\n";

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