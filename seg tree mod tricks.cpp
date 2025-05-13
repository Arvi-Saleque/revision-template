// https://codeforces.com/contest/438/problem/D

/*
If I need to work with mod on segment tree lazy
we cant do lazy as we do instead 
we do something like point update with mx >= mod
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 9, mod = 998244353; 

class SegTlazy
{
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node
    {
        ll sum, mx;
        node() {
            sum = mx = 0;
        };
        node (ll s, ll _mx) {
            sum = s;
            mx = _mx;
        }
    };
    vector<int> a;
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
        t.resize(4*n + 1, node());
    }
    void take_input() {
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(1, 1, n);
    }
    inline void merge(node &ND, node L, node R) {
        ND.sum = L.sum + R.sum;
        ND.mx = max(L.mx, R.mx);
    } 
    void build(int nd, int b, int e) {
        if(b == e) {
            t[nd].sum = t[nd].mx = a[b];
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
    void upd(int nd, int b, int e, int i, int j, int v) {
        if(j < b || e < i) return;
        if(v > 0 && t[nd].mx < v) return; 
        if(b == e) {
            if(v < 0) {
                t[nd].sum = -v;
                t[nd].mx = -v;
            }
            else {
                t[nd].sum %= v;
                t[nd].mx %= v;
            }
            return;
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd, int b, int e, int i, int j) {
        if(j < b || e < i) return node();
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
    tree.take_input();

    auto print = [&]() {
        for(int i = 1; i <= n; i++) {
            cout << tree.query(1, 1, n, i, i).sum << " \n"[i == n];
        }
        for(int i = 1; i <= n; i++) {
            cout << tree.query(1, 1, n, i, i).mx << " \n"[i == n];
        }
        cout << "\n";
    };

    while(q--) {
        int ty; cin >> ty;
        if(ty == 1) {
            int l, r;
            cin >> l >> r;
            cout << tree.query(1, 1, n, l, r).sum << "\n";
        }
        else if(ty == 2) {
            int l, r, x; cin >> l >> r >> x;
            tree.upd(1, 1, n, l, r, x);
        }
        else {
            int id, x;
            cin >> id >> x;
            tree.upd(1, 1, n, id, id, -x);
        }

        //print();
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
