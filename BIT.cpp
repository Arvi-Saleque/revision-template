// https://cses.fi/problemset/task/1144/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 9, mod = 998244353; 

template <class T>
struct BIT { //1-indexed
  int n; vector<T> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    vector<int> st;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        st.push_back(v[i]);
    }
    vector<array<int, 3>> Q;
    while(q--) {
        char ch; cin >> ch;
        if(ch == '?') {
            int a, b;
            cin >> a >> b;
            Q.push_back({1, a, b});
            st.push_back(a);
            st.push_back(b);
        }
        else {
            int idx, x;
            cin >> idx >> x;
            st.push_back(x);
            Q.push_back({2, idx, x});
        }
    }
 
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
 
    int mx = 0;
 
    auto id = [&](int x) {
        int val = lower_bound(st.begin(), st.end(), x) - st.begin();
        mx = max(mx, val + 1);
        return val + 1;
    };
 
    map<int, int> cnt;
    for(int i = 1; i <= n; i++) {
        v[i] = id(v[i]);
        cnt[v[i]]++;
    }    
    for(auto &[ty, x, y] : Q) {
        if(ty == 1) {
            x = id(x);
            y = id(y);
        }
        else {
            y = id(y);
        }
    }   
 
    n = mx + 1;
    
    BIT<ll> bit(n);
 
    for(int i = 1; i < n; i++) {
        bit.upd(i, cnt[i]);
    }
 

    for(auto [ty, x, y] : Q) {
        if(ty == 1) {
            cout << bit.query(x, y) << "\n";
        }
        else {
            bit.upd(v[x], -1);
            v[x] = y;
            bit.upd(v[x], 1);
        }
    } 
 
 
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": " << "\n";
        solve();
    }
}
