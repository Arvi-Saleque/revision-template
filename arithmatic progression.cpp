// https://codeforces.com/gym/102419/problem/I

// arithmatic progression
// work with difference array and make the
// update a contstant value d 
/*
tree.upd(1, 1, n, l, l, a);
if(l + 1 <= r) tree.upd(1, 1, n, l + 1, r, d);
if(r + 1 <= n) tree.upd(1, 1, n, r + 1, r + 1, -(a + 1LL * (r - l) * d));
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int const N = 1e5 + 2, mod = 1e9 + 7;
class SegTlazy {
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node {
        ll mn, mx;
        bool hasLazy;
        node(){
            mn = 0;
            mx = 0;
            hasLazy = false;
        }
        node(ll _mn, ll _mx, bool _h) {
            mn = _mn;
            mx = _mx;
            hasLazy = _h;
        }
    };
    vector<int> a;
    vector<ll> lazy;
    vector<node> t;
    int n;
    SegTlazy() {
        a.clear();
        t.clear();
        n = 0;
    }   
    SegTlazy(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        lazy.resize(4*n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void merge(node &nd, node &l, node &r) {
        nd.mn = min(l.mn, r.mn);
        nd.mx = max(l.mx, r.mx);
    }
    void push(int nd, int b, int e) {
        if(!t[nd].hasLazy) return;
        t[nd].mn += lazy[nd];
        t[nd].mx += lazy[nd];
        if(b != e) {
            lazy[lc] += lazy[nd];
            t[lc].hasLazy = 1;
            lazy[rc] += lazy[nd];
            t[rc].hasLazy = 1;
        }
        lazy[nd] = 0;
        t[nd].hasLazy = false;
    }
    void upd(int nd, int b, int e, int i, int j, ll v) {
        push(nd, b, e);
        if(j < b || e < i) return;
        if(i <= b && e <= j) {
            lazy[nd] += v;
            t[nd].hasLazy = true;
            push(nd, b, e);
            return;
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd, int b, int e, int i, int j) {
        push(nd, b, e);
        if(j < b || e < i) return node(1e18, -1e18, false);
        if(i <= b && e <= j) {
            return t[nd];
        }
        int mid = b + e >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid + 1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    SegTlazy tree(n);
    while(q--) {
        int ty; cin >> ty;
        if(ty == 1) {
            int l, r;
            cin >> l >> r;    
            if(l == r) {
              cout << 1 << "\n";
              continue;
            }
            auto nd = tree.query(1, 1, n, l + 1, r);
            cout << (nd.mn == nd.mx && nd.mn == 0 ? 1 : 0) << "\n";
        }
        else {
            ll l, r, a, d;
            cin >> l >> r >> a >> d;
            tree.upd(1, 1, n, l, l, a);
            if(l + 1 <= r) tree.upd(1, 1, n, l + 1, r, d);
            if(r + 1 <= n) tree.upd(1, 1, n, r + 1, r + 1, -(a + 1LL * (r - l) * d));
        }
    }
}  
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t; 
    while(t--) {
        //cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}
