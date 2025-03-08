// https://codeforces.com/contest/1364/problem/C

// if i need to equal an array a with mex values 
// then i never put any ai before ai
// so mark the safe values and put them 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9;
void solve() {
    int n; cin >> n;
    set<int> has;
    for(int i = 0; i <= 2*n; i++) has.insert(i);
    vector<int> v(n);
    for(auto &x : v) {
        cin >> x;
        if(has.count(x)) has.erase(x);
    }
    vector<int> ans(n, -1);
    for(int i = n - 1; i >= 1; i--) {
        if(v[i] != v[i - 1]) {
            ans[i] = v[i - 1];
        }
    } 
    if(v[0] != 0) {
        ans[0] = 0;
        if(has.count(0)) has.erase(0);
    }
    for(int i = 0; i < n; i++) {
        if(ans[i] == -1) {
            ans[i] = *has.begin();
            has.erase(has.begin());
        }
    }
    for(auto x : ans) {
        cout << x << " ";
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