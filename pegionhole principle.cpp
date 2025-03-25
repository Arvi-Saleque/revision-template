#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 2, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    ll sum = 0;
    map<int, int> mp;
    mp[0] = 0;
    for(int i = 0; i < n; i++) {
        if(v[i] % n == 0) {
            cout << 1 << "\n";
            cout << i + 1 << "\n";
            return;
        }
        sum += v[i];
        int rem = sum % n;
        if(mp.count(rem)) {
            vector<int> ans;
            for(int j = mp[rem] + 1; j <= i + 1; j++) {
                ans.push_back(j);
            }
            cout << ans.size() << "\n";
            for(auto x : ans) {
                cout << x << " ";
            }
            cout << "\n";
            return;
        }
        mp[rem] = i + 1;
    }

    cout << "-1\n";
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
