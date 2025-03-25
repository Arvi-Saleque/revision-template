// https://codeforces.com/gym/102881/problem/E

// two consecutive value XOR = 1 maens even
//  "          " value OR  = odd


#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
void solve() {
    int n, q;
    cin >> n >> q;
    set<int> odd, ev;
    vector<int> v(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        if((v[i] & 1) && v[i] > 1) {
            odd.insert(i);
        }
        else {
            ev.insert(i);
        }
        sum += v[i];
    }

    while(q--) {
        int ty, l, r;
        cin >> ty >> l >> r;
        if(ty == 2) {
            auto it1 = odd.lower_bound(l);
            vector<int> tmp;
            while(it1 != odd.end() && *it1 <= r) {
                int val = v[*it1];
                sum -= val;
                sum++;
                tmp.push_back(*it1);
                it1++;
            }
            for(auto x : tmp) {
                odd.erase(x);
            }
            it1 = ev.lower_bound(l);
            tmp.clear();
            while(it1 != ev.end() && *it1 <= r) {
                int val = v[*it1];
                int val2 = val ^ (val - 1);
                sum -= val;
                sum += (val2);
                v[*it1] = val2;
                odd.insert(*it1);
                tmp.push_back(*it1);
                it1++;
            }
            for(auto x : tmp) {
                ev.erase(x);
            }
        }
        else {
            auto it1 = ev.lower_bound(l);
            vector<int> tmp;
            while(it1 != ev.end() && *it1 <= r) {
                int val = v[*it1];
                int val2 = val | (val - 1);
                sum -= val;
                sum += (val2);
                v[*it1] = val2;
                odd.insert(*it1);
                tmp.push_back(*it1);
                it1++;
            }
            for(auto x : tmp) {
                ev.erase(x);
            }
        }
        cout << sum << "\n";
    }
}   
int main() {
    freopen("orxor.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
