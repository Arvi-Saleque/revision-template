// https://atcoder.jp/contests/abc134/tasks/abc134_e?lang=en

// to calcualte longest non-increasing subsequence
// just make v[i] = -v[i]
// and find longest increasing subsequence

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
    int n; cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        v[i] = -x;
    }
    vector<int> inc;
    for(int i = 1; i <= n; i++) {
        auto it = upper_bound(inc.begin(), inc.end(), v[i]);
        if(it == inc.end()) {
            inc.push_back(v[i]);
        }
        else {
            *it = v[i];
        }
    }
    cout << inc.size() << "\n";
    
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
